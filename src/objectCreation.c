#include "objectCreation.h"
#include <stdlib.h>
#include "struct.h"
#include "definitions.h"

void create_pedina(BoardPointer board) {
    int i,j;
    for (i=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
            if ((i + j) % 2 == 0 && i!=3) {
                board->mat[i][j].piece[0].team = i < 3 ? 1 : 2;
                board->mat[i][j].piece[0].p = i < 3 ? 'r' : 'g';
                board->mat[i][j].piece[0].rank = 1;
                board->mat[i][j].height=1;
            }
        }
    }
}

BoardPointer initialize() {
    int i, j, h;
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(DIM * sizeof(struct Cella*));
    for(i=0; i<DIM; i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(DIM * sizeof(struct Cella));
        for(j=0; j<DIM; j++) {
            boardPointer->mat[i][j].piece = (struct Pedina*) malloc(HEIGHT*sizeof(struct Pedina));
            for(h=0; h<HEIGHT; h++) {
                boardPointer->mat[i][j].piece[h].team = 0;
                boardPointer->mat[i][j].piece[h].p = '-';
                boardPointer->mat[i][j].piece[h].rank = 0;
                boardPointer->mat[i][j].height = 0;
            }
        }
    }
    create_pedina(boardPointer);
    return boardPointer;
}
