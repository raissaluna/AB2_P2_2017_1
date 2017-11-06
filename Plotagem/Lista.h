#include <stdio.h>
#include <stdlib.h>

#ifndef list_h
#define list_h

typedef struct Node{
	int item;
	struct Node *next;
}node;


node *createEmptyList();
node *new_node(int item);
void insertNode(node **l, int item);
void print_list(node *l);
int search_list(node *l, int item);
void free_node(node **l);
int size_list(node *l);
int empty_list(node *l);

#endif