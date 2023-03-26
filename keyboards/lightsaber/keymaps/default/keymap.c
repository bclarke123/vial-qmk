/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
#include "quantum.h"

enum ls_keycodes {
   BTN = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(BTN)
};

void doWritePin(pin_t pin, bool high) {
   ATOMIC_BLOCK_FORCEON {
      setPinOutput(pin);
      if (high) {
         writePinHigh(pin);
      } else {
         writePinLow(pin);
      }
   }
}

void keyboard_post_init_user(void) {
   rgb_matrix_set_color_all(RGB_PURPLE);
   doWritePin(GP25, false);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

   bool down = record->event.pressed;
   doWritePin(GP25, down);

   if (down) {
      rgb_matrix_set_color_all(RGB_PURPLE);
      rgb_matrix_enable();
   } else {
      rgb_matrix_disable();
   }

   return false;
}
