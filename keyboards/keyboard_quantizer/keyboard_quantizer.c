/* Copyright 2020 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyboard_quantizer.h"

#include "print.h"
#include "string.h"
#include "uart.h"
#include "quantum.h"

bool ch559UpdateMode = false;

bool    ch559_start  = false;
uint8_t device_cnt = 0;
uint8_t hid_info_cnt = 0;

__attribute__((weak)) void keyboard_post_init_kb_rev(void) {}

void keyboard_post_init_kb() {
    // debug_enable   = true;
    // debug_keyboard = true;
    keyboard_post_init_kb_rev();
}

enum {
    SLIP_END     = 0xC0,
    SLIP_ESC     = 0xDB,
    SLIP_ESC_END = 0xDC,
    SLIP_ESC_ESC = 0xDD,
};

enum {
    LEN_L = 0,
    LEN_H,
    MSG_TYP,
    DEV_TYP,
    DEV_NUM,
    EP,
    VID_L,
    VID_H,
    PID_L,
    PID_H,
    REPORT_START,
} packet_index;

enum {
    CONNECTED = 1,
    DISCONNECTED,
    ERROR,
    DEVICE_POLL,
    DEVICE_STRING,
    DEVICE_INFO,
    HID_INFO,
    STARTUP,
} msg_type;

enum {
    NONE = 0,
    POINTER,
    MOUSE,
    RESERVED,
    JOYSTICK,
    GAMEPAD,
    KEYBOARD,
    KEYPAD,
    MULTI_AXIS,
    SYSTEM,
} dev_type;

#define SERIAL_BUFFER_LEN 256

void send_reset_cmd(void) {
    hid_info_cnt = 0;
    device_cnt = 0;

    uart_putchar('\n');
    _delay_ms(10);
    uart_putchar('k');
    uart_putchar('r');
    uart_putchar('\n');
}

bool parse_packet(uint8_t* buf, uint32_t cnt, matrix_row_t* current_matrix) {
    static uint8_t pre_keyreport[8];
    bool           matrix_has_changed = false;
    uint16_t       msg_len            = buf[LEN_L] | ((uint16_t)buf[LEN_H] << 8);

    // dprintf("Packet received:%d\n", msg_len);

    // validate packet length
    if (cnt < REPORT_START || msg_len != cnt - REPORT_START) {
        matrix_has_changed = false;
        return matrix_has_changed;
    }

    if (debug_enable) {
        print("Receive:");
        for (int idx = 0; idx < cnt; idx++) {
            xprintf("%02X ", buf[idx]);
        }
        xputc('\n');
    }

    switch (buf[MSG_TYP]) {
        case STARTUP:
            dprintf("CH559 start\n");
            ch559_start = true;
            break;

        case CONNECTED:
            device_cnt++;
            dprintf("Connected\n");
            break;

        case DISCONNECTED:
            device_cnt--;
            dprintf("Disconnected\n");
            for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS; rowIdx++) {
                if (current_matrix[rowIdx] != 0) {
                    matrix_has_changed     = true;
                    current_matrix[rowIdx] = 0;
                }
                memset(pre_keyreport, 0, sizeof(pre_keyreport));
            }
            break;

        case HID_INFO:
            hid_info_cnt++;
            break;

        case DEVICE_POLL:
            // dprintf("Report received\n");
            if (msg_len == 8 && buf[DEV_TYP] == KEYBOARD) {
                // accept only bootmode keyboard packet

                // dprintf("%d %d %d %d %d %d %d %d\n", buf[REPORT_START], buf[REPORT_START + 1], buf[REPORT_START + 2], buf[REPORT_START + 3], buf[REPORT_START + 4], buf[REPORT_START + 5], buf[REPORT_START + 6], buf[REPORT_START + 7]);

                if (memcmp(pre_keyreport, &buf[REPORT_START], sizeof(pre_keyreport)) == 0) {
                    // no change
                    matrix_has_changed = false;
                    break;
                } else {
                    matrix_has_changed = true;
                    memcpy(pre_keyreport, &buf[REPORT_START], sizeof(pre_keyreport));
                }

                // clear all bit
                for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS; rowIdx++) {
                    current_matrix[rowIdx] = 0;
                }

                // set bits
                for (uint8_t keyIdx = 0; keyIdx < 6; keyIdx++) {
                    uint8_t key    = buf[REPORT_START + keyIdx + 2];
                    uint8_t rowIdx = key / (sizeof(matrix_row_t) * 8);
                    uint8_t colIdx = key - rowIdx * (sizeof(matrix_row_t) * 8);
                    current_matrix[rowIdx] |= (1 << colIdx);
                }

                // modifier bits
                current_matrix[MATRIX_ROWS - 1] = buf[REPORT_START];
            }
            break;
    }

    return matrix_has_changed;
}

bool process_packet(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    bool receive_complete   = false;

    static uint8_t  buf[SERIAL_BUFFER_LEN];  // serial buffer
    static uint16_t widx     = 0;            // write index
    static bool     escaped  = false;        // escape flag
    static bool     overflow = false;        // overflow flag

    if (ch559UpdateMode) {
        return false;
    }

    while (uart_available()) {
        uint8_t c = uart_getchar();

        if (c == SLIP_END) {
            // dprintf("Detect END signal\n");
            if (overflow) {
                // reset receive buffer
                overflow         = false;
                receive_complete = false;
                widx             = 0;
                escaped          = false;
                memset(buf, 0, sizeof(buf));
            } else {
                receive_complete = true;
            }
            break;
        } else if (c == SLIP_ESC) {
            escaped = true;
        } else if (widx < sizeof(buf)) {
            if (escaped) {
                if (c == SLIP_ESC_END) {
                    buf[widx] = SLIP_END;
                } else if (c == SLIP_ESC_ESC) {
                    buf[widx] = SLIP_ESC;
                } else {
                    buf[widx] = c;
                }
                escaped = false;
            } else {
                buf[widx] = c;
            }

            widx++;
            if (widx > sizeof(buf)) {
                dprintf("Buffer overflow\n");
                overflow = true;
                widx     = 0;
            }
        }
    }

    if (receive_complete) {
        matrix_has_changed = parse_packet(buf, widx, current_matrix);

        receive_complete = false;
        widx             = 0;
        escaped          = false;
        overflow         = false;
        memset(buf, 0, sizeof(buf));
    }

    return matrix_has_changed;
}