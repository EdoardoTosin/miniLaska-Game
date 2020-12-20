#include "printBoard.h"

void print_board(BoardPointer board){
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            printf("|");
            for (int k = 0; k < 3; ++k) {
                printf("%c",board->mat[i][j].pedina[k].p);
                /*
                if (board->mat[i][j].pedina[1].p=='r'){
                    //setcolor(RED);
                }
                */
            }
        }
        printf("|\n");
    }
}
