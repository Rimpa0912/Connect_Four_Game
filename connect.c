/*
 * connect.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];
int row;
int col;
enum Player {Red, Yellow}; // Enumeration for the players Red and Yellow

//Function to initialize the game board
void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' '; //Fills the game board with empty spaces throughout
        }
    }
}

//Function to display the game board, which includes the player tokens and separators
void displayBoard(const char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", board[i][j]); //Prints '|' separators on the game board to separate the columns
        }
        printf("|\n");
    }
    printf("===============\n"); //Prints the base of the board
}

//Function to check if a player has won
int checkWin(const char board[ROWS][COLS], enum Player player, int row, int col) {
    char playerSign = (player == Red) ? 'R' : 'Y';

    //Checks the tokens horizontally
    int count = 0;
    for (int i = col - 3; i <= col; i++) {
        if (i >= 0 && i + 3 < COLS) {
            int win = 1;
            for (int j = 0; j < 4; j++) {
                if (board[row][i + j] != playerSign) {
                    win = 0;
                    break;
                }
            }
            if (win) return 1;
        }
    }

    //Checks the tokens vertically
    count = 0;
    for (int i = row - 3; i <= row; i++) {
        if (i >= 0 && i + 3 < ROWS) {
            int win = 1;
            for (int j = 0; j < 4; j++) {
                if (board[i + j][col] != playerSign) {
                    win = 0;
                    break;
                }
            }
            if (win) return 1;
        }
    }

    //Checks the tokens diagonally (bottom-left to top-right)
    count = 0;
    for (int i = -3; i <= 0; i++) {
        if (row + i >= 0 && row + i + 3 < ROWS && col + i >= 0 && col + i + 3 < COLS) {
            int win = 1;
            for (int j = 0; j < 4; j++) {
                if (board[row + i + j][col + i + j] != playerSign) {
                    win = 0;
                    break;
                }
            }
            if (win) return 1;
        }
    }

    //Checks the tokens diagonally (bottom-right to top-left)
    count = 0;
    for (int i = -3; i <= 0; i++) {
        if (row - i >= 0 && row - i - 3 < ROWS && col + i >= 0 && col + i + 3 < COLS) {
            int win = 1;
            for (int j = 0; j < 4; j++) {
                if (board[row - i - j][col + i + j] != playerSign) {
                    win = 0;
                    break;
                }
            }
            if (win) return 1;
        }
    }

    return 0; //No player has won
}

//Function to reset the game board completely
void resetGame(char board[ROWS][COLS], struct Node** movesList, enum Player* currentPlayer) {
    initializeBoard(board); // Resets the game board,
    freeList(movesList); //Frees the linked list of moves
    *currentPlayer = (currentPlayer == 'R') ? 'R' : 'Y'; //Makes sure that Red always starts the game
}

//The main method
int main() {
    enum Player currentPlayer = Red;
    int moves = 0;
    struct Node* movesList = NULL;

    //Display the Welcome message
    printf("Welcome! Press 'q' to quit or any other key to continue:\n");
    char decision;
    scanf(" %c", &decision);

    //When the players want to play the game
    if (decision != 'q') {
        while (1) {
            initializeBoard(board); // Initialize a new game board
            displayBoard(board);

            while (1) {
                printf("%s to play. Pick a column (1-7):", (currentPlayer == Red) ? "Red" : "Yellow");
                scanf("%d", &col);
                col--;

                //Checks if the move is valid or not
                if (col < 0 || col >= COLS || board[0][col] != ' ') {
                    printf("Invalid move. Try again.\n");
                    continue;
                }

                //Finds the empty row in the chosen column
                for (row = ROWS - 1; row >= 0; row--) {
                    if (board[row][col] == ' ') {
                        board[row][col] = (currentPlayer == Red) ? 'R' : 'Y';
                        break;
                    }
                }

                insertNode(&movesList, board, currentPlayer, col); //Adds the move to the linked list
                displayBoard(board);

                //When a  player has won the game
                if (checkWin(board, currentPlayer, row, col)) {
                    printf("You win, %s!\n", (currentPlayer == Red) ? "Red" : "Yellow");
                    printf("Good game!\n");

                    char playerChoice;
                    printf("Press 'q' to quit or 'r' to replay or any other key to continue:\n");
                    scanf(" %c", &playerChoice);

                    //The player wants to quit the game
                    if (playerChoice == 'q') {
                        freeList(&movesList); // Free the linked list
                        exit(0); // Quit the program

                    //The player wants to replay the game
                    } else if (playerChoice == 'r') {
                        struct Node* currentMove = movesList;
                        while (currentMove != NULL) {
                            displayBoard(currentMove->board);
                            currentMove = currentMove->next;
                        }
                        printf("Press 'q' to quit or any other key to continue: ");
                        char replay;
                        scanf(" %c", &replay);
                        if (replay == 'q') {
                            freeList(&movesList); // Frees the linked list
                            exit(0); // Quit
                        }
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);

                    //The player wants to continue playing
                    } else {
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);
                    }
                }

                //Checks whether there is a draw
                if (moves == ROWS * COLS) {
                    printf("It's a draw!\n");
                    break;
                }

                //Switches between the players
                currentPlayer = (currentPlayer == Red) ? Yellow : Red;
                moves++;
            }
        }
    }
    return 0;
}
