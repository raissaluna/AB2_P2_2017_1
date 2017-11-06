Node *new_node(char value, Node* left, Node* right){

	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node->letter = value;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

Node *build_tree(char *str_tree, int *pos){

	if(str_tree[*pos] == '*'){

		*pos = *pos + 1;
		Node *left = build_tree(str_tree, pos);
		*pos = *pos + 1;
		return new_node('*', left, build_tree(str_tree, pos));
	}else if(str_tree[*pos] == '\\'){

		*pos = *pos + 1;
		return new_node(str_tree[*pos], NULL, NULL);
	}
	return new_node(str_tree[*pos], NULL, NULL);
}


void decompress(char *new_file_path){

	int i, j, pos;
	FILE *compressed_file, *new_file;
	int total_bytes, size_trash, size_tree;
	unsigned char *buffer;
	char header[17];

	compressed_file = fopen("compressed_file.huff", "rb");
	new_file = fopen(new_file_path, "wb");

	if (compressed_file == NULL || new_file == NULL){

		printf("\n\tWrong file path.\n");
		return;
	}

	printf("\n\tDecompressing ...\n");

	fseek(compressed_file , 0 , SEEK_END);
	total_bytes = ftell(compressed_file);
	rewind(compressed_file);
	buffer = (unsigned char*) malloc(sizeof(char)*total_bytes);
	fread(buffer, 1, total_bytes, compressed_file);

	for (i = 0; i < 17; ++i){

		header[i] = '\0';
	} // Setando tudo pra NULL para não ter problema de lixo

	for(i = 0; i < 2; i++){
	// 2 por ser os dois primeiros bytes
		for(j = 7; j >= 0; j--){
		// 7 por ser o tamanho do byte
			if(is_bit_i_set(buffer[i], j) == 0){
				header[strlen(header)] = '0'; // O tamanho da string sempre aumenta
			}else{
				header[strlen(header)] = '1';
			}
		}
	}
	
	size_trash = bin_int(header, 3);
	size_tree = bin_int(header+3, 13);

	char str_tree[size_tree + 1]; // Armazena a arvore, o +1 é para guardar o /0

	// i = 2 pois os 2 primeiros bytes já foram lidos
	// Agora lendo a árvore
	for(i = 2, pos = 0; i < size_tree + 2; i++, pos++){

		fseek(compressed_file, i, SEEK_SET);
		str_tree[pos] = getc(compressed_file);
	}
	str_tree[pos] = '\0'; // Para finalizar a string
	pos = 0;

	Node *root_huff = build_tree(str_tree, &pos);

	Node *aux_tree = root_huff; // arvore reconstruida

	// O tamanho da arvore + 2; ele agora vai comecar a ler o texto codificado
	fseek(compressed_file, size_tree + 2, SEEK_SET);
	// Comecando a ir de bit em bit buscando uma folha na arvore
	// Ate (o total de bytes) - (o que eu ja li)) - (o byte de lixo)
	unsigned int bit_cur = 0; //bit atual
	for(i = 0; i < (total_bytes - (size_tree + 2)) - 1; i++){

		bit_cur = getc(compressed_file);
		for(j = 7; j >= 0; j--){

			if(is_bit_i_set(bit_cur, j)){
				aux_tree = aux_tree->right;
			}else{
				aux_tree = aux_tree->left;
			}
			if(is_leaf(aux_tree)){

				fprintf(new_file, "%c", aux_tree->letter);
				aux_tree = root_huff;
			}
		}
	}

	// Ultimo byte (trabalhado com o lixo)
	bit_cur = getc(compressed_file);
	for(j = 7; j >= size_trash; j--){

		if(is_bit_i_set(bit_cur, j)){
			aux_tree = aux_tree->right;
		}else{
			aux_tree = aux_tree->left;
		}
		if(is_leaf(aux_tree)){

			fprintf(new_file, "%c", aux_tree->letter);
			aux_tree = root_huff;
		}
	}
	
	fclose(compressed_file);
	fclose(new_file);

	printf("\n\tSuccess!\n\n");
}