#include "2_compress.c"

/* Recebe o arquivo e uma Hash
 * função que conta a frequencia de caracter
 * e ja adiciona na hash utilizada
 */
void freq_count(void *file, HashT *ht);

/* Recebe a árvore e a quantidade atual de escapes. Na sua primeira chamada os scapes = 0
 * Retorna a quantidade de escapes adicionados; conta a quantidade de caracteres de escape
 */
int escape(Node *huff, int escapes);

/* Recebe o arquivo.huff e a arvore
 * trata os casos de * e barra invertida
 */
void print_tree_header(void *file, Node *huff);

/* Recebe o arquivo a ser compactado, o novo arquivo compactado e uma Hash
 * Retorna o tamanho do lixo
 * tem objetivo de escrever os bits no novo arquivo compactado
 */
int write_compressed_file(void *souce_file, void *compressed_file, HashT *ht);

/* Inicia a compressão do arquivo recebido
 */
void compress(void *file_name);
