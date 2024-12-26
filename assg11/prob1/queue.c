/*
* File: queue.c
* Author: Louis Romeo
* Purpose: Implements a linked-list-based queue used for breadth-first
* search in the graph traversal.
*/
#include "queue.h"
#include <stdlib.h>
#include <string.h>

Queue *create_queue() {
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = queue->rear = NULL;
    return queue;
}

void free_queue(Queue *queue) {
    while (queue->front) {
        QueueNode *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
    free(queue);
}

void enqueue(Queue *queue, void *data) {
    QueueNode *node = malloc(sizeof(QueueNode));
    if (!node) return;
    node->data = data;
    node->next = NULL;
    if (!queue->rear) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
}

void *dequeue(Queue *queue) {
    if (!queue->front) return NULL;
    QueueNode *node = queue->front;
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    void *data = node->data;
    free(node);
    return data;
}

int is_queue_empty(Queue *queue) {
    return queue->front == NULL;
}
