/* This program is free software: you can redistribute it and/or modify
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

<<<<<<< HEAD
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"

enum contra_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER5,
  _LAYER6,
  _LAYER7,
  _LAYER8
};

enum custom_keycodes {
    BALL_SCR = SAFE_RANGE
=======

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
>>>>>>> ec5db760f9 ([Keymap] Add keymap for Contra 40% (#351))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Adjst| Ctrl | Gui  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
   * `-----------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT_planck_mit(
<<<<<<< HEAD
    KC_ESC,      KC_Q,    KC_W,    KC_E,     KC_R,       KC_T,    KC_Y,    KC_U,         KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,      KC_A,    KC_S,    KC_D,     KC_F,       KC_G,    KC_H,    KC_J,         KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,     KC_Z,    KC_X,    KC_C,     KC_V,       KC_B,    KC_N,    KC_M,         KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL,     KC_LGUI, KC_LALT, BALL_SCR, MO(_LOWER), KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
=======
    KC_ESC,      KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,         KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,         KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M,         KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    MO(_ADJUST), KC_LCTL, KC_LGUI, KC_LALT, MO(_LOWER),     KC_SPC,       MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
>>>>>>> ec5db760f9 ([Keymap] Add keymap for Contra 40% (#351))
  ),

  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
<<<<<<< HEAD
   * |      |      |      | TO 5 |      |             |      | Next | Vol- | Vol+ | Play |
=======
   * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
>>>>>>> ec5db760f9 ([Keymap] Add keymap for Contra 40% (#351))
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_mit(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    _______,    KC_HOME, KC_END,  _______,
<<<<<<< HEAD
    _______, _______, _______, TO(_LAYER5), _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
=======
    _______, _______, _______, _______, _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
>>>>>>> ec5db760f9 ([Keymap] Add keymap for Contra 40% (#351))
  ),

  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |Pg Up |Pg Dn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_mit(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______,     _______,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  /* Adjust
   * ,----------------------------------------------------------- ------------------------.
   * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_planck_mit(
    _______, QK_BOOT,   DB_TOGG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  ),

  /* Layer 5 */
  [_LAYER5] = LAYOUT_planck_mit(
    _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, TO(_LAYER6), _______,     _______,      TO(_BASE), _______, _______, _______, _______
  ),

  /* Layer 6 */
  [_LAYER6] = LAYOUT_planck_mit(
    _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, TO(_LAYER7), _______,     _______,      TO(_LAYER5), _______, _______, _______, _______
  ),

  /* Layer 7 */
  [_LAYER7] = LAYOUT_planck_mit(
    _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, TO(_LAYER8), _______,     _______,      TO(_LAYER6), _______, _______, _______, _______
  ),

  /* Layer 8 */
  [_LAYER8] = LAYOUT_planck_mit(
    _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, TO(_BASE), _______,     _______,      TO(_LAYER7), _______, _______, _______, _______
  ),
};

void keyboard_post_init_user(void) {
    pimoroni_trackball_set_rgbw(0,0,0,0);
}

bool set_scrolling = false;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x * 0.3;
        mouse_report.v = mouse_report.y * 0.3;
        mouse_report.x = mouse_report.y = 0; 
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == BALL_SCR) {
    set_scrolling = record->event.pressed;

    if (set_scrolling) {
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);
    }
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BASE:
        pimoroni_trackball_set_rgbw(0,0,0,0);
        break;
    case _LOWER:
        pimoroni_trackball_set_rgbw(0,90,150,0);
        break;
    case _RAISE:
        pimoroni_trackball_set_rgbw(205,140,0,0);
        break;
    default: //  for any other layers, or the default layer
        pimoroni_trackball_set_rgbw(0,205,15,0);
        break;
    }
  return state;
}
