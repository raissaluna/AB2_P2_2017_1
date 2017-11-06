#include <limits.h>
#include "BinarySearchTree.h"
#include "List.h"
#include <time.h>
 
void shuffle(int *array, size_t n){

    // Randomiza os elementos de um vetor qualquer

    if (n > 1){

        size_t i;
        for (i = 0; i < n - 1; i++){

          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

unsigned int rand_interval(unsigned int min, unsigned int max){

    // Dado um intervalo, esta função retorna um número aleatório que está dentro desse intervalo.

    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */

    do{

        r = rand();
    }while(r >= limit);

    return min + (r / buckets);
}

void create_data (int array_size, node *List, Tree *BinarySearchTree){

    int numero_de_sorteios = 1000;
    int i;
    int number_to_search, y_lista, y_arvore;

    for (i = 0; i < numero_de_sorteios; i++){

        number_to_search = rand_interval(0, array_size-1);

        y_lista = search_list(List, number_to_search);
        y_arvore = binarySearch(BinarySearchTree, number_to_search);

        printf("%d %d %d\n", number_to_search, y_lista, y_arvore);
    } 
}

int main(){

    int i, option;
    Tree* BinarySearchTree = createEmptyTree();
    node* List = createEmptyList();

    node* List2 = createEmptyList();

    //printf("Count and plot data\nBinary Search Tree vs. List\n\n");

    srand(time(NULL));
    // int r = rand();
    
    int array_size = 10000;

    //printf("Array Size: \n");

    //scanf("%d", &array_size);

    int array[array_size];

    // Preenchendo o vetor de forma ordenada

    for (i = 0; i < array_size; i++){

        array[i] = i;
    }

    // Imprimindo o vetor em ordem

    // printf("\n");
    // for (i = 0; i < array_size; i++) {
    //     printf("%d ", array[i]);
    // }

    for(i = 0; i < array_size; i++){

        insertNode(&List2, array[i]); // Lista sequencial
    }

    // Randomizando o vetor

    shuffle(array, array_size);

    // Imprimindo o vetor randomizado

     // printf("\n");printf("\n");
     // for (i = 0; i < array_size; i++) {
     //     printf("%d ", array[i]);
     // }
     // printf("\n");printf("\n");

    // Colocando os dados nas estruturas

    for(i = 0; i < array_size; i++){

        insertNode(&List, array[i]); // Lista randômica que foi criada a partir do shuffle
        BinarySearchTree = insertNodeTree(BinarySearchTree, array[i]);
    }

    // Imprimindo as estruturas

    // printf("\nLista 2:\n");
    // printf("[");
    // print_list(List2);
    // printf("]");
    // printf("\nLista:\n");
    // printf("[");
    // print_list(List);
    // printf("]\n");
    // printf("\n");
    //printf("\nArvore:\n");
    //preOrder(BinarySearchTree);

    // Testando o sorteador

    // printf("\n\tTestando o sorteador:\n\n");
    // for (i=0; i < 25; i++) {
    //     printf("%d ", rand_interval(0,array_size));
    // }
    // printf("\n\n\tFim do teste do sorteador.\n");

    // Gerando os dados a partir dos sorteios.

    // Os numeros sorteados representam os valores a serem buscados nas estruturas e são colocados como entrada da função (eixo-x). A saída (eixo-y) é o numero de comparacoes realizadas para encontrar este valor. Para cada estrutura haverá uma saida. Ou seja, estaa função retorna três números: "x y_lista y_arvore"

    //create_data (array_size, List, BinarySearchTree); // lista randomica com abb randomica, sem ser balanceada

    create_data (array_size, List2, BinarySearchTree); // lista sequencial numa abb randômica, sem ser balanceada, criando dados da coluna1(varios numeros a serem sorteados), coluna2(números de comparações da lista) e coluna3(numero de comparações da árvore)

    // int number_to_search = rand_interval(0, array_size);

    // printf("\n\nNumber of comparisons to find %d in the List: %d\n",             number_to_search, search_list(List, number_to_search));
    // printf("\nNumber of comparisons to find %d in the Binary Search Tree: %d\n", number_to_search, binarySearch(BinarySearchTree, number_to_search));
    //printf("\n");

    return 0;
}