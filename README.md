# Project-1-Bitboard-Checkers-

Author: Kelly Martinez-Ramirez

description: building a checkers game using  bitwise functions, bit manipulation, and boolean algebra to create a simple and efficient checker's game that allows for input from the user(s) and in order to win this game either player 1 or player 2 will need to be left with no pieces. player 1 is represented as r or R (king) and player 2 is represented as b or B (king).

Instructions:
When asked for input make sure it is in the following order: fromRow fromCol toRow toCol seperated by a space only

make sure you know that the checker is labeled 0-7 for both col and rows 

Player 1 pieces will be located at the bottom of the board and player 2 pieces will be at the top

player 1 starts off first with their input then it will ask player 2 for input (make sure the input for player 2 is moving downward diagonally because if not you will be asked again until there is a valid input from the player)

However, when it is one of the player's turn and it is determined that the current player's turn is able to make another jump then the player will need to continue to make the jump until it is determined that they are no longer able to make another jump

To capture the opponent's piece simply input the position where the piece will end at, meaning opponent's piece position should be located in the middle from player's to and from input, Once a player's piece has been captured it will be cleared from the board and player will have less pieces on the board

To be promoted to king, player's will need to reach the opposite end from which they started from that is the only way a piece will be promoted to king
King's are able to move back and forth 

game end's when a player is left with no more pieces the winner will be the player that is still left with pieces

Building: 
bitboard.c contains all the functions in order for game to work (ex: movePiece, creatBoard, printBoard etc.)
bitboard.h is the header file that contains all functions declaration and the game board structure
main.c is where the functions are used to make the game playable

references: 
https://dyclassroom.com/c/c-pointers-and-structures#google_vignette
https://www.geeksforgeeks.org/c/structure-pointer-in-c/

