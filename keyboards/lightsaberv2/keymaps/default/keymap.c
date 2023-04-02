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

#define LED_RED GP17
#define LED_GREEN	GP16
#define LED_BLUE GP25

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_A,  KC_B, KC_C)
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   bool down = record->event.pressed;

   if (down) {
      rgb_matrix_enable();
   } else {
      rgb_matrix_disable();
   }

   switch (keycode) {
      case KC_A:
         doWritePin(LED_BLUE, down);
      break;
      case KC_B:
         doWritePin(LED_GREEN, down);
         if (down) {
            rgb_matrix_step();
         }
      break;
      case KC_C:
         doWritePin(LED_RED, down);
         if (down) {
            rgb_matrix_increase_hue();
         }
      break;
   }

   return false;
}
