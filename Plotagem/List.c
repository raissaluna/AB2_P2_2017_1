#include "List.h"

node *createEmptyList(){

	return NULL;
}

node *new_node(int item){

	node *novo = (node*) malloc(sizeof(node));
	novo->item = item;
	novo->next = NULL;
	return novo;
}

void insertNode(node **l, int item){
	if(*l == NULL){

		*l = new_node(item);
	}
	else{

		insertNode(&(*l)->next, item);

	}
}

void print_list(node *l){

 	if(l != NULL){

 		printf("%d ", l->item);
 		print_list(l->next);
 	}
}

int search_list(node *l, int item){
	int comparisons = 0;
	while(l!=NULL){

	 	if (l -> item == item) return comparisons+1;
	 	comparisons++;
	 	l = l -> next;
	}
return comparisons;
}

void free_node(node **l){

	if (*l != NULL){

		free_node(&(*l)->next);
		free(*l);
		*l = NULL;
	}
}

int size_list(node *l){

	if(l == NULL){

		return 0;
	}
	return 1 + size_list(l -> next);
}

int empty_list(node *l){

   return (l == NULL);
}