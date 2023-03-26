MCU = RP2040
BOOTLOADER = rp2040

BOARD = GENERIC_RP_RP2040

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
RGBLIGHT_ENABLE = no
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = vendor