#include "minimax.h"
#include "board.h"

void calculate_minimax(char board[3][3], char first_player);
void calculate_ab_pruning(char board[3][3], char first_player);
char **copy_board(char* list_of_boards[4]);
void free_list_of_boards(char* list[4]);
