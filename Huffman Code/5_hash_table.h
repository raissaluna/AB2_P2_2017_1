#include "5_hash_table.c"

// Cria uma nova hash
HashT *create_hash();

// Copia a string do bit para a hash
void addCharBits(HashT *ht, unsigned char c, char *bits);

// Retorna o bit que representa esse caracter
char *getCharBits(HashT *ht, unsigned char c);

/* Pecorre a arvore e cria string com o caminho de cada letra; adicionando sempre na hash
 * direita 1, esquerda 0;
 * tem o esquema de corta o ultimo bit quando chamar a recussão(não to me lembrando bem)
 */
void build_representations(Node *tree, unsigned char *bit_string, int index, unsigned char bit, HashT *ht);
