#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef tree_h
#define tree_h

struct tree {
    int item;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

Tree *createEmptyTree();
Tree *createTree(int item, Tree *left, Tree *right);
int isEmpty(Tree *tree);
int binarySearch(Tree *root, int item);
Tree *insertNodeTree(Tree *tree, int item);
void preOrder(Tree *root);

#endif