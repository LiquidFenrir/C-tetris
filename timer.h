#pragma once

#include "common.h"

#define MULT 1.5 //1 for normal fall speed, higher for easier
#define FRAMES_PER_SECOND 60
#define CLOCKS_PER_FRAME CLOCKS_PER_SEC/FRAMES_PER_SECOND*MULT

typedef struct {
    clock_t startTime;
    clock_t endTime;
    bool ended;
} timer;

extern timer gravityTimer;

void setupTimer();
bool checkTimer();
