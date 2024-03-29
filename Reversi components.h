#define SIZE 8 // Board size of 8x8
void showboard(char board[][SIZE])
{
   int row  = 0;          // Row index
   int col = 0;           // Column index
   char col_letter = 'a';  // Column label

   puts(" ");                  // Start top line
   for(col = 0 ; col<SIZE ;col++)
     printf("   %c", col_letter+col); // Display the top line
   puts(" ");                  // End the top line

   // Display the intermediate rows
   for(row = 0; row < SIZE; row++)
   {
     printf("  +");
     for(col = 0; col<SIZE; col++)
       printf("---+");
     printf("\n%2d|",row + 1);

     for(col = 0; col<SIZE; col++)
       printf(" %c |", board[row][col]);  // Display counters in row
     puts(" ");
   }

   printf("  +");                  // Start the bottom line
   for(col = 0 ; col<SIZE ;col++)
     printf("---+");               // Display the bottom line
   puts(" ");                      // End the bottom  line
}


struct player // Structure for players
{
 char name[32]; // array for name of player
 char disk; // disk type
} P1, P2;



// Function definition to get player details and store in struct members for use
int getdetails()
 {
   puts("-------------------------------------------");
   printf("Player 1 enter your name please.\n");
   fgets(P1.name,32,stdin); // Assigning name to P1 with user input
   P1.name[strcspn(P1.name, "\n")] = 0; // Remove the newline character
   P1.disk = '1'; // Assigning disk type to P1
   printf("Hello %s\nYour disk is %c as you are Player 1\n",P1.name, P1.disk);
   puts("-------------------------------------------\n");

   puts("-------------------------------------------");
   printf("Player 2 enter your name please.\n");
   fgets(P2.name,32,stdin); // Assigning name to P2 with user input
   P2.name[strcspn(P2.name, "\n")] = 0; // Remove the newline character
   P2.disk = '2'; // Assigning disk type to P2
   printf("Hello %s\nYour disk is %c as you are Player 2\n",P2.name, P2.disk);
   puts("-------------------------------------------");

   return 0;
 }

 // Function definition for finding valid moves and displaying the valid moves
 // along with the options for the user to pick from
 int valid_moves(char board[][SIZE], int valid_move_check[][SIZE], char p1, int valid[20])
 {
    int row = 0, col = 0;
    int i = 0, j = 0, k = 0, x = 0, y = 0;
    int move_count = 0;

    // Set the opponent based on the current turn
    char op = (p1 == P1.disk)? P2.disk : P1.disk;

    // Initialize moves array to zero
    for(row = 0; row < SIZE; row++)
      for(col = 0; col < SIZE; col++)
        valid_move_check[row][col] = 0;

    // Check squares until P1 disk is found
    for(row = 0; row < SIZE; row++)
      for(col = 0; col < SIZE; col++)
        {
          if(board[row][col] == ' ')
            continue;

          if(board[row][col] == p1) // If we find a P1 disk
           {
             for(x = -1; x < 2; x++)
               for(y = -1; y < 2; y++)
                {
                  // Ignore current square and outside of the array
                  if(row + x < 0 || row + x >= SIZE || col + y < 0 || col + y >= SIZE ||(x == 0 && y == 0))
                    continue; // Check the next square

                  if(board[row + x][col + y] == op) // If opponent's disk is found
                   {
                     // New variables initalised to check for valid moves
                     int rowco_ord = row + x;
                     int colco_ord = col + y;
                     while(1) // Always true so that the loop continues until we hit a break;
                       {
                         rowco_ord += x;  // Leapfrog the opponent's counter
                         colco_ord += y;  // in a straight line

                         // If we move outside the array then no valid move
                         if(rowco_ord < 0 || rowco_ord >= SIZE || colco_ord < 0 || colco_ord >= SIZE)
                          {
                            break;
                          }

                         // If we find a blank square, we have a valid move
                         else if(board[rowco_ord][colco_ord] == ' ')
                          {
                            // Store valid move as a double digit in the array
                            valid[move_count] = (rowco_ord)*10 + (colco_ord);
                            valid_move_check[rowco_ord][colco_ord] = 1;       // Mark as valid move
                            move_count++;                                     // Increase valid moves count
                            break;                                            // Continue checking squares
                          }

                         // If we find our own counter then no valid move
                         else if(board[rowco_ord][colco_ord] == p1)
                          {
                            break;
                          }
                       }
                   }
                }
           }
        }

   for(i = 0; i < move_count; i++) // Remove duplicate valid moves from the array
        for(j = i+1; j < move_count; j++)
         {
            if(valid[i] == valid[j]) // If any duplicates are found
             {
               for(k=j; k<move_count; k++) // Delete the current duplicate element
                {
                  valid[k] = valid[k + 1];
                }

               move_count--; // Decrement size after removing duplicate element
               j--; // If shifting of elements occur then don't increment j
             }
         }

   printf("Valid moves -> ");
   for(i = 0; i < move_count; i++) // Display the valid moves
     {
       printf("%d. (%d %c)  ",i+1 ,(valid[i]/10 + 1), (valid[i]%10 + 97));
     }
   return move_count;
 }


