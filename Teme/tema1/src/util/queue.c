#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

int isQueueEmpty(Queue *queue)
{
    return (queue->front == NULL);
}


void enQueue(Queue* queue, void *data)
{
    if (isQueueEmpty(queue)) //in case the queue is reused, to avoid circularity
        queue->back = NULL;

    SimpleNode* node = (SimpleNode*) malloc(sizeof(SimpleNode));

    node->value = data;
    node->next = NULL;

    if (queue->back == NULL)
        queue->back = node;
    else
    {
        queue->back->next = node;
        queue->back = node;
    }

    if (queue->front == NULL)
        queue->front = queue->back;

}

void enQueueCopy(Queue* queue, void* data)
{
    if (queue->scheme == NULL)
    {
        printf("Queue data scheme not defined!\n");
        return;
    } 
    if (isQueueEmpty(queue)) //in case the queue is reused, to avoid circularity
        queue->back = NULL;

    SimpleNode* node = (SimpleNode*) malloc(sizeof(SimpleNode));

    node->value = NULL;

    queue->scheme->copy(&(node->value), data); //no copy

    node->next = NULL;

    if (queue->back == NULL)
        queue->back = node;
    else
    {
        queue->back->next = node;
        queue->back = node;
    }

    if (queue->front == NULL)
        queue->front = queue->back;
}


//Not needed anymore, just use the same pointer, use scheme to copy when needed
// void deQueueCopy(Queue* queue, void** data)
// {
//     if (queue->scheme == NULL)
//     {
//         printf("Queue data scheme not defined!\n");
//         return;
//     } 

//     if (isQueueEmpty(queue))
//         return;

//     SimpleNode* front = queue->front;

//     if (data != NULL)//Allows null calls when we don't want to get the value, just dequeue
//         queue->scheme->copy(data, front->value);

//     //printf("next is: %X\n", queue->front->next);
//     queue->front = queue->front->next;
//     queue->scheme->free(front->value);
//     free(front);

// }

void deQueue(Queue* queue, void** data)
{
    if (isQueueEmpty(queue))
        return;

    SimpleNode* front = queue->front;

    if (data != NULL) //Allows null calls when we don't want to get the value, just dequeue
        *data = front->value;
    else //data needs to be freed
        queue->scheme->free(front->value);

    queue->front = queue->front->next;
    free(front); //Free node, but not value

}

void deleteQueue(Queue *queue)
{
    if (queue->scheme == NULL)
    {
        printf("Queue data scheme not defined!\n");
        return;
    } 
    
    while (!isQueueEmpty(queue))
        deQueue(queue, NULL);
}


void printQueue(Queue *queue)
{
    if (queue->scheme == NULL)
    {
        printf("Queue data scheme not defined!\n");
        return;
    } 
    if (isQueueEmpty(queue))
        return;

    SimpleNode* current = queue->front;
    while (current != NULL)
    {
        queue->scheme->print(current->value);
        current = current->next;
    }
}
