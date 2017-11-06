#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{

    int item;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

Tree *createEmptyTree(){

    return NULL;
}

// Cria uma árvore não nula com seus items e ponteiros
Tree *createTree(int item, Tree *left, Tree *right){

    Tree *tree = (Tree*) malloc(sizeof(Tree));
    tree->item = item;
    tree->left = left;
    tree->right = right;
}

int isEmpty(Tree *tree){

    return (tree == NULL);
}

// Retorna o número de comparações necessárias para achar o item dado
int binarySearch(Tree *root, int item){

  int op = 0;
    Tree *temp;
    temp = root;
    while (temp != NULL){

        op++;
        if (temp->item == item){
            return op;
        }
        if (temp->item > item){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    return op;
}

// insere um nó na árvore, ordenando-o
Tree *insertNodeTree(Tree *tree, int item){

    if (tree == NULL){

        return(createTree(item, NULL, NULL));
    }
    if (item < tree->item){

        tree->left  = insertNodeTree(tree->left, item);
    }else{

        tree->right = insertNodeTree(tree->right, item);
    }
    return tree;
}

void preOrder(Tree *root){

    if(root != NULL){

        printf("%d ", root->item);
        preOrder(root->left);
        preOrder(root->right);
    }
}
