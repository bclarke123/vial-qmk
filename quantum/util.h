// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2011 Jun Wako <wakojun@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "bitwise.h"

// convert to string
#define STR(s) XSTR(s)
#define XSTR(s) #s

#if !defined(MIN)
#    define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#if !defined(MAX)
#    define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
