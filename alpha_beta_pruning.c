#include "board.h"
#include "alpha_beta_pruning.h"
#include "minimax.h"
#include <limits.h>

/*
    int alpha_beta_search(char board[3][3], char current_player)
    
        current_player: indica quem deve fazer uma jogada no momento atual
        INT_MIN:        valor da biblioteca limits.h que fornece o MENOR valor possível que um int pode guardar
        INT_MAX:        valor da biblioteca limits.h que fornece o MAIOR valor possível que um int pode guardar
        board:          guarda um estado, ou seja, a configuracao do jogo em um dado momento no tempo

        alpha:          o melhor valor de utilidade/minimax que MAX consegue obter em face da qualidade das jogadas de MIN
                        lembrando que:
                            - MAX deseja atingir valor maximo de utilidade/minimax.
                            - consideramos MIN um 'superjogador', que faz apenas as melhores jogadas.

        beta:           o melhor valor de utilidade/minimax de MIN consegue obter em face da qualidade das jogadas de MAX
                        lembrando que:
                            - MIN deseja atingir valor minimo de utilidade/minimax


    levando-se em consideracao um jogo two-ply (de dois turnos intercalados, max joga, min joga, max joga, min joga e assim sucessivamente):

        - se o jogador atual for MAX, entao a chamada recursiva se inicia chamando max_value
            * depois em max_value chamaremos min_value, simulando jogadas intercaladas.

        - se o jogador atual for MIN, entao a chamada recursiva se inicia chamando min_value.
            * depois em min_value chamaremos max_value.

    eis o raciocinio:
        se o jogador for MAX este busca a jogada que tenha o maior valor de utilidade (valor minimax),
        logo deve chamar max_value, que vai fazer uma busca em profundidade e trazer o maior valor possivel dada
        a circunstancia imposta pela configuracao atual do jogo (variavel board).

        caso o jogadar atual seja MIN o raciocinio segue de forma analoga.

*/
int alpha_beta_search(char board[3][3], char current_player){
    int minimax_value = (current_player == MAX_PLAYER) ? max_value(board, INT_MIN, INT_MAX) : min_value(board, INT_MIN, INT_MAX);
    return minimax_value;
}

/*
    max_value(char board[3][3], int alpha, int beta)

    - retorna o valor de utilidade/minimax para um determinado estado MAX
    - se o espaco estiver vazio vamos tentar fazer a jogada e calcular o 
    valor minimax dela. faremos isto para todos os espacos vazio e retornamos
    o valor da melhor jogada que encontramos.

    obs1: 
    - Dado que estamos na função max_value, devemos considerar duas possibilidades:
        * estamos em um nó intermediário e em um nível anterior/superior existe um nível MIN.
        * o nó/estado da função atual é um nó raiz.
    
    - Beta é o valor de utilidade/minimax mais baixo que MIN encontrou até o momento.
        * se o nó é raiz e se (valor de utilidade) > beta, então podemos simplesmente retornar o valor
        pois encontramos o maior valor possível dadas as condições atuais - lidando com um oponente ideal
        * se o nó não é raiz e se (valor de utilidade) > beta, isto indica que podemos podar esta subárvore,
        pois:
            -> existe um min value acima querendo encontrar os estados/caminhos de menor valor de utilidade,
            e considerando o oponente ideal, ele nunca irá escolher um nó que tenha um valor alto, especialmente
            levando-se em consideração que ele já encontrou um caminho de valor de utilidade menor (valor beta),
            então podemos desconsiderar toda esta subárvore e não precisamos investigá-la, pois já sabemos
            que ela não é uma opção viável para MIN.
*/
int max_value(char board[3][3], int alpha, int beta){
    // condicao de parada
    int score = utility(board);
    if (score != 0) return score;
    if (!isMovesLeft(board) && score == 0) return 0; 

    int best_value = INT_MIN;

    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == EMPTY){                                           // se o espaco estiver vazio
                board[i][j] = MAX_PLAYER;                                       // tentamos fazer a jogada
                best_value = max(best_value, min_value(board, alpha, beta));    // com a jogada feita calculamos minimax
                /* ler obs 1 */
                if (best_value >= beta) {
                    board[i][j] = EMPTY;
                    return best_value;
                    }
                alpha = max(alpha, best_value);                 // alpha deve refletir o maior valor de utilidade encontrado
                board[i][j] = EMPTY;                // voltamos o board ao estado original para prosseguirmos com a busca
            }
        }
    }
    return best_value;
}

/*
    min_value(char board[3][3], int alpha, int beta)

    - analogo ao max_value
*/
int min_value(char board[3][3], int alpha, int beta){
    // condicao de parada
    int score = utility(board);
    if (score != 0) return score;
    if (!isMovesLeft(board) && score == 0) return 0; 

    int best_value = INT_MAX;
    
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == EMPTY){
                board[i][j] = MIN_PLAYER;
                best_value = min(best_value, max_value(board, alpha, beta));
                if (best_value <= alpha) {
                    board[i][j] = EMPTY;
                    return best_value;
                }
                beta = min(beta, best_value);
                board[i][j] = EMPTY;
            }
        }
    }
    return best_value;
}

move find_best_move_alphabeta(char board[3][3], char symbol){ 
	int bestVal;
	if(symbol == MAX_PLAYER) bestVal = INT_MIN;
	else bestVal = INT_MAX;

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

				if(symbol == MAX_PLAYER) moveVal = alpha_beta_search(board, MIN_PLAYER);
				else moveVal = alpha_beta_search(board, MAX_PLAYER);

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

	printf("(Alpha-Beta Pruning) Valor do melhor movimento : %d | Jogador: %c | Move: %d %d\n\n", bestVal, symbol, bestMove.row, bestMove.col); 

	return bestMove; 
}