// Function definition for making a move after a valid move has been selected
void make_move(char board[][SIZE], int row, int col, char p1)
  {
     int rowco_ord = 0, colco_ord = 0;
     int x = 0, y = 0;

     // Identify opponent
     char op = (p1 == P1.disk)? P2.disk : P1.disk;

     board[row][col] = p1; // Place the p1 counter on the selected square

     // Check all the squares around this square for the opponents counter
     for(x = -1; x <= 1; x++)
       for(y = -1; y <= 1; y++)
         {
           // Ignore squares off the board and the current square
           if(row + x < 0 || row + x >= SIZE || col + y < 0 || col + y >= SIZE || (x==0 && y== 0))
             continue;

           // When the opponent's counter is found
           if(board[row + x][col + y] == op)
             {
               rowco_ord = row + x; // Variables used to check surrounding squares
               colco_ord = col + y;

               while(1)
                 {
                   rowco_ord += x;           // Move to the
                   colco_ord += y;           // next square

                   // If we find the P1 counter then we change all the opponent counters
                   // in between the two P1 counters
                   if(board[rowco_ord][colco_ord] == p1)
                     {
                       while(board[rowco_ord -= x][colco_ord -= y] == op)
                        {
                          board[rowco_ord][colco_ord] = p1; // Change to P1 counter
                        }
                       break; // No more opponent counters to change
                     }

                   // Despite the selected move being a valid move
                   // the below conditions are included to avoid bus errors
                   // which are errors when the hardware tries to access invalid memory
                   if(rowco_ord < 0 || rowco_ord >= SIZE || colco_ord < 0 || colco_ord >= SIZE)
                     break;

                   if(board[rowco_ord][colco_ord] == ' ')
                     break;
                 }
             }
         }
  }

  // Function definition for players taking turns and deciding their move
  int player_move(char board[][SIZE], int valid_move_check[][SIZE], int valid[10], int count, int invalid_count, int move_count)
    {
      char y = 0; int x = 0;
      char move = 0; int choice = 0;

      if((count % 2) != 0) // P1's turn
      {
        puts("-------------------------------------------");
        printf("%s's move.\n",P1.name);
        if(valid_moves(board, valid_move_check, P1.disk,valid)) // Prints valid moves also
          {
            // Read p1 moves until a valid move is entered
            while(1)
              {
                fflush(stdin);                // Flush the keyboard buffer
                printf("\nPlease choose from one of the valid moves: ");
                scanf("%d%*c",&choice);       // Choose from valid moves

                // Valid moves are stored as a double digit numbers in indexes of array
                x = valid[choice-1]/10;       // Assign row by dividing double digit number
                y = valid[choice-1]%10;       // Assign column by getting remainder of division

                if( (x>=0 && y>=0) && (x<SIZE && y<SIZE) && valid_move_check[x][y]) // If valid_move
                {
                  make_move(board, x, y, P1.disk);
                  move_count++;                             // Increment move count
                  break;
                }

                else
                 {
                   printf("Please pick a valid move from the options\n"); // When a non-valid move is entered
                 }
              }
          }
        else   // No valid moves
          if(++invalid_count <= 2)
          {
            fflush(stdin); // flush input buffer
            printf("\nNo valid moves on this turn. Press enter to pass ");
            scanf("%c", &move); // When no valid moves left for player
          }
          else // When no more valid moves left for either players
            printf("\nNo more squares left, GAME OVER\n");
            puts("-------------------------------------------");
       }

       else if((count % 2) == 0) // P2's turn
       {
         puts("-------------------------------------------");
         printf("%s's move.\n",P2.name);
         if(valid_moves(board, valid_move_check, P2.disk,valid)) // Prints valid moves also
         {
           while(1)
           {
             fflush(stdin);              // Flush the keyboard buffer
             printf("\nPlease choose from one of the valid moves: ");
             scanf("%d%*c",&choice); // Choose from one of the valid moves

             x = valid[choice-1]/10; // Assign row
             y = valid[choice-1]%10; // Assign column

             if( (x>=0 && y>=0) && (x<SIZE && y<SIZE) && valid_move_check[x][y])
               {
                 make_move(board, x, y, P2.disk);
                 move_count++;              // Increment move count
                 break;
               }
             else
               printf("Please pick a valid move from the options\n");
               puts("-------------------------------------------");
           }
         }
         else                                // No valid moves
           if(++invalid_count <= 2)
           {
             fflush(stdin);                  // Flush the keyboard buffer
             printf("\nNo valid moves on this turn. Press enter to pass ");
             scanf("%c", &move);            // Pass
           }
           else
             printf("\nNo more squares left, GAME OVER\n");
             puts("-------------------------------------------");
             // End of game
        }
      return invalid_count;
    }


