#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "startGame.h"
#include "endGames.h"
#include "controlGame.h"
#include "structSquare.h"
#include "printBoard.h"

int main(){
	square* table;
	createTable(table);
	printf("Test output\n");
	/*table_out(table);*/
	return 0;
}
