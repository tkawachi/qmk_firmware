#include QMK_KEYBOARD_H

enum LAYER {
  _QW,
  _FN,
  _RS,
  _LW,
  _ADJUST
};

enum custom_keycords {
  LOWER = SAFE_RANGE,
  RAISE,
  // SQL keywords
  S_FROM,
  S_GROUP,
  S_HAVIN,
  S_INNER,
  S_LEFTJ,
  S_ORDER,
  S_PARTI,
  S_RIGHT,
  S_SELEC,
  S_UPDAT,
  S_WHERE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // qwerty (base)
	[_QW] = LAYOUT_all(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, _______, KC_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   MO(_FN),
        KC_ESC,  KC_LALT, KC_LGUI,                   LOWER,   KC_SPC,  RAISE,                     KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

  // FUNC
	[_FN] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

  // lower
	[_LW] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_DEL,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_LPRN, KC_RPRN, KC_PIPE, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_UNDS, _______, _______, KC_BSLS, _______, _______, _______, _______,
        _______, AG_NORM, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
    ),

  // raise
	[_RS] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        KC_GRV,  _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_0,    _______,  _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_4,    KC_5,    KC_6,    _______, _______, _______, _______,
        _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_1,    KC_2,    KC_3,    _______, _______, _______, _______,
        _______, AG_SWAP, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
    ),

  // adjust
	[_ADJUST] = LAYOUT_all(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, S_WHERE, _______, S_RIGHT, _______, _______, S_UPDAT, S_INNER, S_ORDER, S_PARTI, _______, _______, _______,
        _______, _______, S_SELEC, KC_MSTP, S_FROM,  S_GROUP, S_HAVIN, _______, _______, S_LEFTJ, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______, _______
    ),

};

static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;

#define TAPPING_TERM 200

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;
        layer_on(_LW);
        update_tri_layer(_LW, _RS, _ADJUST);
      } else {
        layer_off(_LW);
        update_tri_layer(_LW, _RS, _ADJUST);

        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG2);
          unregister_code(KC_LANG2);
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;
        layer_on(_RS);
        update_tri_layer(_LW, _RS, _ADJUST);
      } else {
        layer_off(_RS);
        update_tri_layer(_LW, _RS, _ADJUST);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG1);
          unregister_code(KC_LANG1);
          register_code(KC_HENK);
          unregister_code(KC_HENK);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case S_HAVIN:
      if (record->event.pressed) {
        SEND_STRING("HAVING ");
      }
      break;
    case S_GROUP:
      if (record->event.pressed) {
        SEND_STRING("GROUP BY ");
      }
      break;
    case S_SELEC:
      if (record->event.pressed) {
        SEND_STRING("SELECT ");
      }
      break;
    case S_FROM:
      if (record->event.pressed) {
        SEND_STRING("FROM ");
      }
      break;
    case S_INNER:
      if (record->event.pressed) {
        SEND_STRING("INNER JOIN ");
      }
      break;
    case S_ORDER:
      if (record->event.pressed) {
        SEND_STRING("ORDER BY ");
      }
      break;
    case S_PARTI:
      if (record->event.pressed) {
        SEND_STRING("PARTITION BY ");
      }
      break;
    case S_WHERE:
      if (record->event.pressed) {
        SEND_STRING("WHERE ");
      }
      break;
    case S_LEFTJ:
      if (record->event.pressed) {
        SEND_STRING("LEFT JOIN ");
      }
      break;
    case S_RIGHT:
      if (record->event.pressed) {
        SEND_STRING("RIGHT JOIN ");
      }
      break;
    case S_UPDAT:
      if (record->event.pressed) {
        SEND_STRING("UPDATE ");
      }
      break;
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
