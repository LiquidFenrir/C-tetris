#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#define GETBIT(var, n) ((var >> n) & 1)

//taille du terrain sur le jeu GB
#define MAP_WIDTH 10
#define MAP_HEIGHT 16

#define X_OFFSET 2
#define Y_OFFSET 2

#define SPAWN_X ((MAP_WIDTH/2)-2)

extern uint8_t grid[MAP_HEIGHT][MAP_WIDTH];
extern int xpos;
extern int ypos;
