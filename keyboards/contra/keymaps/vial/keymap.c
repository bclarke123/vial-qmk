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
  _WADS,
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

#    ifndef MIN
#        define MIN(a, b) ((a) < (b) ? (a) : (b))
#    endif

#    ifndef MAX
#        define MAX(a, b) ((a) > (b) ? (a) : (b))
#    endif

#    ifndef CLAMP
#        define CLAMP(a, b, c) MAX(b, MIN(c, a))
#    endif

bool change_color = false;

HSV get_layer_hsv(layer_state_t state) {
  HSV hsv = { HSV_BLACK };
  int layer = get_highest_layer(state);

  if (layer == _BASE) {
    hsv = (HSV){ HSV_BLACK };
  } else
  if (layer == _LOWER) {
    hsv = (HSV){ HSV_PURPLE };
    change_color = true;
  } else
  if (layer == _RAISE) {
    hsv = (HSV){ HSV_GOLD };
    change_color = true;
  } else
  if (layer == _ADJUST) {
    hsv = rgb_matrix_get_hsv();
    change_color = true;
  } else
  if (layer == _FUNC || layer == _WADS) {
    hsv = (HSV){ HSV_GREEN };
    change_color = true;
  } else
  if (layer >= _ARTSEY1 && layer <= _ARTSEY6) {
    hsv = (HSV){ HSV_ORANGE };
    change_color = true;
  }

  float val = rgb_matrix_get_val();
  hsv.v = MIN(hsv.v, val);

  return hsv;
}

void set_trackball(RGB rgb) {
  float _max = MAX(rgb.r, MAX(rgb.g, rgb.b));

  if (_max == 0) {
    pimoroni_trackball_set_rgbw(0, 0, 0, 0);
    return;
  }

  float _mult = 255.0 / _max;

  float hr = rgb.r * _mult;
  float hg = rgb.g * _mult;
  float hb = rgb.b * _mult;

  float hMax = MAX(hr, MAX(hg, hb));
  float hMin = MIN(hr, MIN(hg, hb));

  float w = ((hMax + hMin) / 2.0 - 127.5) * (255.0 / 127.5) / _mult;
  float r = CLAMP(rgb.r - w, 0.0, 255.0);
  float g = CLAMP(rgb.g - w, 0.0, 255.0);
  float b = CLAMP(rgb.b - w, 0.0, 255.0);

  pimoroni_trackball_set_rgbw(r, g, b, w);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  change_color = false;
  HSV hsv = get_layer_hsv(state);
  RGB rgb = hsv_to_rgb(hsv);
  set_trackball(rgb);

  return state;
}

void rgb_matrix_indicators_user(void) {
  if (change_color) {
    HSV hsv = get_layer_hsv(layer_state | default_layer_state);
    RGB rgb = hsv_to_rgb(hsv);

    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    set_trackball(rgb);
  }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
  int layer = get_highest_layer(layer_state | default_layer_state);
  return layer >= _ARTSEY1 && layer <= _ARTSEY6;
}
