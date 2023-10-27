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

#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"

enum contra_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FUNC,
  _ARTSEY1,
  _ARTSEY2,
  _ARTSEY3,
  _ARTSEY4,
  _ARTSEY5,
  _ARTSEY6,
  _USER1,
  _USER2,
  _USER3,
  _USER4
};

enum custom_keycodes {
    BALL_SCR = USER00
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_mit(
    KC_ESC,      KC_Q,    KC_W,    KC_E,     KC_R,       KC_T,    KC_Y,    KC_U,         KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,      KC_A,    KC_S,    KC_D,     KC_F,       KC_G,    KC_H,    KC_J,         KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,     KC_Z,    KC_X,    KC_C,     KC_V,       KC_B,    KC_N,    KC_M,         KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL,     KC_LGUI, KC_LALT, BALL_SCR, MO(_LOWER), KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  )
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

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
bool change_color = false;

layer_state_t layer_state_set_user(layer_state_t state) {
  change_color = false;

  switch (get_highest_layer(state)) {
    case _BASE:
        r = g = b = 0;
        break;
    case _LOWER:
        r = 0;
        g = 90;
        b = 150;
        change_color = true;
        break;
    case _RAISE:
        r = 205;
        g = 140;
        b = 0;
        change_color = true;
        break;
    case _ADJUST:
        r = 80;
        g = 0;
        b = 191;
        change_color = true;
        break;
    default: //  for any other layers, or the default layer
        r = 0;
        g = 205;
        b = 15;
        change_color = true;
        break;
  }

  pimoroni_trackball_set_rgbw(r, g, b, 0);

  return state;
}

void rgb_matrix_indicators_user(void) {
  if (change_color) {
    rgb_matrix_set_color_all(r * 0.1, g * 0.1, b * 0.1);
  }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
  int layer = get_highest_layer(layer_state | default_layer_state);
  return layer >= _ARTSEY1 && layer <= _ARTSEY6;
}
