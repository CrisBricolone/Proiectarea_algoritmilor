#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

bool isEmptyBST(BST *bst)
{
    return bst->root == NULL;
}

//Iterative

void insertBST(BST *bst, void *data)
{
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    if (bst->root == NULL)
    {
        bst->root = node;
        return;
    }

    if (bst->scheme == NULL)
    {
        printf("BST data scheme not defined!\n");
        return;
    }

    TreeNode* current = bst->root;

    while (current != NULL)
    {
        //Compare nodes
        int comp = bst->scheme->compare(node->value, current->value);

        if (comp == 0) //Duplicate
        {
            free(node);
            return;
        }

        if (comp > 0)
        {
            if (current->right == NULL)
            {
                current->right = node;
                return;
            }
            else
                current = current->right;
                
        } else
        {
            if (current->left == NULL)
            {
                current->left = node;
                return;
            } else
                current = current->left;
        }
    }

}

void insertCopyBST(BST *bst, const void *data)
{
    if (bst->scheme == NULL)
    {
        printf("BST data scheme not defined!\n");
        return;
    }

    void* copy;
    bst->scheme->copy(&copy, data);

    insertBST(bst, copy);

}

void printNodeBST(TreeNode* node, DataScheme* scheme)
{
    if (node == NULL)
        return;
    scheme->print(node->value);
}

void printBST(BST *bst)
{
    if (bst->scheme == NULL)
    {
        printf("BST data scheme not defined!\n");
        return;
    }

    reverseInOrder(bst->root, bst->scheme, &printNodeBST);

}

void deleteBST(BST *bst)
{
    if (bst->scheme == NULL)
    {
        printf("BST data scheme not defined!\n");
        return;
    }

    postOrder(bst->root, bst->scheme, &deleteNode);
}
