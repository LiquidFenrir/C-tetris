#include "timer.h"
#include "grid.h"

static int framesPerRowPerLevel[] = {
	53,
	49,
	45,
	41,
	37,
	33,
	28,
	22,
	17,
	11,
	10,
	9,
	8,
	7,
	6,
	6,
	5,
	5,
	4,
	4,
	3
};

timer gravityTimer;

void setupTimer()
{
	gravityTimer.startTime = clock();
	gravityTimer.endTime = gravityTimer.startTime + (framesPerRowPerLevel[level]*CLOCKS_PER_FRAME);
	gravityTimer.ended = false;
}

bool checkTimer()
{
    if (clock() > gravityTimer.endTime) gravityTimer.ended = true;
    return gravityTimer.ended;
}
