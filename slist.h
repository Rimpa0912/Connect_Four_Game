/*
 * slist.h
 */

#ifndef SLIST_H
#define SLIST_H

#define ROWS 6
#define COLS 7

//Define a struct to represent a node in a singly-linked list of game moves
struct Node {
    char board[ROWS][COLS];
    char player; //The player who moved ('R' for Red, 'Y' for Yellow)
    int column; //Column in which the move was made
    struct Node* next; //Pointer to the next node in the list
};

//Function to create a new node and initialize its values
struct Node* createNode(char board[ROWS][COLS], char player, int column);

//Function to insert a new node at the beginning of the linked list
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column);

//Function to free the memory taken up by the linked list
void freeList(struct Node** head);

#endif
