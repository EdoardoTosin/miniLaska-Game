#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "start.h"
#include "squareActions.h"
#include "checkFunctions.h"
#include "struct.h"
#include "output.h"

int main(){
	square* table;
	const int dim = 7;
	int i, j;
	table = (square*) malloc (dim * dim * sizeof(square));
	for (i = 0; i < dim, i++){
		for (j = 0; j < dim, j++){
			if ((i%2==0 && j%2==0) || (i%2!=0 && j%2!=0)){
				if (i < 3)
					table(i * dim + j) = 1;
				else if (i == 3)
					table(i * dim + j) = NULL;
				else if (i > 3)
					table(i * dim + j) = 2;
			}
		}
	}
	printf("Test output\n");
	table_out(table);
	return 0;
}
