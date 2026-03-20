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
    return;
}

int main(int argc, char **argv) {
    Node *head_1 = NULL, *head_2 = NULL;
    int n, m;

    list_create(&n, &head_1);
    disp_list(head_1);

    return 0;
}