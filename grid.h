#pragma once

#include "common.h"

extern int score;
extern int lines;
extern int level; //increases by 1 for every 10 lines completed, max 20

bool checkLines();
bool checkFall();
bool checkBounds();
