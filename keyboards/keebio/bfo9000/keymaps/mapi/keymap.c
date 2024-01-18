#include QMK_KEYBOARD_H
#include "keymap_japanese.h"


// keyboard layouts
enum layers {
    _BASE = 0,
    _MOD1,
    _MOD2,
    _XXXX,
};


// Custom Keycords
enum custom_keycodes {
    ATAB = SAFE_RANGE,
    ASTAB,
    CK1,  // semicolon, shift: colon
    CK2,  // asterisk, shift: plus
};

// Key combination short hand.
#define ALTF4 LALT(KC_F4)
#define TAB_N LCTL(KC_TAB)
#define TAB_P LSFT(TAB_N)
#define S_INS LSFT(KC_INS)
#define C_INS LCTL(KC_INS)

struct ck1_key_state {
    bool normal;
    bool shift;
};
static struct ck1_key_state ck1_state;

// 良い感じに alt-tab する
static bool is_window_switching = false;
bool window_switch(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case ATAB:
            if (record->event.pressed) {
                is_window_switching = true;
                register_code(KC_LALT);
                tap_code(KC_TAB);
            }
            return false;
        case ASTAB:
            if (record->event.pressed) {
                is_window_switching = true;
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            return false;
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RIGHT:
            return true;
        case MO(_MOD1):
            if (!record->event.pressed) {
                unregister_code(KC_LALT);
                is_window_switching = false;
                return true;
            }
        default:
            unregister_code(KC_LALT);
            is_window_switching = false;
            return false;
    }
}


uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();

    if (is_window_switching) {
        return window_switch(keycode, record);
    }

    switch (keycode) {
        case ATAB:
        case ASTAB:
            return window_switch(keycode, record);
        case CK1:
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    // シフト押しながらだとコロン(JP_COLN)
                    del_mods(MOD_MASK_SHIFT);
                    register_code(JP_COLN);
                    set_mods(mod_state);
                    ck1_state.shift = true;
                } else {
                    // 普通に押すとセミコロン(JP_SCLN)
                    register_code(JP_SCLN);
                    ck1_state.normal = true;
                }
            } else {
                if (ck1_state.normal) {
                    unregister_code(JP_SCLN);
                    ck1_state.normal = false;
                }
                if (ck1_state.shift) {
                    unregister_code(JP_COLN);
                    ck1_state.shift = false;
                }
            }
            return false;
        case CK2:
            if (mod_state & MOD_MASK_SHIFT) {
                // シフト押しながらだと + (S(JP_SCLN))
                if (record->event.pressed) {
                   register_code(JP_SCLN);
                } else {
                   unregister_code(JP_SCLN);
                }
            } else {
                // 普通に押すと * (S(JP_COLN))
                add_mods(MOD_MASK_SHIFT);
                if (record->event.pressed) {
                   register_code(JP_COLN);
                } else {
                   unregister_code(JP_COLN);
                }
                set_mods(mod_state);
            }
            return false;
        default:
            return true;
    }

    return true;
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( \
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,     XXXXXXX, XXXXXXX,    XXXXXXX, KC_F7,  KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, XXXXXXX, \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,      XXXXXXX, XXXXXXX,    XXXXXXX, KC_7,   KC_8,      KC_9,    KC_0,    JP_MINS, JP_CIRC, JP_YEN,  XXXXXXX, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   XXXXXXX,   XXXXXXX, XXXXXXX,    XXXXXXX, KC_Y,   KC_U,      KC_I,    KC_O,    KC_P,    JP_AT,   JP_LBRC, XXXXXXX, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_WBAK,   KC_WFWD, XXXXXXX,    XXXXXXX, KC_H,   KC_J,      KC_K,    KC_L,    KC_ENT,  CK1,     JP_RBRC, KC_ESC, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   XXXXXXX,   XXXXXXX, XXXXXXX,    XXXXXXX, KC_N,   KC_M,      JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS, KC_UP,   XXXXXXX, \
    KC_DEL,  KC_LWIN, XXXXXXX, KC_LALT, KC_BSPC, KC_SPC, MO(_MOD2), KC_ESC,  XXXXXXX,    XXXXXXX, KC_SPC, MO(_MOD1), JP_ZKHK, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT \
),

[_MOD1] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, ALTF4,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, C_INS,   KC_HOME, KC_UP,   KC_END,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, ASTAB  , XXXXXXX, ATAB,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, S_INS,   KC_LEFT, KC_DOWN, KC_RIGHT, CK2,     XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, TAB_P,   XXXXXXX, TAB_N,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_DEL,  _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

[_MOD2] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),


// blank layout
[_XXXX] = LAYOUT( \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),
};
