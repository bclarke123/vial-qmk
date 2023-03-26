#pragma once

#include "config_common.h"

#undef VENDOR_ID
#define VENDOR_ID 0xBE17

#undef PRODUCT_ID
#define PRODUCT_ID 0x0060

#undef DEVICE_VER
#define DEVICE_VER 0x0001

#undef MANUFACTURER
#define MANUFACTURER Ben

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* key matrix pins */
#define MATRIX_ROW_PINS { GP0 }
#define MATRIX_COL_PINS { GP1 }

// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define RGB_DI_PIN GP16
#define RGBLED_NUM 30
#define DRIVER_LED_TOTAL RGBLED_NUM
#define NOP_FUDGE 1

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5
