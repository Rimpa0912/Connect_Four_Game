/*
 * slist.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

//Function to create a new node and initialize its values
struct Node* createNode(char board[ROWS][COLS], char player, int column) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // Allocates memory for the new node
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

//Copies the game board configuration, player, and column to the new node
    memcpy(newNode->board, board, sizeof(char) * ROWS * COLS);
    newNode->player = player;
    newNode->column = column;
    newNode->next = NULL;

    return newNode;
}

//Function to insert a new node at the end of the linked list
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column) {
    struct Node* newNode = createNode(board, player, column); //Creates a new node

    // If the linked list is empty then make the new node the head
    if (*head == NULL) {
        *head = newNode;
    } else { //Traverse through the list to find the last node
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; //Inserts the new node at the end
    }
}

//Function to free the entire linked list
void freeList(struct Node** head) {
    struct Node* current = *head; //Starts with the head of the list
    while (current != NULL) {
        struct Node* next = current->next; //Keeps a reference to the next node
        free(current); //Frees the current node
        current = next; //Moves to the next node
    }
    *head = NULL; //Sets the head to NULL to indicate an empty list
}
