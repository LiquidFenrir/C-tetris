#include <time.h>
#include <math.h>
#include "pieces.h"

tetrimino piecesTypes[PIECES_AMOUNT+1];
int currentPiece = 0;
int nextPiece = 0;
int currentPieceRotation = 0;

int oldPiecePositions[4][2];

void generatePiecesTypes()
{
	memset(oldPiecePositions, -1, sizeof(int)*4*2);

	piecesTypes[0].color = "\x1b[40m";

	//I - barre verticale
	piecesTypes[1].color = "\x1b[46m";
    piecesTypes[1].rotations[0] = 0x0F00;
    piecesTypes[1].rotations[1] = 0x2222;
    piecesTypes[1].rotations[2] = 0x00F0;
    piecesTypes[1].rotations[3] = 0x4444;

	//J
	piecesTypes[2].color = "\x1b[44m";
    piecesTypes[2].rotations[0] = 0x8E00;
    piecesTypes[2].rotations[1] = 0x6440;
    piecesTypes[2].rotations[2] = 0x0E20;
    piecesTypes[2].rotations[3] = 0x88C0;

    //L
    piecesTypes[3].color = "\x1b[43m";
    piecesTypes[3].rotations[0] = 0x2E00;
    piecesTypes[3].rotations[1] = 0x4460;
    piecesTypes[3].rotations[2] = 0x0E80;
    piecesTypes[3].rotations[3] = 0xC440;

    //O - carré
    piecesTypes[4].color = "\x1b[47m";
    piecesTypes[4].rotations[0] = 0x6600;
    piecesTypes[4].rotations[1] = 0x6600;
    piecesTypes[4].rotations[2] = 0x6600;
    piecesTypes[4].rotations[3] = 0x6600;

    //T
    piecesTypes[5].color = "\x1b[45m";
    piecesTypes[5].rotations[0] = 0x4E00;
    piecesTypes[5].rotations[1] = 0x4640;
    piecesTypes[5].rotations[2] = 0x0E40;
    piecesTypes[5].rotations[3] = 0x4C40;

     //S
    piecesTypes[6].color = "\x1b[42m";
    piecesTypes[6].rotations[0] = 0x6C00;
    piecesTypes[6].rotations[1] = 0x4620;
    piecesTypes[6].rotations[2] = 0x06C0;
    piecesTypes[6].rotations[3] = 0x8C40;

     //Z
    piecesTypes[7].color = "\x1b[41m";
    piecesTypes[7].rotations[0] = 0xC600;
    piecesTypes[7].rotations[1] = 0x2640;
    piecesTypes[7].rotations[2] = 0x0C60;
    piecesTypes[7].rotations[3] = 0x4C80;
}

int randPiece() //need better RNG
{
	srand(clock());
	return (rand() % (PIECES_AMOUNT) +1);
}

bool spawnPieces()
{
	currentPiece = nextPiece;
    nextPiece = randPiece();
    xpos = SPAWN_X;
    ypos = 0;

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
		if ((grid[y][x] != BLANK)) return false; //was blocked during spawn = game lost;
	}

	return true; //spawned fine
}
