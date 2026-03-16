#ifndef BST_H
#define BST_H

#include "data.h"
#include <stdbool.h>

typedef struct
{
    TreeNode* root;
    const DataScheme* scheme;
} BST;

bool isEmptyBST(BST* bst);

void insertBST(BST* bst, void* data);

void insertCopyBST(BST* bst, const void* data);

void printBST(BST* bst);

void deleteBST(BST* bst);


#endif //BST_H