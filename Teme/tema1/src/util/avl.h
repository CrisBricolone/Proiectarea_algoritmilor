#ifndef AVL_H
#define AVL_H

#include "data.h"

typedef struct
{
    TreeNode* root;
    const DataScheme* scheme;
} AVL;

bool isEmptyAVL(AVL* avl);

void insertAVL(AVL* avl, void* data);

void insertCopyAVL(AVL* avl, const void* data);

void printAVL(AVL* avl);

void deleteAVL(AVL* avl);

#endif //AVL_H