#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define the variables size and bombs that are global variables used throughout the program
#define SIZE 10
#define BOMBS 15

//Function to replace 15 random locations with "X" to indicate a bomb
void placeBombs(char board[SIZE][SIZE]) {
    //Allows for seed value to be different every time so the sequence of random numbers generated is unique 
    srand(time(NULL));
    //Number of bombs placed has to initially equal zero so bombs can start being placed
    int placedBombs = 0;
    //While the number of bombs placed is less than the required number of bombs
    while (placedBombs < BOMBS) {
        //generate random x,y coordinates within the board range and if a bomb has not been placed there, place a bomb
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (board[x][y] != 'X') {
            board[x][y] = 'X';
            placedBombs++;
        }
    }
}

//Function to check if the input entered by a user as a move is within the range of the board
int CheckValidMove(int x, int y) {
    return x>= 0 && x<SIZE && y>=0 && y<SIZE;
} 

//Function to count the bombs adjacent to a valid location entered by the user if it is not a bomb
int countAdjacentBombs(char board[SIZE][SIZE], int x, int y) {
    //Counter for number of bombs is initially zero
   int counter = 0; 
   //iterates through rows containing adjacent locations to the nput location
   for(int i=-1; i<=1; i++) {
    //iterates through rows containing adjacent locations to the nput location
    for(int j= -1 ;j <=1; j++) {
      if(CheckValidMove(x+i, y+j) && board[x+i][y+j]=='X') {
        //add 1 to the counter if a bomb is found in any adjacent locations
        counter++;
      }
    }
   }
   return counter; 
}

//Function to construct updated board after every valid attempt
void UpdateBoard(char board[SIZE][SIZE]) {
    //print the Column headers of the mineswweper board
    printf(" 0 1 2 3 4 5 6 7 8 9\n");
    //iterate through each row of the board array
    for (int x = 0; x < SIZE; x++) {
        //print the row index to help identify each row
        printf("%d ", x);
        //iterate through each column of a given row and print the correspond value at location [row, column]
        for(int y=0; y < SIZE; y++) {
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

int main() {
    char board[SIZE][SIZE];

    //Create the empty poard without any bombs at the start of the game
    for(int x = 0; x < SIZE; x++){
        for(int y = 0; y < SIZE; y++){
            board[x][y]='-';
        }
    }
    //Place the bombs 
    placeBombs(board);
    //Counter variable to keep track of how many cells are revealed
    int CellsRevealed = 0;
    //Bolean variable to change in any conditions that the game has to terminate
    int isGameOver = 0;

    //Run the game while checking all the necessary conditions to see if the user inputs are valid, and see if the game is over
    while(!isGameOver){
        UpdateBoard(board);
        int x,y;
        printf("Welcome to Minesweeper! Let the game begin!");
        printf("Enter Row and Column (0 to 9) seperated by a space: ");
        scanf("%d %d", &x, &y);

        if(!CheckValidMove(x,y)){
            printf("Invalid Move! \n Please enter a row and column between 0 to 9 without any additional characters and seperated by a single space\n");
            continue;
        }
        if (board[x][y] != '-' && board[x][y] != 'X') {
            printf("This cell is already revealed!\n");
            continue;
        }
        if(board[x][y]=='X'){
            printf("Game Over! You just hit a bomb.\n");
            isGameOver = 1;
        }
        else{
            int NumberOfBombs = countAdjacentBombs(board, x, y);
            board[x][y] = (char)(NumberOfBombs + '0');
            CellsRevealed++; 

            if(CellsRevealed == SIZE*SIZE-BOMBS){
                printf("Congratulations you won!");
                isGameOver = 1;
            }
        }
    }
    return 0;
}