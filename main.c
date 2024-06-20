#include "minimax.h"
#include "board.h"
#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


int main(){
	char board_01[3][3] = { 
		{ 'x', '_', '_' }, 
		{ '_', '_', '_' }, 
		{ '_', '_', '_' } 
	};
	char board_02[3][3] = { 
		{ 'x', '_', 'o' }, 
		{ '_', '_', '_' }, 
		{ '_', '_', '_' } 
	};
	char board_03[3][3] = { 
		{ '_', 'x', '_' }, 
		{ '_', 'o', '_' }, 
		{ 'x', '_', '_' } 
	};
	char board_04[3][3] = { 
		{ 'x', 'x', '_' }, 
		{ '_', 'o', '_' }, 
		{ 'o', '_', '_' } 
	};

	char* list_of_boards[4] = {(char*)board_01, (char*)board_02, (char*)board_03, (char*)board_04};
	char** list_of_boards2 = copy_board(list_of_boards);
	char** list_of_boards3 = copy_board(list_of_boards);
	char** list_of_boards4 = copy_board(list_of_boards);

	FILE* timings_file = fopen("timings.txt", "w");
	fprintf(timings_file, "algo\t\tmarks\ttime\n");
	clock_t start, end;
	
	// minimax runs
    for(int i = 0; i < 4; i++){
        printf("\n\n!--- GAME BOARD 0%d ---!\n\n\n", i);

        char player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;

		start = clock();
        calculate_minimax((char (*)[3])list_of_boards[i], player);
		end = clock();

		fprintf(timings_file, "minimax\t\t%d\t\t%ld\n", i+1, (end-start));
    }

	// alpha beta pruning runs
	for(int i = 0; i < 4; i++){
        printf("\n\n!--- GAME BOARD 0%d ---!\n\n\n", i);

        char player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;

		start = clock();
		calculate_ab_pruning((char (*)[3])list_of_boards2[i], player);
		end = clock();

		fprintf(timings_file, "ab_pruning\t%d\t\t%ld\n", i+1, (end-start));
    }

	// mixed MAX uses ab pruning
	for(int i = 0; i < 4; i++){
        printf("\n\n!--- GAME BOARD 0%d ---!\n\n\n", i);

        char player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;

		start = clock();
		calculate_mixed((char (*)[3])list_of_boards3[i], player, true);
		end = clock();

		fprintf(timings_file, "mix_ab_max\t%d\t\t%ld\n", i+1, (end-start));
    }

	// mixed MIN uses ab pruning
	for(int i = 0; i < 4; i++){
        printf("\n\n!--- GAME BOARD 0%d ---!\n\n\n", i);

        char player = (i % 2 == 0) ? MIN_PLAYER : MAX_PLAYER;

		start = clock();
		calculate_mixed((char (*)[3])list_of_boards4[i], player, false);
		end = clock();

		fprintf(timings_file, "mix_ab_min\t%d\t\t%ld\n", i+1, (end-start));
    }

	fclose(timings_file);
	free_list_of_boards(list_of_boards2);
	free_list_of_boards(list_of_boards3);
	free_list_of_boards(list_of_boards4);
	
	return 0; 
}
