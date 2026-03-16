#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include "team.h"


int isStackEmpty(Stack* stack)
{
    return stack->top == NULL;
}

void push(Stack* stack, void* data)
{
    
    SimpleNode* node = (SimpleNode*) malloc(sizeof(SimpleNode));
    node->value = data;
    node->next = stack->top;
    stack->top = node;
}

void pushCopy(Stack* stack, void* data)
{
    if (stack->scheme == NULL)
    {
        printf("Stack data scheme not defined!\n");
        return;
    }
    SimpleNode* node = (SimpleNode*) malloc(sizeof(SimpleNode));

    node->value = NULL;
    stack->scheme->copy(&node->value, data);
    node->next = stack->top;
    stack->top = node;
}


//Not needed anymore, just use the same pointer, use scheme to copy when needed
// void popCopy(Stack* stack, void** data)
// {
//     if (data == NULL)
//     {
//         printf("Pointer must not be null to copy!\n");
//         return;
//     }
//     if (stack->scheme == NULL)
//     {
//         printf("Stack data scheme not defined!\n");
//         return;
//     }

//     
//     // if (isStackEmpty(stack)) return;

//     // SimpleNode* stackTop = stack->top;

//     //  //Allows null calls when we don't want to get the value, just pop
//     // stack->scheme->copy(data, stackTop->value);

//     // stack->top = stack->top->next;
//     // // if (stack->scheme == &teamScheme)
//     // // {
//     // //     //printf("next: %X\n", stack->top);
//     // //     //printf("removed: %s\n", ((Team*)stackTop->value)->name);
//     // // }

//     // stack->scheme->free(stackTop->value);
//     // free(stackTop);
// }

void pop(Stack* stack, void** data)
{
    if (isStackEmpty(stack)) return;
    SimpleNode* stackTop = stack->top;

    if (data != NULL) //Allows null calls when we don't want to get the value, just pop
        *data = stackTop->value;
    else //data needs to freed
        stack->scheme->free(stackTop->value);

    stack->top = stack->top->next;
    free(stackTop); //free node but not data inside
}

void top(Stack* stack, void* data)
{
    if (stack->scheme == NULL)
    {
        printf("Stack data scheme not defined!\n");
        return;
    }

    if (isStackEmpty(stack)) return;

    data = stack->top->value;
}

void deleteStack(Stack* stack)
{
    if (stack->scheme == NULL)
    {
        printf("Stack data scheme not defined!\n");
        return;
    }

    while (!isStackEmpty(stack))
        pop(stack, NULL);

}

void printStack(Stack* stack)
{
    if (stack->scheme == NULL)
    {
        printf("Stack data scheme not defined!\n");
        return;
    }

    if (isStackEmpty(stack))
        return;

    SimpleNode* current = stack->top;
    while (current != NULL)
    {
        stack->scheme->print(current->value);

        current = current->next;
    }

}

void copyStack(Stack *dest, Stack *src)
{
    if (dest->scheme == NULL || src->scheme == NULL)
    {
        printf("Stack data scheme not defined!\n");
        return;
    }

    if (dest->scheme != src->scheme)
    {
        printf("Stacks do not use the same data scheme!\n");
        return;
    }

    SimpleNode* srcHead = src->top;

    while (srcHead != NULL)
    {
        void* dat;
        dest->scheme->copy(&dat, srcHead->value);
        push(dest, dat);
        srcHead = srcHead->next;
    }

}
