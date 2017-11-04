typedef struct node{

	unsigned char letter; // Caractere
	int freq; 			  // Frequencia do caractere
	struct node *next;    // Proxima da fila
	struct node *left;    // Filho esquuerdo
	struct node *right;   // Filho direito
}Node;

Node *create_empty_queue(){

    return NULL;
}

Node *create_empty_tree(){

	return NULL;
}

int is_empty(Node *node){

	return (node == NULL);
}

Node *insert_node(Node *queue, Node *new_node){
	
	// Um normal enqueue de priority queue

	if(queue == new_node){

		// *** Usado no merge_node. ***

		new_node -> next = NULL;

		//printf("\nqueue == new_node\n");

		return new_node;

	}else if(is_empty(queue) || new_node->freq <= queue->freq){

		// Insere o primeiro. || Insere antes do primeiro quando a frequência do nó é menor ou igual que o primeiro.

		new_node -> next = queue;

		//printf("\nis_empty || new_node->freq <= queue->freq\n");

		return new_node;

	}else{

		// Insere antes do maior em relação ao nó ou no final se ele for o maior de todos.
		// *** Usado no merge_node. ***

		Node *aux = queue;

		while(aux->next != NULL && new_node->freq > aux->next->freq){
			
			aux = aux->next;

		}

		new_node->next = aux->next;
		aux->next = new_node;

		//printf("\nelse\n");

		return queue;
	}
}

Node *create_node(Node *queue, unsigned char letra, int frequency){
	
	// Crio o nó (com a letra e a frequencia) e já insiro em uma lista
	
	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node -> letter = letra;
	new_node -> freq = frequency;
	new_node -> next = NULL;
	new_node -> left = NULL;
	new_node -> right = NULL;
	
	queue = insert_node(queue, new_node);

	return queue;
}

Node *merge_node(Node *queue){
	
	// Remove e junta os dois nós com menores frequências, criando um novo nó como seus pais onde a frequência desse pai será igual a soma da frequência dos dois filhos.

	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node -> left = queue;
	new_node -> right = queue -> next;
	
	if(new_node->right->next != NULL){
		
		queue = new_node->right->next;

	}else{
	
		queue = new_node;

	}
	
	new_node -> left -> next = NULL;
	new_node -> right -> next = NULL;
	new_node -> letter = '*';
	new_node -> freq = (new_node->left->freq) + (new_node->right->freq);
	
	queue = insert_node(queue, new_node);

	// Insere o novo nó na fila, ordenando-o.

	return queue;
}

Node *huff_tree(Node *queue){

	// Função que chama merge na fila toda até se tornar uma arvore
	// Caso a fila só tenha 1 nó, o merge não é necessário, só é preciso criar um novo nó que vai ter a mesma frequência do anterior.

	if(queue->next == NULL){

		Node *new_node = (Node*) malloc(sizeof(Node));
		new_node -> left = queue;
		new_node -> right = NULL;
		new_node -> letter = '*';
		new_node -> freq = queue -> freq;
		queue = new_node;

	}else{
		
		while(queue->next != NULL){
			
			queue = merge_node(queue);

		}
	}
	return queue;
}

void print_tree(Node *tree){

	if(tree != NULL){

		printf("%c", tree -> letter);
		print_tree(tree -> left);
		print_tree(tree -> right);

	}
}

// Tamanho da arvore huffman
int size_huff(Node *huff){

	if(huff == NULL){

		return 0;

	}else{
		
		return 1 + size_huff(huff->left) + size_huff(huff->right);

	}
}

int is_leaf(Node *huff){
	
	return (huff -> left == NULL && huff -> right == NULL);

}