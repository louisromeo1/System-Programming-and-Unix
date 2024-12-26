#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *create_queue();
void free_queue(Queue *queue);
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
int is_queue_empty(Queue *queue);

#endif
