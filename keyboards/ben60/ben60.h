#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, \
    k40, k41, k42,           k45,                k49, k4A, k4B, k4C, k4D \
) { \
    { k00, k02, k04, k06, k08, k0A, k0C }, \
    { k01, k03, k05, k07, k09, k0B, k0D }, \
    { k10, k12, k14, k16, k18, k1A, k1C }, \
    { k11, k13, k15, k17, k19, k1B, k1D }, \
    { k20, k22, k24, k26, k28, k2A, k2C }, \
    { k21, k23, k25, k27, k29, k2B, KC_NO }, \
    { k30, k32, k34, k36, k38, k3A, k3C }, \
    { k31, k33, k35, k37, k39, k3B, k3D }, \
    { k40, k42, KC_NO, KC_NO, k49, k4B, k4D }, \
    { k41, KC_NO, k45, KC_NO, KC_NO, k4A, k4C } \
}
