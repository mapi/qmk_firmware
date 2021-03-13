#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#define _BASE 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1, \
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, XXXXXXX,    KC_9, KC_8, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1  \
)
};
