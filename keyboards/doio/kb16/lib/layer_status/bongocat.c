/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "quantum.h"
#include "../util.h"

#define IDLE_FRAMES 5
#define IDLE_FRAME_DURATION 300  // how long each frame lasts in ms
#define ANIM_SIZE 512  // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t curr_anim_duration = 0; // variable animation duration
uint32_t bongo_timer = 0;
uint8_t current_idle_frame = 0;

void render_bongocat(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
        {
        //Idle 1 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 2 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x9f, 0x9f, 0xff,
        0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1e, 0x1e, 0x3f, 0x3d, 0x3d, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0xf9, 0xf9, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 3 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x9f, 0x9f, 0xff,
        0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1e, 0x1e, 0x3f, 0x3d, 0x3d, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0xf9, 0xf9, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 4 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0,
        0xf0, 0xf8, 0xfc, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x1c, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        },
        {
        //Idle 5 - 128x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xce, 0x9c, 0xf8, 0xfc, 0xfe, 0x80, 0xe0, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
        0xf8, 0xfc, 0xfe, 0xff, 0xfe, 0xfc, 0xf8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x38, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0x31, 0x00, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0xff,
        0xff, 0xbf, 0x7f, 0x7f, 0xbf, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x06, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30, 0x38, 0x2c, 0x04, 0x64, 0xf8, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x8f, 0x27, 0x27, 0x27, 0xc7, 0xc7, 0x4f, 0x4f, 0x8f, 0x8f,
        0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0xfc, 0xfc, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30,
        0x60, 0x40, 0xc0, 0x86, 0x87, 0x85, 0xc4, 0x49, 0x69, 0x3e, 0x0e, 0x13, 0x11, 0x12, 0x12, 0x3d,
        0x2d, 0x25, 0x26, 0x44, 0x68, 0x78, 0x58, 0x9d, 0x97, 0x93, 0xe3, 0x62, 0x34, 0x3c, 0x2c, 0x26,
        0xc7, 0xc5, 0x69, 0x39, 0x19, 0x1d, 0x36, 0xa2, 0xe2, 0x62, 0x24, 0x18, 0x3c, 0x7e, 0x7f, 0x7f,
        0x7f, 0xbf, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0x63, 0x27, 0x27, 0x47, 0x47, 0xcf, 0xcf, 0x0f, 0x08,
        0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    if (timer_elapsed32(bongo_timer) > IDLE_FRAME_DURATION) {
        bongo_timer = timer_read32();
        current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
    }

    WRITE_RAW(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)]);
}
