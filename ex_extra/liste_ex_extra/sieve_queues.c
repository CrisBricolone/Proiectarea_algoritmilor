#include <stdio.h>
#include <stdlib.h>
#define DYN_ALLOC 61

typedef struct list_queue{
    int info;
    struct list_queue *next;
} QUEUE_t;

typedef struct list_stack{
    int info;
    struct list_stack *next;
} STACK_t;

STACK_t* create_stack(STACK_t *top) {
    int n;
    static int cnt = 0;
    printf("What is the size of stack %d?", ++cnt);
    scanf("%d", &n);

    printf("Introduce elements in the stack!\n");
    for(int i = 0; i < n; i++) {
        STACK_t *new_node = (STACK_t*)malloc(sizeof(STACK_t));
        scanf("%d", &(new_node->info));

        if(!top)
            top = new_node;
        else {
            new_node->next = top;
            top = new_node;
        }
    }   

    return top;
} 

QUEUE_t *create_queue(QUEUE_t *tail) {
    int n;
    static int cnt = 0;
    printf("What is the size of stack %d?", ++cnt);
    scanf("%d", &n);

    printf("Introduce elements in the stack!\n");
    for(int i = 0; i < n; i++) {
        QUEUE_t *new_node = (QUEUE_t*)malloc(sizeof(QUEUE_t));
        scanf("%d", &(new_node->info));

        if(!tail)  
            tail = new_node;
        else {
            QUEUE_t *tail_cpy = tail;
            while(tail_cpy->next) 
                tail_cpy = tail_cpy->next;
            tail_cpy->next = new_node;
        }

        new_node->next = NULL;
    }
    return tail;
}

void disp_queue(QUEUE_t *rear) {
    printf("Elements of the stack:\n");
    while(rear){
        printf("%d ", rear->info);
        rear = rear->next;
    }
    printf("\n-----------------------=================-----------------------\n");
    return;
}

STACK_t* interclas_stacks(STACK_t *s1, STACK_t *s2) {
    int parity = 1;
    STACK_t *new_sieve = NULL, *current_node;
    while(s1 && s2) {
        if(parity % 2) {
            current_node = s1;
            s1 = s1->next;
        }
        else {
            current_node = s2;
            s2 = s2->next;
        }

        if(!new_sieve) {
            new_sieve = current_node;
            current_node->next = NULL;
        }
        else {
            current_node->next = new_sieve;
            new_sieve = current_node;
        }
        parity++;
    }

    while(s1){
        current_node = s1;
        s1 = s1->next;
        current_node->next = new_sieve;
        new_sieve = current_node;
    }

    while(s2){
        current_node = s2;
        s2 = s2->next;
        current_node->next = new_sieve;
        new_sieve = current_node;
    }

    return new_sieve;
}

void disp_stack(STACK_t *top) {
    printf("Elements of the stack:\n");
    while(top){
        printf("%d\n", top->info);
        top = top->next;
    }
    printf("-----------------------=================-----------------------\n");
    return;
}

void pop(STACK_t **top){
    if(!top) {
        printf("Stack is already empty!\n");
        return;
    }
    
    STACK_t *current_node = *top;
    (*top) = current_node->next;
    free(current_node);

    return;
}

void push(STACK_t **top, int x) {
    STACK_t *new_node = (STACK_t*)malloc(sizeof(STACK_t));
    new_node->info = x;
    if(!*top) {
        *top = new_node;
    }
    else{
        new_node->next = *top;
        *top = new_node;
    }
    return;
}

void reverse_stack(STACK_t **top) {
    STACK_t *reverse_s = NULL;

    if(!reverse_s) {
        reverse_s = *top;
        pop(top);
    }
    return;
}

int main(void) {
    STACK_t *s1 = NULL, *s2 = NULL, *s3 = NULL;
    QUEUE_t *q1 = NULL;

    s1 = create_stack(s1);
    //s2 = create_stack(s2);

    //disp_stack(s1);
    //disp_stack(s2);

    //s3 = interclas_stacks(s1, s2);
    //disp_stack(s3);

    //q1 = create_queue(q1);
    //disp_queue(q1);

    disp_stack(s1);
    reverse_stack(&s1);
    disp(s1);

    return 0;
}