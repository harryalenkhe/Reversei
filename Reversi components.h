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
