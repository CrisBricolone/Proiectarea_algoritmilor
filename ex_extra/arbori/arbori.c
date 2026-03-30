#include <stdio.h>
#include <stdlib.h>

typedef struct arbore_binar{
    struct arbore_binar *left, *right;
    int info;
} BIN_TREE_t;

void creareArboreBinar(BIN_TREE_t **root, int x) {
    if(x) {
        *root = malloc(sizeof(BIN_TREE_t));
        (*root)->info = x;
        (*root)->left = (*root)->right = NULL;

        int y;
        printf("Introduceti fiul STANG pentru nodul %d (0 pt NULL): ", x);
        scanf("%d", &y);
        creareArboreBinar(&(*root)->left, y);

        printf("Introduceti fiul DREPT pentru nodul %d (0 pt NULL): ", x);
        scanf("%d", &y);
        creareArboreBinar(&(*root)->right, y);
    }
    return;
}

void preOrder(BIN_TREE_t *root) {
    if(root != NULL) {
        printf("%d ", root->info);
        preOrder(root->left);
        preOrder(root->right);
    }

    return;
}

void postOrder(BIN_TREE_t *root) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->info);
    }

    return;
}

void inOrder(BIN_TREE_t *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->info);
        inOrder(root->right);
    }

    return;
}

void eliberareRecursiva(BIN_TREE_t **root) {
    if(*root != NULL) {
        eliberareRecursiva(&(*root)->left);
        eliberareRecursiva(&(*root)->right);
        printf("Eliminam nodul %d\n", (*root)->info);
        free(*root);
        *root = NULL;
    }

    return;
}

void eliminareSubArbore(BIN_TREE_t **current_node) {
    if(*current_node) {
        eliminareSubArbore(&(*current_node)->left);
        eliminareSubArbore(&(*current_node)->right);
        printf("Eliminam nodul %d\n", (*current_node)->info);
        free(*current_node);
        *current_node = NULL;
    }
    return;
}

BIN_TREE_t **gasireIndex(BIN_TREE_t **root, int x) {
    if(*root) {
        if((*root)->info == x)
            return root;
        else {
            return gasireIndex(&(*root)->left, x);
            return gasireIndex(&(*root)->right, x);
        }
    }
}

void gasireRootSubarbore(BIN_TREE_t **root) {
    int x;
    printf("Scrieti valoarea nodului radacina pt a elimina subarborele: ");
    scanf("%d", &x);

    eliminareSubArbore(gasireIndex(root, x));
    return;
}

BIN_TREE_t* gasireLCA(BIN_TREE_t *root, int x, int y) {
    // 1. Cazul de bază: am ajuns la capăt (frunză goală)
    if (root == NULL) {
        return NULL;
    }

    // 2. Am găsit unul dintre nodurile căutate! 
    // Returnăm propria adresă ca "semnal" către părinte.
    if (root->info == x || root->info == y) {
        return root;
    }

    // 3. Căutăm în stânga și în dreapta (Parcurgere de jos în sus)
    BIN_TREE_t *stanga = gasireLCA(root->left, x, y);
    BIN_TREE_t *dreapta = gasireLCA(root->right, x, y);

    // 4. AICI ESTE CONDIȚIA TA DE "2"!
    // Dacă am primit semnal (adrese non-NULL) din ambele părți, 
    // înseamnă că x e într-o parte și y în cealaltă. 
    // Deci EU (root-ul curent) sunt LCA-ul!
    if (stanga != NULL && dreapta != NULL) {
        return root;
    }

    // 5. Dacă am găsit doar pe o parte, pasăm acel semnal mai sus
    if (stanga != NULL) {
        return stanga;
    } else {
        return dreapta; // Poate fi un nod valid sau NULL, e ok oricum
    }
}

int main(void) {
    BIN_TREE_t *root = NULL;
    int x;
    
    creareArboreBinar(&root, 1);
    //inOrder(root);
    //printf("\n");
    //postOrder(root);
    //printf("\n");
    //preOrder(root);
    //printf("\n");

    //eliberareRecursiva(&root);
    //gasireRootSubarbore(&root);
    //preOrder(root);
    
    gasireLCA(root, x, y);

    return 0;
}