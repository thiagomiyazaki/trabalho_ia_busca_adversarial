#include "minimax.h"
#include "board.h"
#include "execution.h"
#include "alpha_beta_pruning.h"
#include <stdbool.h>

void calculate_minimax(char board[3][3], char first_player){

    // Apenas printa o tabuleiro
    #ifdef VERBOSE
        printBoard(board);
    #endif

    // determina quem será o primeiro a jogar
    int k = (first_player == MIN_PLAYER) ? 0 : 1;
    
    // enquanto: utilidade == 0 e ainda houver espaços vazios
    while(utility(board)==0 && isMovesLeft(board)){
        if (k%2==0){
            move bestMove = findBestMove(board, 'o');
            play(board, bestMove,'o');
        }
        else{
            move bestMove = findBestMove(board, 'x');
            play(board, bestMove,'x');
        }
        #ifdef VERBOSE
            printBoard(board);
        #endif
        k++;
    }
}

void calculate_ab_pruning(char board[3][3], char first_player){

    // Apenas printa o tabuleiro
    #ifdef VERBOSE
        printBoard(board);
    #endif

    // determina quem será o primeiro a jogar
    int k = (first_player == MIN_PLAYER) ? 0 : 1;
    
    // enquanto: utilidade == 0 e ainda houver espaços vazios
    while(utility(board)==0 && isMovesLeft(board)){
        if (k%2==0){
            move bestMove = find_best_move_alphabeta(board, MIN_PLAYER);
            play(board, bestMove, MIN_PLAYER);
        }
        else{
            move bestMove = find_best_move_alphabeta(board, MAX_PLAYER);
            play(board, bestMove, MAX_PLAYER);
        }
        #ifdef VERBOSE
            printBoard(board);
        #endif
        k++;
    }
}

void calculate_mixed(char board[3][3], char first_player, bool is_max_alpha){

    // Apenas printa o tabuleiro
    #ifdef VERBOSE
        printBoard(board);
    #endif

    // determina quem será o primeiro a jogar
    int k = (first_player == MIN_PLAYER) ? 0 : 1;
    
    // enquanto: utilidade == 0 e ainda houver espaços vazios
    while(utility(board)==0 && isMovesLeft(board)){
        if (k%2==0){
            move bestMove = is_max_alpha ? findBestMove(board, MIN_PLAYER) : find_best_move_alphabeta(board, MIN_PLAYER);
            play(board, bestMove, MIN_PLAYER);
        }
        else{
            move bestMove = !is_max_alpha ? findBestMove(board, MAX_PLAYER) : find_best_move_alphabeta(board, MAX_PLAYER);
            play(board, bestMove, MAX_PLAYER);
        }
        #ifdef VERBOSE
            printBoard(board);
        #endif
        k++;
    }
}

char **copy_board(char* original_list_of_boards[4]){
    char** copy_list_of_boards = (char**) malloc(sizeof(char*)*4);
    char* board_01 = (char*) malloc(9);
    char* board_02 = (char*) malloc(9);
    char* board_03 = (char*) malloc(9);
    char* board_04 = (char*) malloc(9);
    copy_list_of_boards[0] = board_01;
    copy_list_of_boards[1] = board_02;
    copy_list_of_boards[2] = board_03;
    copy_list_of_boards[3] = board_04;

    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 9; j++){
            copy_list_of_boards[i][j] = original_list_of_boards[i][j];
        }
    }
    return copy_list_of_boards;
}

void free_list_of_boards(char* list[4]){
    for (int i = 0; i < 4; i++){
        free(list[i]);
    }    
}
