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
#include <math.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Basic numpad
    [0] = LAYOUT(
        KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7, KC_P8, KC_P9,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3,
        KC_P0, KC_PDOT, KC_PENT)
};

void rgb_matrix_indicators_user() {
   led_t led_state = host_keyboard_led_state();
   // bool caps = led_state.caps_lock;
   bool num = led_state.num_lock;

   HSV hsv = rgb_matrix_get_hsv();
   float v = rgb_matrix_get_val();

   if (hsv.v > v) {
      hsv.v = v;
   }

   RGB rgb = hsv_to_rgb(hsv);

   if (num) {
      rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
   }

   int layer = get_highest_layer(layer_state | default_layer_state);
   int banks = floor(layer / 5);
   int slot = layer % 5;

   for (int i = 0; i < 5; i++) {
      int layer_led = (i + 1) * 5 - 1;

      if (slot == i) {
         rgb_matrix_set_color(layer_led, rgb.r, rgb.g, rgb.b);
      }
   }

   if (banks >= 1) {
      rgb_matrix_set_color(18, rgb.r, rgb.g, rgb.b);
   }

   if (banks >= 2) {
      rgb_matrix_set_color(23, rgb.r, rgb.g, rgb.b);
   }
}
