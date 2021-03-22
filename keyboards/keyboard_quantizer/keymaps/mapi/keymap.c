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
#include QMK_KEYBOARD_H
#include "keymap_jp.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _MOD1,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    A_TAB = SAFE_RANGE,
    A_S_TAB,
    MY_SCLN,
    MY_COLN,
};

/* Original Layout(from upstream micro controller)
 * LAYOUT(
 *    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4,     KC_F5, KC_F6, KC_F7, KC_F8,     KC_F9, KC_F10, KC_F11, KC_F12,    KC_PSCR, KC_SCROLLLOCK, KC_PAUS,
 *    JP_ZKHK, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, JP_MINS, JP_CIRC, JP_YEN, KC_BSPACE, KC_INSERT, KC_HOME, KC_PGUP,       KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
 *    KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, JP_AT, JP_LBRC,           KC_ENT,   KC_DEL, KC_END,  KC_PGDN,          KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS,
 *    KC_CAPS,   KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, JP_SCLN, JP_COLN, JP_RBRC,                                                  KC_KP_4, KC_KP_5, KC_KP_6,
 *    KC_LSFT,    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, JP_SLSH, JP_BSLS, KC_RSFT,                 KC_UP,                     KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
 *    KC_LCTRL, KC_LGUI, KC_LALT, JP_MHEN, KC_SPC, JP_HENK, JP_KANA, KC_RALT, KC_RGUI, KC_APP, KC_RCTRL,            KC_LEFT,  KC_DOWN, KC_RIGHT,       KC_KP_0,          KC_KP_DOT
 *   )
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] =  LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4,     KC_F5, KC_F6, KC_F7, KC_F8,     KC_F9, KC_F10, KC_F11, KC_F12,    KC_PSCR, KC_SCROLLLOCK, KC_PAUS,
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, JP_MINS, JP_CIRC, JP_YEN, KC_BSPACE, KC_INSERT, KC_HOME, KC_PGUP,       KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, JP_AT, JP_LBRC,           KC_ESC,   KC_DEL, KC_END,  KC_PGDN,          KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS,
    KC_LCTRL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, MY_COLN, JP_RBRC,                                                  KC_KP_4, KC_KP_5, KC_KP_6,
    KC_LSFT,    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, JP_SLSH, JP_BSLS, KC_RSFT,                 KC_UP,                     KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,
    KC_LCTRL, KC_LGUI, KC_LALT, KC_BSPACE, KC_SPC, MO(_MOD1), JP_ZKHK, KC_RALT, KC_RGUI, KC_APP, KC_RCTRL,            KC_LEFT,  KC_DOWN, KC_RIGHT,       KC_KP_0,          KC_KP_DOT
    ),

    /* MOD1 **/
    [_MOD1] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, LALT(KC_F4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, A_S_TAB, XXXXXXX, A_TAB,   XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, MY_SCLN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, _______, KC_DEL,  XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
// clang-format on


uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    // A_TAB, A_S_TAB を連打した時用
    static bool atab_registered;
    if (keycode == A_TAB) {
        if (record->event.pressed) {
            register_code(KC_LALT);
            atab_registered = true;
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        return false;
    } else if (keycode == A_S_TAB) {
        if (record->event.pressed) {
            register_code(KC_LALT);
            atab_registered = true;
            register_code16(LSFT(KC_TAB));
        } else {
            unregister_code16(LSFT(KC_TAB));
        }
        return false;
    } else {
        if (atab_registered) {
            unregister_code(KC_LALT);
            atab_registered = false;
        }
    }

    switch (keycode) {
        case MY_COLN:
            {
            static bool my_coln_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(JP_COLN);
                    my_coln_registered = true;
                    set_mods(mod_state);
                } else {
                    register_code(JP_SCLN);
                }
            } else {
                if (my_coln_registered) {
                    unregister_code(JP_COLN);
                    my_coln_registered = false;
                } else {
                    unregister_code(JP_SCLN);
                }
            }
            return false;
        }
        case MY_SCLN:
            {
            static bool my_scln_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    register_code16(LSFT(JP_SCLN));
                    my_scln_registered = true;
                } else {
                    register_code16(LSFT(JP_COLN));
                }
            } else {
                if (my_scln_registered) {
                    unregister_code16(LSFT(JP_SCLN));
                    my_scln_registered = false;
                } else {
                    unregister_code16(LSFT(JP_COLN));
                }
            }
            return false;
        }
        default:
            return true;
    }
};

#ifdef OLED_DRIVER_ENABLE
#    include "rev1.h"
#    include "oled_driver.h"
#endif

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) { render_logo(); }
#endif
