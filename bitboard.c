#include <stdbool.h>
#include <stdio.h>
#include "bitboard.h"
#include <stdlib.h> 

void createBoard(GameState* game) {
    game->red_pieces = 0;
    game->red_kings = 0;
    game->black_pieces = 0;
    game->black_kings = 0;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 1) { 
                int index = row * 8 + col;

                if (row < 3) {
                    game->black_pieces |= 1ULL << index;
                } else if (row > 4) {
                    game->red_pieces |= 1ULL << index;
                }
            }
        }
    }

    game->current_turn = 0; 
    //player 1 will start 
}
void printBoard(GameState* game) {
    printf("0 1 2 3 4 5 6 7\n");
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int i = row * 8 + col; 
            int darkSpace = (row + col) % 2 == 1;
            char c = '*';

            if (darkSpace) {
                if ((game->red_pieces >> i) & 1){
                    c = 'r';
                }
                else if ((game->red_kings >> i) & 1){
                    c = 'R';
                } 
                else if ((game->black_pieces >> i) & 1){
                    c = 'b';
                }
                else if ((game->black_kings >> i) & 1){
                    c = 'B';
                } 
                else{
                    c = '*';
                } 
            }

            printf("%c ", c);
        }
        printf("\n");
    }
    printf("\n");
}


//check if there's already a piece on the square 
//shift bitboard to i bits to the right and then check if the last bit is 1 (means there's a piece)
//red pieces will be labeled as r and red's king will be R same for black B = black's king b = black pieces

bool IsValidMove(GameState* game, int from, int to){
    //create a variable that will hold the bit positon at from which will be represented by 1 and the same for to

    unsigned long long fromBitPosition = 1ULL << from;
    unsigned long long toBitPosition = 1ULL << to;

    //printf ("from: %d to: % d \n", from, to);
    
    //first check if the input of player from and to are in range of the board meaning it can't be less than 0 or greater than 64
    if ( from < 0 || from >= 64 || to < 0 || to >= 64){
        printf("out of range\n");
        return false;
    }

 

    //printf("Checking move from %d to %d\n", from, to);
    //printf("From bit: %llu\n", fromBitPosition);
    //printf("Occupied? %d\n", (game->red_pieces | game->black_pieces | game->red_kings | game->black_kings) & toBitPosition);


    //then check if it the positon where player input of to is occupied (if player is trying to move from a place that is already occupied)
    //do this by getting a bit representation where it shows where all occupied spaces of any piece (red, black, kings) and then use & 
    //to check if the space is occupied or not (will return true if the space is already occupied and returns false if the space is empty)

    if ((game -> red_pieces | game -> black_pieces | game -> red_kings | game -> black_kings) &toBitPosition){
        //printf("positon to is occupied \n");
        return false;
    }

    //check to see if the player is trying to move a piece that isn't there's ex: check current_turn where 0 - red/player 1 and 1 - black/player 2
    //if that matches up then check if the input to is valid  (in checkers moving forwared would mean moving one diagonally either left or right)
    //to move left or right for player 1 since its pieces are at the bottom the input should be equal to fromPositon + 7 to go left (diagnoal) and fromPos + 9 to go right (diagnal)
    //same thing for player 2 but subtraction since pieces start at the top 
    //board starts from 0 (bottomm left) to 63 (top right)

    if (game -> current_turn == 0 && (game -> red_pieces & fromBitPosition)){
        if (to == from - 7 || to == from - 9){
            //printf("Valid move for red piece\n");
            return true;
        }
    }

    if (game -> current_turn == 1 && (game -> black_pieces & fromBitPosition)){
        if (to == from + 7 || to == from + 9){
            //printf("valid move for black piece\n");
            return true;
        }
    }

    //before move is done check if the jump that the player is going to do i correct
    //for example plyaer 1 (red) should only jump over black pieces same applies to p2 (black)

    if(game -> current_turn == 0 && (game -> red_pieces & fromBitPosition)){
        if (to == from - 14|| to == from - 18){ //flip them for now
            int mid = (from + to) / 2;
            if (checkForOpponent(game, mid)){
                //printf("valid jump for red piece\n");
                return true;
            }
        }
    }

    if (game -> current_turn == 1 && (game -> black_pieces & fromBitPosition)){
        if (to == from + 14 || to == from + 18){ //flipped this for now
                int mid = (from + to) / 2;
            if (checkForOpponent(game, mid)){
                //printf("valid jump for black piece\n");
                return true;
            }

            }
    }

    //check if it is player's 1 turn and if it is the king piece then check if it is moving forward or back + or - 7 and + - 9  for moving left and right 
    //same thing for player 2 
    

    if (game -> current_turn == 0 && (game -> red_kings & fromBitPosition)){
        if (to == from + 7 || to == from - 7 || to == from + 9 || to == from - 9){
            return true;
        }

        if (to == from + 14 || to == from - 14 || to == from + 18 || to == from - 18){
            int mid = (to + from)/2;
            if (checkForOpponent(game, mid)){
                return true;
            }
        }
    }

    if (game -> current_turn == 1 && (game -> black_kings & fromBitPosition)){
        if (to == from + 7 || to == from - 7 || to == from + 9 || to == from - 9){
            return true;
        }

        if (to == from + 14 || to == from - 14 || to == from + 18 || to == from - 18){
            int mid = (to + from)/2;
            if (checkForOpponent(game, mid)){
                return true;
            }
        }
    }
    return false;

}

