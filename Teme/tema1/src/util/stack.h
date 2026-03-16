#ifndef STACK_H
#define STACK_H

#include "data.h"

typedef struct Stack
{
    SimpleNode* top;
    const DataScheme* scheme;
} Stack;

int isStackEmpty(Stack* stack);

void push(Stack* stack, void* data);

void pushCopy(Stack* stack, void* data);

//Not needed anymore, just use the same pointer, use scheme to copy when needed
//void popCopy(Stack* stack, void** data);

void pop(Stack* stack, void** data);

void top(Stack* stack, void* data);

void deleteStack(Stack* stack);

void printStack(Stack* stack);

void copyStack(Stack* dest, Stack* src);

#endif //STACK_H