#include "../minimax.h"
#include "../board.h"
#include "../execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
    argv[1] -- Numero de espacos ja preenchidos (Complexidade do Tabuleiro)
		--> Valores de 1 a 4
    argv[2] -- Qual algoritmo sera usado
        --> 0: MinMax
        --> 1: Alpha Beta Pruning
        --> 2: Mixed MAX uses AB Pruning
        --> 3: Mixed MIN uses AB Pruning
*/
int main(int argc, char const *argv[]) {

	int i;
	int j;

	int board_complexity;
	int algorithm_type;

	char player;
	char board[3][3];

	if (argc != 3)
	{
		printf("As entradas do programa são: \n\n");
		printf("argv[1] -- Numero de espacos ja preenchidos (Complexidade do Tabuleiro)\n");
		printf("	--> Valores de 1 a 4\n");
		printf("argv[2] -- Qual algoritmo sera usado\n");
		printf("	--> 0: MinMax\n");
		printf("	--> 1: Alpha Beta Pruning\n");
		printf("	--> 2: Mixed MAX uses AB Pruning\n");
		printf("	--> 3: Mixed MIN uses AB Pruning\n");
		return -1;
	}
	
	board_complexity = atoi(argv[1]);
	algorithm_type = atoi(argv[2]);

	/*============================*/
	/* Criacao da Matrix de Teste */
	/*============================*/
    
	int rand_col;
	int rand_row;

	bool valid_pos;
	bool table_is_ready;

	srand(time(NULL));
	table_is_ready = false;

	/*Enquanto nao produzir um tabuleiro valido (sem vencedores)*/
	while (!table_is_ready)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
				board[i][j] = '_';	
		}

		for (i = 0; i < board_complexity; i++)
		{
			valid_pos = false;

			if (algorithm_type == 2)
				player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;
			else
				player = (i % 2 == 0) ? MAX_PLAYER : MIN_PLAYER;
			

			/*Enquanto nao achar um lugar vago pra inserir*/
			while (!valid_pos)
			{
				rand_col = rand() % 3;
				rand_row = rand() % 3;

				if (board[rand_row][rand_col] == '_')
				{
					valid_pos = true;
					board[rand_row][rand_col] = player;
				}
			}

		}

		table_is_ready = (board_complexity > 2) ? !(utility(board)) : true;
	}

	/*=================================*/
	/* Execucao do Algoritmo Escolhido */
	/*=================================*/

	clock_t start, end;

	if (algorithm_type == 2)
		player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;
	else
		player = (i % 2 == 0) ? MAX_PLAYER : MIN_PLAYER;

	switch (algorithm_type)
	{
	/*MinMax*/
	case 0:
		start = clock();
        calculate_minimax(board, player);
		end = clock();
		break;
	/*Alpha Beta Pruning*/
	case 1:
		start = clock();
        calculate_ab_pruning(board, player);
		end = clock();
		break;
	/*Mixed MAX uses AB Pruning*/
	case 2:
		start = clock();
        calculate_mixed(board, player, true);
		end = clock();
		break;
	/*Mixed MIN uses AB Pruning*/
	case 3:
		start = clock();
        calculate_mixed(board, player, false);
		end = clock();
		break;
	
	default:
		printf("Codigo nao corresponde a nenhum algoritmo");
		return -1;
		break;
	}
	
	fprintf(stderr, "%ld\n", (end-start));

	return 0; 
}
