
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef BOARD_H
#define BOARD_H

#define MAX_PLAYER 'x'
#define MIN_PLAYER 'o'
#define EMPTY '_'

typedef struct { 
	int row, col;
} move;

bool isMovesLeft(char board[3][3]);
int utility(char b[3][3]);
void play(char b[3][3], move m, char p);
void printBoard(char b[3][3]);
void calculate_mixed(char board[3][3], char first_player, bool is_max_alpha);
#endif