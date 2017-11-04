#include "4_huffman.h"

#define ASCII_CHARS 256

typedef struct element{

	unsigned char letter;
	int freq;
	char bitstring[ASCII_CHARS];
}Element;

typedef struct hash_table{

	Element *table[ASCII_CHARS];
}HashT;

// Cria a hash table
HashT *create_hash(){

	int i;
	HashT *ht = (HashT*) malloc(sizeof(HashT));
	
	for (i = 0; i < ASCII_CHARS; ++i){

		ht -> table[i] = (Element*) malloc(sizeof(Element));
		ht -> table[i] -> letter = i;
		ht -> table[i] -> freq = 0;
	}
	return ht;
}

// Copia a string do bit para a hash table
void addCharBits(HashT *ht, unsigned char c, char *bits){

	strcpy(ht -> table[(int)c] -> bitstring, bits);
}

// Retorna o bit que representa esse caractere
char *getCharBits(HashT *ht, unsigned char c){

	return ht -> table[(int)c] -> bitstring;
}

/* Pecorre a arvore e cria string com o caminho de cada letra; adicionando sempre na hash
 * direita 1, esquerda 0;
 * tem o esquema de corta o ultimo bit quando chamar a recussão(não to me lembrando bem)
 */
void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned char bit, HashT *ht){

	if(index > -1){ // Se estiver em -1 foi a primeira chamada da função, portanto tree ainda é a raiz da árvore
	
		bit_string[index] = bit; // Vai sempre salvando o bit passado na pos correta da string
		if(is_leaf(tree)){

			bit_string[index + 1] = '\0';
			strcpy(ht -> table[(int)tree->letter] -> bitstring, bit_string);
			// printf("%s\n", bit_string);
		}
	}
	// As chamadas recursivas vão para esquerda ou para direita, passando respectivamente 0 ou 1 como bits
	// e incrementando o index para avançar na string, quando for feito o backtrack o index volta para o anterior
	if(tree->left != NULL){
		
		build_representations(tree->left, bit_string, index + 1, '0', ht);
	}
	if(tree->right != NULL){

		build_representations(tree->right, bit_string, index + 1, '1', ht);
	}
	return;
}
