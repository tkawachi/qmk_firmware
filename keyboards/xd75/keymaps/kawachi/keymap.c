/* Copyright 2017 Wunder
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
 *
 */

#include QMK_KEYBOARD_H


// Layer shorthand
enum LAYER{
  _QW,
  _RS,
  _LW,
  _ADJUST,
  _NUM
};

enum custom_keycords {
  LOWER = SAFE_RANGE,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  //qwerty layer(almost use default)
  [_QW] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, TG(_NUM),KC_BSPC, KC_ENT,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_WH_U, KC_HOME, KC_PGUP,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  KC_WH_D, KC_END,  KC_PGDN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, KC_WBAK, KC_UP,   KC_WFWD,
    KC_ESC,  KC_SPC,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  //LOWER
  [_LW] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, RESET,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  KC_ACL0, KC_PAUS, _______, _______,
    _______, _______, _______, KC_MS_U, _______, _______, _______, KC_MINS, KC_LPRN, KC_RPRN, KC_PIPE, KC_BTN1, _______, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_UNDS, _______, _______, KC_BSLS, KC_BTN2, _______, KC_VOLU, _______,
    _______, AG_SWAP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  ),

  //RAISE
  [_RS] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,
    _______, AG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  // ADJUST
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  // NUM
  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_COMM, KC_DOT
  )
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
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