bool checkMultipleJump(GameState* game, int from){
    unsigned long long fromBitPosition = 1ULL << from;
    
    bool redPiece = (game-> red_pieces & fromBitPosition) != 0;
    bool blackPiece = (game-> black_pieces & fromBitPosition) != 0;
    bool redKing = (game -> red_kings & fromBitPosition) != 0;
    bool blackKing = (game-> black_kings & fromBitPosition) != 0;

    if (redPiece && !redKing){
        if (IsValidMove (game, from, from + 14) || IsValidMove (game, from, from + 18)){
            return true;
        }
    }
    if (blackPiece && !blackKing){
        if (IsValidMove (game, from, from -14) || IsValidMove(game, from, from -18)){
            return true;
        }
    }

    if (redKing || blackKing){
        if (IsValidMove (game, from, from + 14) || IsValidMove (game, from, from + 18) || IsValidMove (game, from, from -14) || IsValidMove(game, from, from -18)){
            return true;
        }
    }

    return false;
}

//create MovePiece function where pieces are moved on the board this will be called after isValidFunction function is true 
bool MovePiece(GameState* game, int from, int to){
    //create var for bit representation of both from and to where it will be 1 at the location where from and to are located at
    unsigned long long fromBitPosition = 1ULL << from;
    unsigned long long toBitPosition = 1ULL << to;
    //if it is currently player's 1 turn and there is a red piece at [from] then move piece 
    //then clear the bit at fromBitPosition do this for both red pieces and black piece to clear use ~ 
    //first check if there its reds turn  and that the players input (from pos) is actually a red piece by checking all positions of red pieces
    //after moving the piece remove opp piece that is between the jump 
    //check if the player reaches the other side so if it's red check if it reached the top and promote it positon of king 
    //same thing applies to black 

    if (game -> current_turn == 0 && (game -> red_pieces & fromBitPosition)){

        game -> red_pieces &= ~fromBitPosition;
        game -> red_pieces |= toBitPosition;

        if (abs(to-from) == 14  || abs(to-from) == 18){
            int mid = (from + to) /2;
            removePiece (game, mid); 
        }

        kingPromotion(game, to);

        if (checkMultipleJump(game, to)){
            return true;
        }

        game -> current_turn = 1;

        return false;
    }

    if(game -> current_turn == 1 && (game -> black_pieces & fromBitPosition)){
        game -> black_pieces &= ~fromBitPosition;
        game -> black_pieces |= toBitPosition;

        if (abs(to-from) == 14  || abs(to-from) == 18){
            int mid = (from + to) /2;
            removePiece (game, mid); 
        }

        kingPromotion(game, to);

        if (checkMultipleJump (game, to)){
            return true;
        }

        game -> current_turn = 0;
        return false;
    }
    return false;
}
bool checkForOpponent (GameState* game, int pos){
    unsigned long long bitPos = 1ULL << pos;
    //check whose turn it is player 1 or player 2
    //if it's player 1 check if there is a black piece/king at the pos
    //if its player 2 check if there is a red piece/king at the pos
    //then return true if the opponent is actually at that pos
    // return false if not

    if (game -> current_turn  == 0 ){
        return ((game -> black_pieces | game -> black_kings) & bitPos) != 0;
    }
    if (game -> current_turn == 1){
         return ((game -> red_pieces | game -> red_kings) & bitPos) != 0;
    }

    return false;
}

//create a remove piece func where it takes a position 
//then remove the piece in all of the pieces, kings doesn't matter because if it was a red piece then it will only affect what is stored in red_pieces 
//it wont affect black_piece or black_kings b/c nothing was ever there (~) use (&) for updating the pieces 
//& - 2 1's = 1  0 & 1 = 0 - 0 & 0 = 0
//~ - flips bits 
void removePiece (GameState* game, int pos){
    unsigned long long bitPos = 1ULL << pos;
    game -> red_pieces &= ~bitPos;
    game -> red_kings &= ~bitPos;
    game -> black_pieces &= ~bitPos;
    game -> black_kings &= ~bitPos;

}

//create a function where piece is pormoted to king 
//check which the player's turn and check if where it is going to jump/move is at the top or bottom depending on the player
// pplayer 1 red turns into a kinf when it reaches 56-63 
//player 2 (black) turns into a king when it reaches 0-7 either one of these spaces/positions
//then remove the piece pos from players pieces 
//add the kings position to player's king pos 

void kingPromotion (GameState* game, int to){
     unsigned long long toBitPos = 1ULL << to;

     if (game -> current_turn == 0 && to >= 56){
        game -> red_kings |= toBitPos;
        game -> red_pieces &= ~toBitPos;

     }
     else if (game -> current_turn == 1 && to <= 7){
        game -> black_kings |= toBitPos;
        game -> black_pieces &= ~toBitPos;
     }
}
int BoardToIndex(int row, int col){
    return row * 8 + col;
}
//check if the game is finished by checking if either player 1 or 2 doesn't have any more pieces left
bool IsGameOver(GameState* game){
    return (game -> red_pieces == 0 || game -> black_pieces == 0);
}

int getWinner (GameState* game){
    if (game->red_pieces == 0 && game -> red_kings == 0){
        return 2;
    }
    if (game->black_pieces == 0 && game -> black_kings == 0){
        return 1;
    }
    return 0;
}