// Function definition to count final score and display on screen and in created txt file
int result(char board[][SIZE])
 {
   int p2_score = 0, p1_score = 0;

   for(int row = 0; row < SIZE; row++)
     for(int col = 0; col < SIZE; col++)
       {
         p1_score += board[row][col] == P1.disk; // If P1 counter add to P1_score
         p2_score += board[row][col] == P2.disk; // If P1 counter add to P1_score
       }
   FILE *winner; // Open file

   // Open the file for writing
   winner = fopen("winner.txt", "wt");
   if (!winner) // If file cannot be opened for some reason
   {
     printf("File could not be opened\n\a\a");
     return 0;
   }

   else // If file can be opened
     { // Store and print the winner details in a file and to a screen
       puts("-------------------------------------------");
       fprintf(winner,"The final score is:\n%s - %d\n%s - %d\n\n",P1.name, p1_score, P2.name, p2_score);
       printf("The final score is:\n%s - %d\n%s - %d\n\n",P1.name, p1_score, P2.name, p2_score);

       if(p2_score > p1_score) // If P2 wins
        {
          fprintf(winner,"%s wins!\n",P2.name);
          printf("%s wins!\n",P2.name);
        }
       else if(p2_score < p1_score) // P1 wins
        {
          fprintf(winner,"%s wins!\n",P1.name);
          printf("%s wins!\n",P1.name);
        }
       else // Draw
        {
          fprintf(winner,"It's a draw!\n");
          printf("It's a draw!\n");
        }

       fprintf(winner,"\nThanks for playing\n");
       printf("Thanks for playing\n");
       puts("-------------------------------------------");
     }
   // Close the file
   fclose(winner);

   printf("Please check winner.txt for the results as well\n");
   return 0;
 }
