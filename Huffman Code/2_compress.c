#include "5_hash_table.h"

void freq_count(void *file, HashT *ht){

	unsigned char *buffer;
	int i;
	
	fseek(file , 0 , SEEK_END); // Ajusta a posição do indicador com base em uma referência. SEEK_END (final do arquivo) é a referência e 0 é posição à partir da referência. Isso significa que o indicador vai permanecer na referência. O resultado dessa função é que o indicador está ajustado para indicar o final do arquivo.

	int file_size = ftell(file); // A função "ftell" retorna a posição do indicador. Nesse caso, ele retorna a posição ajustada pela "fseek", ou seja, o valor da posição do último caractere do arquivo. Essa posição é interpretada como o tamanho do arquivo em bytes (1 caractere = 1 byte).

	rewind(file); // Essa função ajusta o indicador para o começo do arquivo, como era antes da função "fseek".

	buffer = (unsigned char *) malloc(sizeof(char) *file_size); // Faz uma atribuição ao "buffer" reservando um espaço na memória igual ao tamanho do arquivo.

	fread(buffer, 1, file_size, file); // Copia os caracteres do arquivo para o "buffer".

	//ht = &(HashT*) ht;

	for(i = 0; i < file_size; i++){

		ht -> table[buffer[i]] -> freq++;

		// Percorre o buffer e atualiza (incrementa) a frequencia do caractere encontrado na hash table.
	}

	free(buffer);

} // Calcula a frequência de cada caractere e armazena as frequências na hash table.

int escape(Node *huff, int escapes){

	if(huff != NULL){

    	if((huff -> letter == 42 || huff -> letter == '\\') && is_leaf(huff)){
    		++escapes;
    	}
		escapes = escape(huff -> left, escapes);
		escapes = escape(huff -> right, escapes);
	}
  return escapes;
} // Conta a frequencia dos scapes para colocar no tamanho da arvore

void print_tree_header(void *file, Node *huff){

	if(huff != NULL){

    	if((huff -> letter == 42 || huff -> letter == '\\') && is_leaf(huff)){

    	  fprintf(file, "\\%c", huff -> letter);
    	}else{

    	  fprintf(file, "%c", huff -> letter);
    	}

		print_tree_header(file, huff -> left);
		print_tree_header(file, huff -> right);
	}
} // Trata o caso dos *

int write_compressed_file(void *source_file, void *compressed_file, HashT *ht){

	unsigned char byteread;
	unsigned char byte = 0;
	char *bitshuff = NULL;
	int bit_index = 7;
	int i;
	rewind(source_file);

	while(fscanf(source_file, "%c", &byteread) > 0){

		bitshuff = getCharBits(ht, byteread);//retorna o bit que representa esse caracter
		//printf("%s\n", bitshuff);
		for(i = 0 ; i < strlen(bitshuff); ++i){

			if(bit_index == -1){

				fprintf(compressed_file, "%c", byte);
				byte = 0;
				bit_index = 7;
			}
			if(bitshuff[i] == '1'){

				byte = set_bit(byte, bit_index);
			}
			bit_index--;
		}
	}
	if(bit_index <= 7){

		fprintf(compressed_file, "%c", byte);
	}
	bit_index++;

	return bit_index;
} // Retorna o tamanho do lixo


void compress(void *file_name){

	FILE  *source_file, *compressed_file;
	HashT *hasht = create_hash();
	Node  *queue = create_empty_queue();
	Node  *huffman_tree = create_empty_tree();
	int i;

	source_file = fopen(file_name, "rb");
	compressed_file = fopen("compressed_file.huff", "wb");

	if (source_file == NULL || compressed_file == NULL){

		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tCompressing ...\n");

	freq_count(source_file, hasht);

	//int c = 0;
	
	for(i = 0; i < 256; i++){
		//printf("\n%d\n", i);
		if(hasht -> table[i] -> freq > 0){
			queue = create_node(queue, i, hasht -> table[i] -> freq);
			
			//printf("\t%d\n", hasht -> table[i] -> freq);
			//printf("\tc: %d\n", c);
			//c++;
		}
	} // Inserindo na fila de prioridade todos os elementos que aparecem pelo menos uma vez na hasht.

	huffman_tree = huff_tree(queue); // Transformando fila em arvore

	// Imprimir a arvore em pre ordem.
	// print_tree(huffman_tree);

	fprintf(compressed_file, "00"); // Ocupando os dois primeiros bytes para guardar lugar p/ lixo e size_tree.

	unsigned char bit_string[255];
	build_representations(huffman_tree, bit_string, -1, '0', hasht);

	unsigned int tree_size = size_huff(huffman_tree) + escape(huffman_tree, 0); // Pegando o tamanho da arvore
	print_tree_header(compressed_file, huffman_tree);//tratando os *

	char *tree_header_tam = (char*)malloc(13*sizeof(char));
	int_bin(tree_header_tam, tree_size, 13); // Transformando o tamanho da arvore em binario

	// Printa o binario da arvore
	// printf("\nbin %s\n", tree_header_tam);
	// printf("tamanho arvore %d\n", tree_size);

	unsigned int lixo = write_compressed_file(source_file, compressed_file, hasht); // Pegando o tamanho do lixo

	char *qtdLixo = (char*)malloc(4*sizeof(char));
	int_bin(qtdLixo, lixo, 3);
	qtdLixo[3] = '\0'; // Transformando o tamanho da lixo em binario

	// Printa tamnhao do lixo, o binario do lixo
	// printf("\n%d lixo %s\n", lixo, qtdLixo);

	// Montando o cabeçario
	char header[17] = "";
	strcpy(header, qtdLixo);
	header[3] = '\0';
	strcat(header, tree_header_tam);
	header[16] = '\0';

	// Printa o cabeçario
	// printf("header-> %s\n", header);

	rewind(compressed_file);
	escreverBitsArquivo(compressed_file, header, 16); // Coloca o header no incio do arquivo

	fclose(source_file);
	fclose(compressed_file);

	printf("\n\tEnd of compression!\n\n");
}