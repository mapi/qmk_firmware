#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

#define _BASE 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( \
    KC_0, KC_ESC,  KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_0, XXXXXXX,    KC_0, KC_F6,  KC_F7, KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_0, \
    KC_0, JP_ZKHK, KC_1,  KC_2,    KC_3,    KC_4,    KC_5,   KC_0, XXXXXXX,    KC_0, KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    JP_MINS, JP_CIRC, JP_YEN, \
    KC_0, KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,   KC_0, XXXXXXX,    KC_0, KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    JP_AT,   JP_LBRC, KC_0, \
    KC_0, KC_LCTL, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,   KC_0, XXXXXXX,    KC_0, KC_H,   KC_J,  KC_K,    KC_L,   JP_SCLN, JP_COLN, JP_RBRC, KC_0, \
    KC_0, KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,   KC_0, XXXXXXX,    KC_0, KC_N,   KC_M,  JP_COMM, JP_DOT, JP_SLSH, JP_BSLS, KC_0,    KC_0, \
    KC_0, KC_0,    KC_0,  KC_LWIN, KC_LALT, KC_BSPC, KC_SPC, KC_0, XXXXXXX,    KC_0, KC_SPC, KC_0,  JP_ZKHK, KC_0,   KC_0,    KC_0,    KC_0,    KC_0  \
)
};
