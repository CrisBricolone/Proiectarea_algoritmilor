#ifndef DATA_H
#define DATA_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

typedef void    (*copyFunc)     (void** dest, const void* src);
typedef void    (*freeFunc)     (void* data);
typedef void    (*initFunc)     (void** ptr, ...);
typedef void    (*printFunc)    (const void* data);
typedef int     (*compareFunc)  (const void* item1, const void* item2);

#define EPSILON 1e-2

typedef struct
{
    initFunc init;
    freeFunc free;
    copyFunc copy;
    printFunc print;
    compareFunc compare;
} DataScheme;

typedef struct SimpleNode
{
    void* value;
    struct SimpleNode* next;
} SimpleNode;

typedef struct DoubleNode
{
    void* value;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;

typedef struct TreeNode
{
    int height; //added to reuse structure for BST and AVL
    void* value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef void (*treeIterator)(TreeNode* node, const DataScheme* scheme);

void reverseList(SimpleNode** head);

void preOrder(TreeNode* root, const DataScheme* scheme, treeIterator iteratorFunc);

void inOrder(TreeNode* root, const DataScheme* scheme, treeIterator iteratorFunc);

void postOrder(TreeNode* root, const DataScheme* scheme, treeIterator iteratorFunc);

void reverseInOrder(TreeNode* root, const DataScheme* scheme, treeIterator iteratorFunc);

bool isInterior(TreeNode* node);

bool isLeaf(TreeNode* node);

int height(TreeNode* root);


void deleteNode(TreeNode* node, const DataScheme* scheme);

#endif //DATA_H