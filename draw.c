#include "draw.h"
#include "pieces.h"
#include "grid.h"

static void drawCorners()
{
	printf("\x1b[%i;%iH*", Y_OFFSET, X_OFFSET);
	printf("\x1b[%i;%iH*", Y_OFFSET+MAP_HEIGHT+1, X_OFFSET);
	printf("\x1b[%i;%iH*", Y_OFFSET, X_OFFSET+MAP_WIDTH+1);
	printf("\x1b[%i;%iH*", Y_OFFSET+MAP_HEIGHT+1, X_OFFSET+MAP_WIDTH+1);
}

static void drawBorders()
{
	for (int i = 0; i < MAP_WIDTH; i++) {
		printf("\x1b[%i;%iH-", Y_OFFSET, X_OFFSET+i+1);
		printf("\x1b[%i;%iH-", Y_OFFSET+MAP_HEIGHT+1, X_OFFSET+i+1);
	}

	for (int i = 0; i < MAP_HEIGHT; i++) {
		printf("\x1b[%i;%iH|", i+Y_OFFSET+1, X_OFFSET);
		printf("\x1b[%i;%iH|", i+Y_OFFSET+1, X_OFFSET+MAP_WIDTH+1);
	}
}

static void drawNextPieceCorners()
{
	printf("\x1b[%i;%iH*", Y_OFFSET, X_OFFSET+MAP_WIDTH+6);
	printf("\x1b[%i;%iH*", Y_OFFSET+5, X_OFFSET+MAP_WIDTH+6);
	printf("\x1b[%i;%iH*", Y_OFFSET, X_OFFSET+MAP_WIDTH+11);
	printf("\x1b[%i;%iH*", Y_OFFSET+5, X_OFFSET+MAP_WIDTH+11);
}

static void drawNextPieceBorders()
{
	for (int i = 0; i < 4; i++) {
		printf("\x1b[%i;%iH-", Y_OFFSET, X_OFFSET+MAP_WIDTH+i+7);
		printf("\x1b[%i;%iH-", Y_OFFSET+5, X_OFFSET+MAP_WIDTH+i+7);
		printf("\x1b[%i;%iH|", i+Y_OFFSET+1, X_OFFSET+MAP_WIDTH+6);
		printf("\x1b[%i;%iH|", i+Y_OFFSET+1, X_OFFSET+MAP_WIDTH+11);
	}
}

void drawStaticInterface()
{
	system("cls");
	printf("\x1b[?25l"); //disable the blinking cursor
	drawNextPieceBorders();
	drawNextPieceCorners();
	drawBorders();
	drawCorners();
}

void drawGrid()
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			printf("\x1b[%i;%iH%s \x1b[0m", i+Y_OFFSET+1, j+X_OFFSET+1, piecesTypes[grid[i][j]].color);
		}
	}
}

void drawNextPiece()
{
	for (int i = 0; i < 16; i++) {
		int x = i % 4;
		x += X_OFFSET+MAP_WIDTH+7;
        int y = i / 4;
        y += Y_OFFSET+1;
		printf("\x1b[%i;%iH%s \x1b[0m", y, x, GETBIT(piecesTypes[nextPiece].rotations[0], (15-i)) ? piecesTypes[nextPiece].color : piecesTypes[BLANK].color);
	}
}

void drawCurrentPiece()
{
	for (int i = 0; i < 4; i++) { //clears the previous position of the falling tetrimino

        printf("\x1b[%i;%iH%s ", oldPiecePositions[i][0]+Y_OFFSET+1, oldPiecePositions[i][1]+X_OFFSET+1, piecesTypes[BLANK].color);
	}
	int poscount = 0;
	for (int i = 0; i < 16; i++) {
		int drawx = i % 4;
		drawx += X_OFFSET+1+xpos;
        int drawy = i / 4;
        drawy += Y_OFFSET+1+ypos;
        if (GETBIT(piecesTypes[currentPiece].rotations[currentPieceRotation], (15-i))) {
			printf("\x1b[%i;%iH%s \x1b[0m", drawy, drawx, piecesTypes[currentPiece].color);
			oldPiecePositions[poscount][0] = drawy-Y_OFFSET-1;
			oldPiecePositions[poscount][1] = drawx-X_OFFSET-1;
			poscount++;
        }
	}
}

void drawScore()
{
	printf("\x1b[%i;%iHScore:", Y_OFFSET+7, X_OFFSET+MAP_WIDTH+6);
	printf("\x1b[%i;%iH%i", Y_OFFSET+8, X_OFFSET+MAP_WIDTH+6, score);

	printf("\x1b[%i;%iHLines:", Y_OFFSET+10, X_OFFSET+MAP_WIDTH+6);
	printf("\x1b[%i;%iH%i", Y_OFFSET+11, X_OFFSET+MAP_WIDTH+6, lines);

	printf("\x1b[%i;%iHLevel:", Y_OFFSET+13, X_OFFSET+MAP_WIDTH+6);
	printf("\x1b[%i;%iH%i", Y_OFFSET+14, X_OFFSET+MAP_WIDTH+6, level);
}
