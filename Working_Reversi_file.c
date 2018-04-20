#include <stdio.h>
#include <string.h>
#include "Reversi components.h" // Includes function definitions for game components

#define SIZE 8 // Board size of 8x8

// Initialisation of variables for use
char board[SIZE][SIZE]; // Array for board
int valid_move_check[SIZE][SIZE]; // Array that stores 1 at co-ordinate of valid move
int valid[20];// Array that stores the co-ordinates of valid moves
int row = 0, col = 0;
int move_count = 4, invalid_count = 0; // Counts for moves made and invalid moves
int p1_score = 0, p2_score = 0;
int x = 0; char y = 0;
char move = 0;
int count = 1, choice = 0;

int main()
{
   getdetails(); // Assign name and disk type to players

   for(row = 0; row < SIZE; row++) // Blank all board squares
     for(col = 0; col < SIZE; col++)
       board[row][col] = ' ';

   // Place the initial four counters in the center as specified
   board[SIZE/2 - 1][SIZE/2 - 1] = board[SIZE/2][SIZE/2] = P1.disk;
   board[SIZE/2 - 1][SIZE/2] = board[SIZE/2][SIZE/2 - 1] = P2.disk;

   // The game play loop
   while(move_count < SIZE*SIZE && invalid_count <= 2) // While game has not ended
    {
      showboard(board);                      // Display the board
      invalid_count = player_move(board,valid_move_check,valid,count,invalid_count,move_count); // Players take turns moving
      count++; // Used to control player's turns
    }

   showboard(board);  // Show final board as game has ended
   result(board);   // Show final score and create text file with final score
   return 0;
}
