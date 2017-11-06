#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree {
    int item;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;


// FUNCTION CREATEEMPITYTREE
// CREATES A EMPTY TREE (NULL POINTER)
Tree *createEmptyTree() {
    return NULL;
}

// FUNCTION CREATETREE
// CREATES A NON-NULL TREE, WITH HER ITEM AND POINTERS
Tree *createTree(int item, Tree *left, Tree *right) {
    Tree *tree = (Tree*) malloc(sizeof(Tree));
    tree->item = item;
    tree->left = left;
    tree->right = right;
}

// FUNCTION ISEMPTY
// VERIFIES IF THE TREE IS EMPTY (NULL POINTER)
int isEmpty(Tree *tree) {
    return (tree == NULL);
}

// FUNCTION BINARYSEARCH (RECURSIVE)
// SEARCHS FOR AN ITEM IN THE TREE AND RETURN THE NUMBER OF COMPARISONS NEEDED TO FIND THE GIVEN ITEM
int binarySearch(Tree *root, int item){
  int op = 0;
    Tree *temp;
    temp = root;
    while (temp != NULL) {
        op++;
        if (temp->item == item){
            return op;
        }
        if (temp->item > item)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return -1;
}

// FUNCTION INSERTNODETREE
// INSERTS A "NODE" IN THE TREE IN THE CORRECT POSITION
Tree *insertNodeTree(Tree *tree, int item) {
    if (tree == NULL) {
        return(createTree(item, NULL, NULL));
    }
    if (item < tree->item) {
        tree->left  = insertNodeTree(tree->left, item);
    } else {
        tree->right = insertNodeTree(tree->right, item);
    }
    return tree;
}

void preOrder(Tree *root) {
    if(root != NULL) {
        printf("|%d| ", root->item);
        preOrder(root->left);
        preOrder(root->right);
    }
}
