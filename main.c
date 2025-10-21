#include <stdio.h>
#include "bitboard.h"
#include <stdbool.h>



int main(){
    //create a game variable that will store red pieces, black pieces, kings and current_turn
    //then create board that changes the actual game state
    GameState game; 
    createBoard(&game);

    //while the game has not ended, print the board
    //print which player is to play currently and updagte the current_turn (easier for the player)
    //player 1 is red and player 2 is black 
    printf("player 1 will be r and player 2 will be b\n");


    while (!IsGameOver(&game)){
        
        printBoard(&game);
        printf("Player %d's turn\n", game.current_turn + 1);

        int fromRow = 0;
        int toRow = 0;
        int fromCol = 0;
        int toCol = 0;

        printf("Enter move (fromRow fromCol toRow toCol): ", game.current_turn);
        scanf("%d %d %d %d", &fromRow, &fromCol, &toRow, &toCol);
        int from = BoardToIndex(fromRow, fromCol);
        int to = BoardToIndex(toRow, toCol);

        //before making a piece move check to see if the player's input is valid if it isn't print an error msg else call MovePiece function
        //printf("Trying move: %d -> %d\n", from, to);
        if(!IsValidMove(&game, from , to)){
            printf("Invalid move, try again. \n");
            continue;
        }
        bool checkTurn = MovePiece(&game, from, to);
        if (checkTurn){
            game.current_turn = 1 - game.current_turn;

        }
    }

    printf("Game over\n");
    int winner = getWinner(&game);
    if (winner == 1){
        printf("player 1 wins! \n");
    }
    else if(winner == 2){
        printf ("player 2 wins! \n");
    }
    else{
        printf("Draw");
    }

}