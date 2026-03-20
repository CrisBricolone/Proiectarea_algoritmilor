#include <stdio.h>
#include <stdlib.h>
#define DYN_ERROR 61

typedef struct linked_list{
    int info;
    struct linked_list *next;
} Node;

void list_create(int *list_s, Node **head); //creating list with a given number of elements
void verify_alloc(const void *p); //checks dynamic mem allocation
void disp_list(Node *head); //displays the elements of the list
Node* task1_interclass(Node *head_1, Node *head_2); //interclasare pe liste 
void task3_remove_k_elem(Node **head_1); // sterge elementul al k-lea de la dreapta spre stanga
Node* task2_interclass_no_cpy(Node *head_1, Node *head_2); //interclasare care realizeaza intersectia celor doua multimi

void verify_alloc(const void *p) {
    if(!p) 
        exit(DYN_ERROR);
    return;
}

void list_create(int *list_s, Node **head) {
    static int index = 0;
    ++index;

    printf("Introduce size of list %d: ", index);
    scanf("%d", list_s);

    printf("Introduce %d elements:\n", *list_s);
    int x;
    for(int i = 0; i < *list_s; i++) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        verify_alloc(new_node);
        scanf("%d", &x);
        new_node->info = x;

        if(!*head)
            *head = new_node;
        else {
            Node *tmp_head = *head;
            while(tmp_head->next)
                tmp_head = tmp_head->next;

            tmp_head->next = new_node;
        } 

        new_node->next = NULL;
    }
    return;
}

void disp_list(Node *head){
    while(head) {
        printf("valoare: %d\nadresa curenta: %p\nadresa urmatoare: %p\n\n", head->info, head, head->next);
        head = head->next;
    }
    printf("-------------------------------------------------------------------------\n");

    return;
}

Node* task1_interclass(Node *head_1, Node *head_2) {
    Node *interclas = NULL;
    Node *tail = NULL;
    int cnt = 0;

    while(head_1 && head_2) {
        Node *new_node = (Node*)malloc(sizeof(Node));

        if(cnt % 2){
            new_node = head_2;
            head_2 = head_2->next;
        }
        else {
            new_node = head_1;
            head_1 = head_1->next;
        }
        
        if(!interclas){
            interclas = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = tail->next;
        }
        
        cnt++;
    }

    if(head_1)
        tail->next = head_1;

    if(head_2)
        tail->next = head_2;

    return interclas;
}

Node* task2_interclass_no_cpy(Node *head_1, Node *head_2) {
    Node *new_head = NULL;
    Node *tail = NULL;
    Node *prev = NULL;
    Node *current_node;

    while(head_1 && head_2) {
        if (head_1->info < head_2->info)
            if(!prev || prev->info != head_1->info) {
                current_node = head_1;
                head_1 = head_1->next;
            }
            else
                head_1 = head_1->next;
        else
            if(!prev || prev->info != head_2->info) {
                current_node = head_2;
                head_2 = head_2->next;
            }
            else
                head_2 = head_2->next;

        if(!new_head) {
            new_head = current_node;
            tail = current_node;
        }
        else {
            tail->next = current_node;
            tail = tail->next;
        }

        prev = current_node;
    }

    if(head_1)
        tail->next = head_1;
    if(head_2)
        tail->next = head_2;

    return new_head;
} 

void task3_remove_k_elem(Node **head_1) {
    int k;
    printf("Care este pozitia elementului pe care vrei sa-l stergi(de la stanga la dreapta): ");
    scanf("%d", &k);

    int nr_elem = 0;
    Node* head_cpy = *head_1;
    for(;head_cpy; nr_elem++, head_cpy = head_cpy->next);

    int actual_poz = nr_elem - k;

    if(!actual_poz) {
        *head_1 = (*head_1)->next;
        return;
    }

    head_cpy = *head_1;
    for(;actual_poz > 1 && head_cpy; actual_poz--, head_cpy = head_cpy->next);

    Node *deleted = head_cpy->next;
    head_cpy->next = head_cpy->next->next;
    free(deleted);

    return;
}


int main(int argc, char **argv) {
    Node *head_1 = NULL, *head_2 = NULL, *head_interclas = NULL, *head_interclas_no_cpy;
    int n, m;

    list_create(&n, &head_1);
    list_create(&n, &head_2);

    disp_list(head_1);
    disp_list(head_2);

    task3_remove_k_elem(&head_1);
    disp_list(head_1);

    //head_interclas_no_cpy = task2_interclass_no_cpy(head_1, head_2);
    //disp_list(head_interclas_no_cpy);

    //aceasta variantra strica listele initiale. daca vrem sa nu le stricam trb sa cream noduri noi pentru head_interclas si sa copeim valorile din noduri
    //head_interclas = task1_interclass(head_1, head_2);
    //disp_list(head_interclas);

    return 0;
}