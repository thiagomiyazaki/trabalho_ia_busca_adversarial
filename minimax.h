
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#ifndef MINIMAX_H
#define MINIMAX_H

int minimax(char board[3][3], int depth, bool isMax);
move findBestMove(char board[3][3], char symbol);
int max(int a, int b);
int min(int a, int b);

#endif