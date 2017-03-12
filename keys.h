#pragma once

#include "common.h"

#define KEY_ENTER (1 << 0)

#define KEY_X (1 << 1)
#define KEY_C (1 << 2)
#define KEY_V (1 << 3)

#define KEY_UP (1 << 8)
#define KEY_DOWN (1 << 9)
#define KEY_LEFT (1 << 10)
#define KEY_RIGHT (1 << 11)

int getKeys();
