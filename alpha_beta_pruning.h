#include "board.h"
#include "minimax.h"

int alpha_beta_search(char board[3][3], char current_player);
int max_value(char board[3][3], int alpha, int beta);
int min_value(char board[3][3], int alpha, int beta);
move find_best_move_alphabeta(char board[3][3], char symbol);
