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
