#include "grid.h"
#include "pieces.h"

static int coeff[4] = {40, 100, 300, 1200};

int score = 0;
int lines = 0;
int level = 0;

bool checkLines()
{
	int completeAmount = MAP_HEIGHT;
	int completeLines[MAP_HEIGHT];
	memset(completeLines, MAP_HEIGHT, 1);

	for (int i = 0; i < MAP_HEIGHT; i++) { //checking if the line/column is complete
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (grid[i][j] == 0) {
				completeLines[i] = 0;
				completeAmount--;
				break;
			}
		}
	}

	if (completeAmount == 0) return false; //if no lines/columns have been completed, skip resetting

	uint8_t newGrid[MAP_HEIGHT][MAP_WIDTH] = {0};
	uint8_t blankLine[MAP_WIDTH] = {0};
	int offset = 0;

	for (int i = MAP_HEIGHT; MAP_HEIGHT-i < MAP_HEIGHT; i--) { //resetting the lines/columns that are complete
        if (completeLines[i]) offset++;
        memcpy(&newGrid[i], &grid[i-offset], MAP_WIDTH);
	}

    memcpy(&grid, &newGrid, MAP_WIDTH*MAP_HEIGHT);

	lines += completeAmount;
	if (level < 20) level += (lines - level*10)/10;
	score += (coeff[completeAmount-1] * (level + 1));
	return true;
}

bool checkFall() //checks if the piece hit bottom/another already present piece
{
    for (int i = 0; i < 4; i++) {
		int x = oldPiecePositions[i][1];
		int y = oldPiecePositions[i][0];
		if (((y+1) >= MAP_HEIGHT) || (grid[y+1][x] != BLANK)) {
			for (int i = 0; i < 4; i++) {
				int x = oldPiecePositions[i][1];
				int y = oldPiecePositions[i][0];
				grid[y][x] = currentPiece;
			}
			memset(oldPiecePositions, -1, sizeof(int)*4*2);
			return true;
		}
    }

    return false;
}

bool checkBounds()
{
	int newPiecePosition[4][2];
	int poscount = 0;

	for (int i = 0; i < 16; i++) {
		int x = i % 4;
		x += xpos;
        int y = i / 4;
        y += ypos;
        if (GETBIT(piecesTypes[currentPiece].rotations[currentPieceRotation], (15-i))) {
			newPiecePosition[poscount][0] = y;
			newPiecePosition[poscount][1] = x;
			poscount++;
        }
	}

	for (int i = 0; i < 4; i++) {
        int x = newPiecePosition[i][1];
		int y = newPiecePosition[i][0];
		if ((grid[y][x] != BLANK) || (x < 0) || (x > MAP_WIDTH-1)) return false;
	}

	return true; //no problem
}
