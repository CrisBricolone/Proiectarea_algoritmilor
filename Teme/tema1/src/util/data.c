#include "data.h"

#include <stdlib.h>
#include <stdio.h>

void reverseList(SimpleNode** head)
{
    SimpleNode* prev = NULL;
    SimpleNode* curr = *head;
    SimpleNode* next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;

        curr = next;
    }

    *head = prev;
}

void preOrder(TreeNode *root, const DataScheme *scheme, treeIterator iteratorFunc)
{
    if (root)
    {
        iteratorFunc(root, scheme);
        preOrder(root->left, scheme, iteratorFunc);
        preOrder(root->right, scheme, iteratorFunc);
    }
}

void inOrder(TreeNode *root, const DataScheme* scheme, treeIterator iteratorFunc)
{
    if (root)
    {
        inOrder(root->left, scheme, iteratorFunc);
        iteratorFunc(root, scheme);
        inOrder(root->right, scheme, iteratorFunc);
    }
}

void postOrder(TreeNode *root, const DataScheme* scheme, treeIterator iteratorFunc)
{
    if (root)
    {
        postOrder(root->left, scheme, iteratorFunc);
        postOrder(root->right, scheme, iteratorFunc);
        iteratorFunc(root, scheme);
    }
}

void reverseInOrder(TreeNode *root, const DataScheme *scheme, treeIterator iteratorFunc)
{
    if (root)
    {
        reverseInOrder(root->right, scheme, iteratorFunc);
        iteratorFunc(root, scheme);
        reverseInOrder(root->left, scheme, iteratorFunc);
    }
}

bool isInterior(TreeNode *node)
{
    return (node->left != NULL || node->right != NULL);
}

bool isLeaf(TreeNode *node)
{
    return (node->left == NULL && node->right == NULL);
}

int height(TreeNode *root)
{
    if (root == NULL) 
        return -1;

    return root->height;
}

void deleteNode(TreeNode* node, const DataScheme* scheme)
{
    if (node == NULL)
        return;
    scheme->free(node->value);
    free(node);
}

