
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "minimax.h"

int max(int a, int b){
    if (a>=b)
        return a;
    else
        return b;
}

int min(int a, int b){
    if (a<=b)
        return a;
    else
        return b;
}

/*
    Algoritmo minimax.
*/
int minimax(char board[3][3], int depth, bool isMax){
    //Checa se alguém venceu o jogo
	int score = utility(board);
	if (score != 0) return score;
    //Ou se empatou 
	if (!isMovesLeft(board) && score == 0) 
		return 0; 

	// Movimento do jogador MAX (x) 
	if (isMax) 
	{ 
		int best = -1000; 

		//Checa todas as posições do tabuleiro para execução de um movimento
		for (int i = 0; i<3; i++)
			for (int j = 0; j<3; j++)
				// Se célula está vazia, movimento é possível
				if (board[i][j]=='_') 
				{ 
					//Movimento do jogador x
					board[i][j] = 'x'; 

                    //Chamada recursiva do minimax
					best = max(best,minimax(board, depth+1, !isMax) ); 

					//Desfaz movimento
					board[i][j] = '_'; 
				}
		return best; 
	} 
	//Movimento do jogador MIN (o)
	else
	{ 
		int best = 1000; 

		//Checa todas as posições do tabuleiro para execução de um movimento
		for (int i = 0; i<3; i++)
			for (int j = 0; j<3; j++) 
				//Se célula está vazia, movimento é possível
				if (board[i][j]=='_'){ 
					//Movimento do jogador o 
					board[i][j] = 'o'; 

                    //Chamada recursiva do minimax
					best = min(best,minimax(board, depth+1, !isMax)); 

					//Desfaz movimento
					board[i][j] = '_'; 
				} 
		return best; 
	} 
} 

/*
    Melhor movimento possível para um jogador
*/
move findBestMove(char board[3][3], char symbol) 
{ 
	int bestVal;
	if(symbol == MAX_PLAYER) bestVal = -1000;
	else bestVal = 1000;

	move bestMove; 
	bestMove.row = -1; 
	bestMove.col = -1; 

	//Checa todas as ações possíveis 
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			// Check if cell is empty 
			if (board[i][j]=='_'){ 
				//Executa movimento
				board[i][j] = symbol; 

				int moveVal;

				if(symbol == MAX_PLAYER) moveVal = minimax(board, 0, false);
				else moveVal = minimax(board, 0, true);

				//Desfaz movimento
				board[i][j] = '_'; 

				//Atualiza melhor movimento, se necessário 
				if ((moveVal > bestVal && symbol == MAX_PLAYER) || (moveVal < bestVal && symbol == MIN_PLAYER)) 
				{ 
					bestMove.row = i; 
					bestMove.col = j; 
					bestVal = moveVal; 
				} 
			} 

	printf("(Minimax) Valor do melhor movimento : %d | Jogador: %c | Move: %d %d\n\n", bestVal, symbol, bestMove.row, bestMove.col); 

	return bestMove; 
}