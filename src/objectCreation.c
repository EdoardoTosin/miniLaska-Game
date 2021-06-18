#include "objectCreation.h"

#include <stdlib.h>

#include "definitions.h"

#include <stdio.h>

void createPiece(BoardPtr board) {
  int i, j;
  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) {
      if ((i + j) % 2 == 0 && i != 3) {
        board[i][j].piece[0].team = i < 3 ? 1 : 2;
        board[i][j].piece[0].p = i < 3 ? 'r' : 'g';
        board[i][j].piece[0].rank = 1;
        board[i][j].height = 1;
      }
    }
  }
}

BoardPtr initialize() {
  int i, j, h;
  BoardPtr mat = (BoardPtr) malloc(DIM * sizeof(struct Cell * ));
    if(mat==NULL) {
        printf("Error! memory not allocated.");
        exit(EXIT_FAILURE);
    }
  for (i = 0; i < DIM; i++) {
    mat[i] = (struct Cell * ) malloc(DIM * sizeof(struct Cell));
      if(mat[i]==NULL) {
          printf("Error! memory not allocated.");
          exit(EXIT_FAILURE);
      }
    for (j = 0; j < DIM; j++) {
      mat[i][j].piece = (PiecePtr) malloc(HEIGHT * sizeof(struct Pedina));
        if(mat[i][j].piece==NULL) {
            printf("Error! memory not allocated.");
            exit(EXIT_FAILURE);
        }
      for (h = 0; h < HEIGHT; h++) {
        mat[i][j].piece[h].team = 0;
        mat[i][j].piece[h].p = '-';
        mat[i][j].piece[h].rank = 0;
        mat[i][j].height = 0;
      }
    }
  }
  createPiece(mat);
  return mat;
}
