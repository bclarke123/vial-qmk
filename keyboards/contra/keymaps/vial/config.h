/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xE7, 0xD1, 0xB6, 0xA3, 0x57, 0x2A, 0xF4, 0xFC}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 } 

#define DYNAMIC_KEYMAP_LAYER_COUNT 16

#define VIAL_COMBO_ENTRIES 42
#define COMBO_SHOULD_TRIGGER

#define USE_I2C
#define PIMORONI
#define PIMORONI_TRACKBALL_TIME_TO_MAX 1000
#define PIMORONI_TRACKBALL_LIFTOFF_DELAY 240
#define PIMORONI_TRACKBALL_RESET_DELAY 300
#define PIMORONI_TRACKBALL_SCALE 3
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
