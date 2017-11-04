#include "6_util.h"
#include "2_compress.h"
#include "3_decompress.h"

int main(){

	int choice;
	char file_name[100];
	printf("\n Choose an option:\n\n\t1 - Compress a file.\n\t2 - Decompress a file.\n\n\t");
	scanf("%d", &choice);
	switch(choice){
		
		case 1:
			printf("\n\tEnter the source file path: ");
			scanf("%s", file_name);
			compress(file_name);
			break;
		case 2:
			printf("\n\tEnter the new file path: ");
			scanf("%s", file_name);
			decompress(file_name);
			break;
		default:
			printf("\n\tError!\n\n");
	}

	return 0;
}