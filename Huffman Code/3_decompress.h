#include "3_decompress.c"

// Cria um novo nó para a nova arvore
Node *new_node(char value, Node *left, Node *right);

// Reconstroi a arvore ja tratando os caso de scape
Node *build_tree(char *str_tree, int *pos);

// Inicia a descompactação do arquivo, tendo como recebimento o nome de saida desse arquivo
void decompress(char *nomeSaida);
