#include "objectCreation.h"
#include <stdlib.h>
#include "struct.h"
#include "definitions.h"

void create_pedina(BoardPointer board) {
    int i,j;
    for (i=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
            if ((i + j) % 2 == 0 && i!=3) {
                board[i][j].piece[0].team = i < 3 ? 1 : 2;
                board[i][j].piece[0].p = i < 3 ? 'r' : 'g';
                board[i][j].piece[0].rank = 1;
                board[i][j].height=1;
            }
        }
    }
}

BoardPointer initialize() {
    int i, j, h;
    BoardPointer mat = (struct Cella**)malloc(DIM * sizeof(struct Cella*));
    for(i=0; i<DIM; i++) {
        mat[i] = (struct Cella*) malloc(DIM * sizeof(struct Cella));
        for(j=0; j<DIM; j++) {
            mat[i][j].piece = (struct Pedina*) malloc(HEIGHT*sizeof(struct Pedina));
            for(h=0; h<HEIGHT; h++) {
                mat[i][j].piece[h].team = 0;
                mat[i][j].piece[h].p = '-';
                mat[i][j].piece[h].rank = 0;
                mat[i][j].height = 0;
            }
        }
    }
    create_pedina(mat);
    return mat;
}
