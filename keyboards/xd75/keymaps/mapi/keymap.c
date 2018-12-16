/* Copyright 2018 mapi
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
#include "keymap_jp.h"
#include "xd75.h"

static bool led_blink = false;
static uint16_t led_blink_timer = 0;

// Layer shorthand
enum layers {
  _QWERTY = 0,
  _MODKEY,
  _FUNCKEY,
  _LED,
};

// Key combination shorthand
#define ALTF4 LALT(KC_F4)
// for Chrome Browser
#define FTAB LCTL(KC_PGUP) // Forward Tab
#define BTAB LCTL(KC_PGDN) // Back Tab
#define CTAB LCTL(KC_F4) // Close Tab
#define ROTAB LCTL(LSFT(KC_T))  // Reopen Close Tab

enum custom_keycodes {
  MOD1 = SAFE_RANGE,
  ATAB,
  ASTAB,
  FUNC_ON,
  FUNC_OFF,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOD1:
      if (record->event.pressed) {
        layer_on(_MODKEY);
      } else {
        clear_mods();
        layer_off(_MODKEY);
      }
      break;
    case ATAB:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_TAB);
      }
      break;
    case ASTAB:
      if (record->event.pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
      break;
    case FUNC_ON:
      if (record->event.pressed) {
        layer_on(_FUNCKEY);
        led_blink = true;
      }
      break;
    case FUNC_OFF:
      if (record->event.pressed) {
        led_blink = false;
        clear_mods();
        backlight_level(6);
        layer_off(_FUNCKEY);
      }
      break;
  }
  return true;
};

void matrix_scan_user(void) {
  // blink backlight LED while function layer enabled.
  if (led_blink) {
    if (timer_elapsed(led_blink_timer) > 300) {
      if (get_backlight_level() == 0) {
        backlight_level(6);
      } else {
        backlight_level(0);
      }
      led_blink_timer = timer_read();
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY LAYER
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 *  | E/J     | 1       | 2       | 3       | 4       | 5       |         | \ / |   | 6       | 7       | 8       | 9       | 0       | - / =   | ^ / ~   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | TAB     | Q       | W       | E       | R       | T       |         | PrtSc   | Y       | U       | I       | O       | P       | @ / `   | [ / {   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LCTRL   | A       | S       | D       | F       | G       | PgUp    | ESC     | H       | J       | K       | L       | ; / +   | : / *   | ] / }   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LSHIFT  | Z       | X       | C       | V       | B       | PgDn    |         | N       | M       | , / <   | . / >   | / / ?   | \ / _   | RSHIFT  |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LCTRL   |         | LWIN    | LALT    | BS      | SPACE   | MHEN    | HENK    | ENTER   | MOD1    |         | RALT    | APP     | RCTRL   | FN(LED) |
 *  '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_QWERTY] = {
    { JP_ZHTG,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  JP_YEN,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     JP_MINS,  JP_CIRC },
    { KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  KC_PSCR,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     JP_AT,    JP_LBRC },
    { KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_PGUP,  KC_ESC,   KC_H,     KC_J,     KC_K,     KC_L,     JP_SCLN,  JP_COLN,  JP_RBRC },
    { KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_PGDN,  FUNC_ON,  KC_N,     KC_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,  KC_RSFT },
    { KC_LCTL,  XXXXXXX,  KC_LWIN,  KC_LALT,  KC_BSPC,  KC_SPC,   JP_MHEN,  JP_HENK,  KC_ENT,   MOD1,     XXXXXXX,  KC_RALT,  KC_APP,   KC_RCTL,  MO(3)   },
  },

/* MODKEY LAYER
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         | AltF4   |         |         |         |         | CTAB    | ROTAB   |         | HOME    | UP      | END     |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | PASS    |         | AltTab- |         | AltTab  |         | FTAB    |         |         | LEFT    | DOWN    | RIGHT   |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | PASS    |         |         |         |         |         | BTAB    |         |         | KC_WBAK | KC_WFWD |         |         |         | PASS    |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | PASS    |         | PASS    | PASS    | DEL     |         |         |         |         | PASS    |         | PASS    |         | PASS    |         |
 *  '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_MODKEY] = {
    { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { XXXXXXX,  ALTF4,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CTAB,     ROTAB,    XXXXXXX,  KC_HOME,  KC_UP,    KC_END,   XXXXXXX,  XXXXXXX,  XXXXXXX },
    { _______,  XXXXXXX,  ASTAB,    XXXXXXX,  ATAB,     XXXXXXX,  FTAB,     XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RIGHT, XXXXXXX,  XXXXXXX,  XXXXXXX },
    { _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  BTAB,     XXXXXXX,  XXXXXXX,  KC_WBAK,  KC_WFWD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______ },
    { _______,  XXXXXXX,  _______,  _______,  KC_DEL,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX },
  },

/* FUNCTION KEY LAYER
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 *  |         | F1      | F2      | F3      | F4      | F5      | F6      | F7      | F8      | F9      | F10     | F11     | F12     |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         | F13     | F14     | F15     | F16     | F17     | F18     | F19     | F20     | F21     | F22     | F23     | F24     |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         | MO(_FN) |         |         |         |         |         |         |         |         |
 *  '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FUNCKEY] = {
    { XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    XXXXXXX,  XXXXXXX,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12  },
    { XXXXXXX,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   XXXXXXX,  XXXXXXX,  KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24  },
    { _______,  KC_1,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  FUNC_OFF, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX },
    { _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX },
  },

/* LED
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 *  |         | BL_ON   | BL_OFF  |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         | BL_INC  | BL_DEC  |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  |         |         |         |         |         |         |         |         |         |         |         |         |         |         | FN(LED) |
 *  '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_LED] = {
    { XXXXXXX,  BL_ON,    BL_OFF,   BL_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { XXXXXXX,  BL_INC,   BL_DEC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX },
    { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______ },
  }
};

const uint16_t PROGMEM fn_actions[] = {

};
