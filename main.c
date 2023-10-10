#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defining the variables size and bombs that are variables used throughout the program
#define SIZE 10
#define BOMBS 15

//Function to replace 15 random locations with "X" in the array to indicate a bomb
void placeBombs(char board[SIZE][SIZE]) {
    //Allows for seed value to be different every time so the sequence of random numbers generated is unique
    srand(time(NULL));
    //Number of bombs placed has to initially equal zero so bombs can start being placed
    int placedBombs = 0;
     //While the number of bombs placed is less than the required number of bombs generate random 
     //x,y coordinates within the board range and if a bomb has not been placed there, place a bomb
    while (placedBombs < BOMBS) {
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
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

//Function to count the bombs adjacent to a valid location entered by the user if it is not a bomb
int countAdjacentBombs(char board[SIZE][SIZE], int x, int y) {
    //Number of Bombs initially counted is zero
    int counter = 0;
    //Iterate through each row of the board
    for (int i = -1; i <= 1; i++) {
        //Iterate through each column of the board
        for (int j = -1; j <= 1; j++) {
            //If a location is valid and there is a bomb at that location add 1 to the counter
            if (CheckValidMove(x + i, y + j) && board[x + i][y + j] == 'X') {
                counter++;
            }
        }
    }
    return counter;
}

//Function to construct updated board after every valid attempt
void UpdateBoard(char board[SIZE][SIZE]) {
    //print the Column headers of the mineswweper board
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    //iterate through each row of the board array
    for (int x = 0; x < SIZE; x++) {
        //print the row index to help identify each row
        printf("%d ", x); 
        //iterate through each column of a given row and print the correspond value at location [row, column]
        for (int y = 0; y < SIZE; y++) {
            if (board[x][y] == 'X') {
                printf("- ");
            } else if (board[x][y] == '-') {
                printf("- ");
            } else {
                printf("%c ", board[x][y]);
            }
        }
        printf("\n");
    }
}

//Function to display final board when the game is over
void FinalBoard(char board[SIZE][SIZE]){
   //print the Column headers of the mineswweper board
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    //iterate through each row of the board array
    for (int x = 0; x < SIZE; x++) {
        //print the row index to help identify each row
        printf("%d ", x); 
        //iterate through each column of a given row and print the correspond value at location [row, column]
        for (int y = 0; y < SIZE; y++) {
            if (board[x][y] == 'X') {
                printf("X ");
            } else if (board[x][y] == '-') {
                printf("- ");
            } else {
                printf("%c ", board[x][y]);
            }
        }
        printf("\n");
    }
} 

int main() {
    char board[SIZE][SIZE];
    //Create the empty poard without any bombs at the start of the game
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            board[x][y] = '-';
        }
    }
    //Place the bombs 
    placeBombs(board);
    //Counter variable to keep track of how many cells are revealed
    int CellsRevealed = 0;
    //Bolean variable to change in any conditions that the game has to terminate
    int GameNotOver = 0;

    printf("Welcome to Minesweeper! Let the game begin!\n");
    while (GameNotOver == 0) {
        //Displays the updated board to the user which includes their most recent move
        UpdateBoard(board);
        int x, y;
        //Asks for user input which is the location the user wishes to reveal (a.k.a their move)
        printf("Enter Row and Column (0 to 9) separated by a space: ");
        scanf(" %d %d", &x, &y);

        //Checks if the move made by the user is valid, if not, asks them to enter another move
        if (!CheckValidMove(x, y)) {
            printf("Invalid Move! Please enter a row and column between 0 to 9 separated by a single space.\n");
            continue;
        }
        //Checks if the move made by the user is for a cell they have already revealed, if yes, then they are asked to make another move
        if (board[x][y] != '-' && board[x][y] != 'X') {
            printf("This cell is already revealed! Please enter a new move!\n");
            continue;
        }
        //Ends the game in the scenario where the user entered a location where there is a bomb
        if (board[x][y] == 'X') {
            printf("Game Over! You just hit a bomb.\n");
            FinalBoard(board);
            GameNotOver = 1;
        //This statement replaces the entered location's '-' with the number of bombs found in adjacent locations 
        //if the cell revelaed is not a bomb
        } else {
            int NumberOfBombs = countAdjacentBombs(board, x, y);
            board[x][y] = (char)(NumberOfBombs + '0');
            CellsRevealed++;
            //Checks if all the cells without bombs have been revelaed. If yes, the game is over and the user won
            if (CellsRevealed == SIZE * SIZE - BOMBS) {
                printf("Congratulations, you won!\n");
                FinalBoard(board);
                GameNotOver = 1;
            }
        }
    }
    return 0;
}