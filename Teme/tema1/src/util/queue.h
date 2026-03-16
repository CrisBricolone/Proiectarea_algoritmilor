#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"

typedef struct
{
    SimpleNode* front;
    SimpleNode* back;
    const DataScheme* scheme;
} Queue;

int isQueueEmpty(Queue* queue);

void enQueue(Queue* queue, void* data);

void enQueueCopy(Queue* queue, void* data);

void deQueue(Queue* queue, void** data);

void deleteQueue(Queue* queue);

void printQueue(Queue* queue);

#endif //QUEUE_H