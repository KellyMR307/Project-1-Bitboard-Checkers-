#ifndef bitboard_h
#define bitboard_h

#include <stdbool.h>

typedef struct{
    unsigned long long red_pieces; //player 1 pieces
    unsigned long long red_kings; //player 1 kings
    unsigned long long black_pieces; //player 2 pieces
    unsigned long long black_kings; //player 2 kings 
    int current_turn;
} GameState;

void createBoard(GameState* game);
void printBoard(GameState* game);
bool IsValidMove(GameState* game, int from, int to);
bool checkMultipleJump(GameState * game, int from);
bool MovePiece(GameState* game, int from, int to);
bool checkForOpponent (GameState* game, int pos);
void removePiece (GameState* game, int pos);
void kingPromotion (GameState* game, int to);
bool IsGameOver(GameState* game);
int getWinner(GameState* game);
int BoardToIndex(int row, int col);

#endif
