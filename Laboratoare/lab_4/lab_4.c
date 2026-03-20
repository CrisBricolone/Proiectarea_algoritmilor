#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct lista_inlantuita{
    int val;
    struct lista_inlantuita *urm;
} Node;

void new_node(Node **head, int val) {
    Node *nod_nou = (Node*)malloc(sizeof(Node));    
    nod_nou->val = val;

    if(!*head)
        *head = nod_nou;
    else{
        Node *tmp_node = *head;
        while(tmp_node->urm) 
            tmp_node = tmp_node->urm;
        tmp_node->urm = nod_nou;
    }
    nod_nou->urm = NULL;
    return;
}

Node* swap_func(Node *head, Node *prev) {
    Node* second = prev->urm;
    Node* second_next = second->urm;
    second->urm = head->urm;
    head->urm = second_next;
    prev->urm = head;
    return second;
}

Node* star_transposition(Node *head) {
    srand(time(NULL));
    int poz = rand() % 14;
    if(!poz)
        return head;

    printf("Pozitia obtinuta este: %d\n\n", poz);
    Node *tmp = head;

    while(poz > 2) {
        tmp = tmp->urm;
        poz--;    
    }

    head = swap_func(head, tmp);
    return head;
}

void random_2_random(Node* head){
    srand(time(NULL));
    int poz1 = rand() % 14;
    int poz2 = rand() % 14;

    Node *prev = head;
    while(poz1 > 2) {
        prev = prev->urm;
        poz1--;
    }

    Node *del_node = prev->urm;
    prev->urm = prev->urm->urm;

    prev = head;
    while(poz2 > 2) {
        prev = prev->urm;
        poz2--;
    }

    del_node->urm = prev->urm;
    prev->urm = del_node->urm;

    return;
}

int main(int argc, char **argv) {
    Node *head = NULL;

    for(int i = 1; i <= 14; i++)
        new_node(&head, i);

    head = star_transposition(head);

    while(head->urm) {
        printf("valoare: %d\n adresa: %p\n\n", head->val, head->urm);
        head = head->urm;
    }

    random_2_random(head);

    while(head->urm) {
        printf("valoare: %d\n adresa: %p\n\n", head->val, head->urm);
        head = head->urm;
    }
    return 0;
}