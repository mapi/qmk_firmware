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

// Layer shorthand
#define QWERTY_LAYER 0
#define _FN 1
#define _LED 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY LAYER
 *  .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 *  | E/J     | 1       | 2       | 3       | 4       | 5       |         | \ / |   | 6       | 7       | 8       | 9       | 0       | - / =   | ^ / ~   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | TAB     | Q       | W       | E       | R       | T       |         |         | Y       | U       | I       | O       | P       | @ / `   | [ / {   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LCTRL   | A       | S       | D       | F       | G       |         | ESC     | H       | J       | K       | l       | ; / +   | : / *   | ] / }   |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LSHIFT  | Z       | X       | C       | V       | B       |         |         | N       | M       | , / <   | . / >   | / / ?   | \ / _   | RSHIFT  |
 *  |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 *  | LCTRL   |         | LWIN    | LALT    | BS      | SPACE   | MHEN    | HENK    | ENTER   | MO      |         | RALT    | APP     | RCTRL   | FN(LED) |
 *  '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */
  [QWERTY_LAYER] = {
    { JP_ZHTG,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  JP_YEN,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     JP_MINS,  JP_CIRC },
    { KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     JP_AT,    JP_LBRC },
    { KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  KC_ESC,   KC_H,     KC_J,     KC_K,     KC_L,     JP_SCLN,  JP_COLN,  JP_RBRC },
    { KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  KC_N,     KC_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,  KC_RSFT },
    { KC_LCTL,  XXXXXXX,  KC_LWIN,  KC_LALT,  KC_BSPC,  KC_SPC,   JP_MHEN,  JP_HENK,  KC_ENT,   XXXXXXX,  XXXXXXX,  KC_RALT,  KC_APP,   KC_RCTL,  MO(_LED)},
  },

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |         | F1      | F2      | F3      | F4      | F5      | F6      | F7      | F8      | F9      | F10     | F11     | F12     |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         | F13     | F14     | F15     | F16     | F17     | F18     | F19     | F20     | F21     | F22     | F23     | F24     |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         | MO(_FN) |         |         |         |         |         |         |         |         |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = { /* FUNCTION */
  { XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX, XXXXXXX  },
  { XXXXXXX,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,   XXXXXXX, XXXXXXX  },
  { _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  },
  { _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX, XXXXXXX  },
  { _______,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX, XXXXXXX  },
 },

/* LED
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |         | BL_ON   | BL_OFF  |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         | BL_INC  | BL_DEC  |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |         |         |         |         |         |         |         |         |         |         |         |         |         |         | FN(LED) |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_LED] = { /* LED */
  { XXXXXXX,  BL_ON,    BL_OFF,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  },
  { XXXXXXX,  BL_INC,   BL_DEC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  },
  { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  },
  { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX  },
  { XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, _______  },
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
