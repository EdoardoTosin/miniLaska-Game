#include "printGame.h"
#include <stdio.h>
#include "struct.h"
#include "definitions.h"

void print_board(BoardPointer board) {
    char white=1;
    int i, j, k, l;
    /*system(CLEAR);*/
    printf(" ");
    for (j=0; j<DIM; j++)
        printf("   %d", j);
    printf("\n");
    for (i=0; i<DIM; i++) {
        printf("  +");
        for (l=0; l<DIM; l++)
            printf("---+");
        printf("\n%c ", ROW+i);
        for (j=0; j<DIM; j++) {
            if ((i+j)%2==0) {
                printf("|");
                for (k=0; k<HEIGHT; k++)
                    if (board[i][j].piece[k].p == '-')
                        printf(" ");
                    else
                        printf("%c", board[i][j].piece[k].p);
            }
            else{
                printf("|");
                for (k=0; k<HEIGHT; k++)
                    printf("%c",white);
            }
        }
        printf("|\n");
    }
    printf("  +");
    for (l=0; l<DIM; l++)
        printf("---+");
    printf("\n");
}

void print_mosse(struct mossa *mosse, int dim) {
    int i;
    for (i=0; i<dim; i++)
        printf("Mossa n.%d %c %d - %c %d\n", i + 1, ROW+mosse[i].startPos.row, mosse[i].startPos.col, ROW+mosse[i].endPos.row, mosse[i].endPos.col);
}
