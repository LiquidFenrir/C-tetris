#pragma once

#include "common.h"

#define PIECES_AMOUNT 7
#define BLANK 0

typedef struct {
	char * color;
	uint8_t width;
	uint8_t height;
	uint16_t rotations[4];
} tetrimino;

extern tetrimino piecesTypes[PIECES_AMOUNT+1]; //+1 for the blank/no piece color
extern int currentPiece;
extern int nextPiece;
extern int currentPieceRotation;
extern int oldPiecePositions[4][2];

void generatePiecesTypes();
int randPiece();
bool spawnPieces();
