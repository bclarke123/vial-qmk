#include "benpad.h"

// led_config_t g_led_config = { {
//     // Key Matrix to LED Index
// { 0, 1, 2, 3 },
// { 5, 6, 7 },
// { 10, 11, 12, 8 },
// { 15, 16, 17 },
// { 20, 21, 18}
// }, {
//     // LED Index to Physical Position
// {  0,  0}, { 56,  0}, {112,  0}, {168,  0}, {224,  0},
// {  0, 16}, { 56, 16}, {112, 16}, {168, 16}, {224, 16},
// {  0, 32}, { 56, 32}, {112, 32}, {168, 32}, {224, 32},
// {  0, 48}, { 56, 48}, {112, 48}, {168, 48}, {224, 48},
// {  0, 64}, { 56, 64}, {112, 64}, {168, 64}, {224, 64},
// }, {
//     // LED Index to Flag
// 2, 2, 2, 2, 8,
// 2, 2, 2, 2, 8,
// 2, 2, 2, 2, 8,
// 2, 2, 2, 2, 8,
// 2, 2, 2, 2, 8
// } };

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