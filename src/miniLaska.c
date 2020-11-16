#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "startGame.h"
#include "endGames.h"
#include "controlGame.h"
#include "structSquare.h"
#include "printBoard.h"

int main(){
	struct square* board;
	createTable(board);
	printf("Test output\n");
	return 0;
}
