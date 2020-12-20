#include "startGame.h"

BoardPointer initialize() {
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(7 * sizeof(struct Cella*));
    for(int i=0;i<7;i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(7*sizeof(struct Cella));
        for(int j=0;j<7;j++) {
            boardPointer->mat[i][j].pedina = (struct Pedina*) malloc(3*sizeof(struct Pedina));
            for(int pedina=0;pedina<3;pedina++) {
                boardPointer->mat[i][j].pedina[pedina].team = 0;
                boardPointer->mat[i][j].pedina[pedina].p = '-';
                boardPointer->mat[i][j].pedina[pedina].grado = 0;
                boardPointer->mat[i][j].height = 0;
            }
        }
    }
    return boardPointer;
}

void create_pedina(BoardPointer board){
    int dim=7;
    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            if ((i + j) % 2 == 0 && i!=3) {
                board->mat[i][j].pedina[0].team = i < 3 ? 1 : 2;
                board->mat[i][j].pedina[0].p = i < 3 ? 'r' : 'g';
                board->mat[i][j].pedina[0].grado = 1;
                board->mat[i][j].height=1;
            }
        }
    }
}
