/*
* File: count2.c
* Author: Louis Romeo
* Purpose:
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newNode->value = value;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a value into the linked list in sorted order
Node* insertOrIncrement(Node *head, int value) {
    Node *prev = NULL, *current = head;

    // Traverse to find the correct insertion point or existing node
    while (current != NULL && current->value < value) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->value == value) {
        current->count++;
        return head;
    }

    Node *newNode = createNode(value);
    if (prev == NULL) {
        newNode->next = head;
        return newNode;
    }

    newNode->next = current;
    prev->next = newNode;
    return head;
}

// Function to free the linked list
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int number;
    Node *head = NULL;

    // Use scanf in a loop to read one integer at a time
    while (scanf("%d", &number) == 1) {
        head = insertOrIncrement(head, number);
    }

    // Check for any non-integer input, print error message, and exit if found
    if (!feof(stdin)) {
        fprintf(stderr, "Error: non-integer input encountered\n");
        freeList(head);
        return 1;
    }

    // Print the list in ascending order
    Node *current = head;
    while (current != NULL) {
        printf("%d %d\n", current->value, current->count);
        current = current->next;
    }

    freeList(head);
    return 0;
}
