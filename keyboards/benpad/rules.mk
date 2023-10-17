# MCU name
MCU = RP2040
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover	
MIDI_ENABLE = yes

# Disable unsupported hardware

# Audio output
AUDIO_SUPPORTED = no
AUDIO_ENABLE = no

# Enable keyboard backlight functionality
BACKLIGHT_SUPPORTED = no
BACKLIGHT_ENABLE = no

# Disable RGBLIGHT to use RGB_MATRIX
RGBLIGHT_SUPPORTED = no
RGBLIGHT_ENABLE = no

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = vendor
