#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Square{
	int height;
	int pos_1;
	int pos_2;
	int pos_3;
};

int square_status(){ /*Controllo casella*/
	return 0;
}

int eat(){ /*Conquista*/
	return 0;
}

int eat_check(){ /*Controllo obbligo di conquista*/
	return 0;
}

int win_check(){ /*Controllo condizioni vittoria dopo ogni mossa*/
	return 0;
}

void table_out(int* table){ /*Creazione output grafico nel terminale*/
	int i, j;
	for (i = 0; i < 7; i++){
		for (j = 0; j < 7; j++){
			if (i%2==0 && j%2==0)
				printf("%c")
			else if (i%2!=0 && j%2!=0)
				printf("%c", table())
		}
	}
	return;
}

int main(){
	int* table;
	const int dim = 7;
	int i;
	table = (int*) malloc (dim * dim * sizeof(int));
	for (i = 0; i < dim * dim, i++){
		
	}
	printf("Test output\n");
	table_out(table);
	return 0;
}
