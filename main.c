#include "common.h"
#include "draw.h"
#include "grid.h"
#include "keys.h"
#include "pieces.h"
#include "timer.h"

uint8_t grid[MAP_HEIGHT][MAP_WIDTH] = {0};
int xpos = SPAWN_X;
int ypos = 0;

int main()
{
	generatePiecesTypes();
	nextPiece = randPiece();

	drawStaticInterface();

	spawnPieces();

	setupTimer();

	draw:
	drawScore();
	drawGrid();
	drawNextPiece();
	drawCurrentPiece();


	while (true) {

		if (checkFall()) {
			setupTimer();
			currentPieceRotation = 0;
			if (!spawnPieces()) break;
			goto draw;
		}

		if (checkLines()) {
            setupTimer();
			goto draw;
		}

		if (checkTimer()) { //gravity
			ypos++;
			score += 4;
			setupTimer();
			goto draw;
		}

		if (getKeys() == KEY_ENTER) break;
		else if (getKeys() == KEY_X) {
			currentPieceRotation--;
			if (currentPieceRotation < 0) currentPieceRotation = 3;
			if (!checkBounds()) currentPieceRotation++;
			if (currentPieceRotation > 3) currentPieceRotation = 0;
			goto draw;
		}
		else if (getKeys() == KEY_C) {
			currentPieceRotation++;
			if (currentPieceRotation > 3) currentPieceRotation = 0;
			if (!checkBounds()) currentPieceRotation--;
			if (currentPieceRotation < 0) currentPieceRotation = 3;
			goto draw;
		}
		else if (getKeys() == KEY_LEFT) {
            xpos--;
            score += xpos+4;
            if (!checkBounds()) xpos++;
            score -= xpos;
            goto draw;
		}
		else if (getKeys() == KEY_RIGHT) {
			xpos++;
			if (!checkBounds()) xpos--;
			goto draw;
		}
		else if (getKeys() == KEY_UP) { //soft drop
            gravityTimer.ended = true;
		}
	}

	return 0;
}
