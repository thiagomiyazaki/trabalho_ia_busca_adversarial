
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

/*
	Checa se existem movimentos a serem feitos
*/
bool isMovesLeft(char b[3][3]){ 
	for (int i = 0; i<3; i++) 
		for (int j = 0; j<3; j++) 
			if (b[i][j]=='_') 
				return true; 
	return false; 
} 

int count_empty_spaces(char b[3][3]){
	int count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (b[i][j] == EMPTY) count++;
	return count;
}

/*
	Função utilidade para um tabuleiro de jogo da velha
*/
int utility(char b[3][3])
{
	int empty_spaces_count = count_empty_spaces(b);
	// Checa linhas
	for (int row = 0; row<3; row++) 
	{ 
		if (b[row][0]==b[row][1] && b[row][1]==b[row][2]){ 
			if (b[row][0]=='x')
				return +100 + empty_spaces_count;
            if (b[row][0]=='o') 
				return -100 - empty_spaces_count;
		} 
	} 

	// Checa colunas
	for (int col = 0; col<3; col++) 
	{ 
		if (b[0][col]==b[1][col] && b[1][col]==b[2][col]){ 
			if (b[0][col]=='x') 
				return +100 + empty_spaces_count;
            if (b[0][col]=='o') 
			    return -100 - empty_spaces_count;

		} 
	} 

	//Checa diagonais
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2]){ 
		if (b[0][0]=='x')
			return +100 + empty_spaces_count; 
		else if (b[0][0]=='o')
			return -100 - empty_spaces_count;
	} 

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0]){ 
		if (b[0][2]=='x') 
			return +100 + empty_spaces_count; 
		else if (b[0][2]=='o') 
			return -100 - empty_spaces_count; 
	} 

	// Else if none of them have won then return 0 
	return 0; 
}

/*
	Realiza uma jogada no tabuleiro
*/
void play(char b[3][3], move m, char p){
    b[m.row][m.col] = p;
}

/*
	Imprime tabuleiro na tela
*/
void printBoard(char b[3][3]){
	for (int i=0; i<3; i++){
		printf("|");
		for (int j=0; j<3; j++){
			printf(" %c |", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}