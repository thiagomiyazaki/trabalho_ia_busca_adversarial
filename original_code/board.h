
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef BOARD_H
#define BOARD_H

typedef struct { 
	int row, col;
} move;

bool isMovesLeft(char board[3][3]);
int utility(char b[3][3]);
void play(char b[3][3], move m, char p);
void printBoard(char b[3][3]);
#endif