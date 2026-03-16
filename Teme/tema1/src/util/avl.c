#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

bool isEmptyAVL(AVL *avl)
{
    return avl->root == NULL;
}

void updateHeight(TreeNode* node)
{
    node->height = 1+ max(height(node->left), height(node->right));
}

TreeNode* rotateLeft(TreeNode* node)
{
    TreeNode* y = node->right;
    TreeNode* T2 = y->left;

    y->left = node;
    node->right = T2;

    updateHeight(node);
    updateHeight(y);

    return y;
}

TreeNode* rotateRight(TreeNode* node)
{
    //printf("RIGHT\n");
    TreeNode* y = node->left;
    TreeNode* T3 = y->right;

    y->right = node;
    node->left = T3;

    updateHeight(node);
    updateHeight(y);

    return y;
}

TreeNode* rotateLR(TreeNode* node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

TreeNode* rotateRL(TreeNode* node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}



TreeNode* insert(TreeNode* node, const DataScheme* scheme, void* data)
{
    //Insert
    if (node == NULL)
    {
        node = (TreeNode*) malloc(sizeof(TreeNode));
        node->value = data;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;

        return node;
    }
    
    //Compare node values
    int comp = scheme->compare(data, node->value);

    if (comp > 0)
        node->right = insert(node->right, scheme, data);
    else if (comp < 0)
        node->left = insert(node->left, scheme, data);
    else
        return node; //Duplicate

    //Height update
    updateHeight(node);

    size_t heightLeft = height(node->left);
    size_t heightRight = height(node->right);

    //Balance factor
    int balanceFactor = heightLeft - heightRight;

    //Balancing
    if (balanceFactor > 1)
    {

        int compLeft = scheme->compare(data, node->left->value);

        //LL
        if (compLeft < 0)
            return rotateRight(node);
        //LR
        if (compLeft > 0)
            return rotateLR(node);
    }

    if (balanceFactor < -1)
    {

        int compRight = scheme->compare(data, node->right->value);

        //RR
        if (compRight > 0)
            return rotateLeft(node);
        //RL
        if (compRight < 0)
            return rotateRL(node);
        
    }

    return node;

}

void insertAVL(AVL *avl, void *data)
{
    
    if (avl->scheme == NULL)
    {
        printf("AVL data scheme not defined!\n");
        return;
    }

    avl->root = insert(avl->root, avl->scheme, data);
}

void insertCopyAVL(AVL *avl, const void *data)
{

    if (avl->scheme == NULL)
    {
        printf("AVL data scheme not defined!\n");
        return;
    }

    void* copy;
    avl->scheme->copy(&copy, data);
    insertAVL(avl, copy);
}

void printNodeAVL(TreeNode* node, DataScheme* scheme)
{
    if (node == NULL)
        return;
    scheme->print(node->value);
}

void printAVL(AVL *avl)
{
    if (avl->scheme == NULL)
    {
        printf("AVL data scheme not defined!\n");
        return;
    }

    reverseInOrder(avl->root, avl->scheme, &printNodeAVL);

}

void deleteAVL(AVL *avl)
{
    if (avl->scheme == NULL)
    {
        printf("AVL data scheme not defined!\n");
        return;
    }

    postOrder(avl->root, avl->scheme, &deleteNode);
}
