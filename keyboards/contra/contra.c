#include "contra.h"

led_config_t g_led_config = { {
    // Key Matrix to LED Index
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 12, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
{0,  0}, 
{0,  32}, {20,  32}, {40,  32}, {60,  32}, {80,  32}, {100,  32}, {120,  32}, {140,  32}, {160,  32}, {180,  32}, {200,  32}, {220,  32},
{220,  64}, {200,  64}, {180,  64}, {160,  64}, {140,  64}, {120,  64}, {100,  64}, {80,  64}, {60,  64}, {40,  64}, {20,  64}, {0,  64}
}, {
    // LED Index to Flag
2, 
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };