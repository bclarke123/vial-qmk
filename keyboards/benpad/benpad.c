#include "benpad.h"

led_config_t g_led_config = { {
    // Key Matrix to LED Index
{ NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED }
}, {
    // LED Index to Physical Position
{0,  0}
}, {
    // LED Index to Flag
2
} };