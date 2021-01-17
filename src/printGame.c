#include "printGame.h"

#include <stdio.h>

#include <stdlib.h>

#include "definitions.h"

void printBoard(BoardPointer board) {
  char white = '$';
  int i, j, k, l;
  system(CLEAR);
  printf(" ");
  for (j = 0; j < DIM; j++)
    printf("   %d", j);
  printf("\n");
  for (i = 0; i < DIM; i++) {
    printf("  %c",206);
    for (l = 0; l < DIM; l++)
      printf("%c%c%c%c",205,205,205,206);
    printf("\n%c ", ROW + i);
    for (j = 0; j < DIM; j++) {
      if ((i + j) % 2 == 0) {
        printf("%c",186);
        for (k = 0; k < HEIGHT; k++)
          if (board[i][j].piece[k].p == '-')
            printf(" ");
          else
            printf("%c", board[i][j].piece[k].p);
      } else {
        printf("%c",186);
        for (k = 0; k < HEIGHT; k++)
          printf("%c", white);
      }
    }
    printf("%c\n",186);
  }
  printf("  %c",206);
  for (l = 0; l < DIM; l++)
    printf("%c%c%c%c",205,205,205,206);
  printf("\n");
}

void printMoves(MossaPointer mosse, int dim) {
  int i;
  for (i = 0; i < dim; i++)
    printf("Choice n.%d: %c %d -> %c %d\n", i + 1, ROW + mosse[i].startPos -> row, mosse[i].startPos -> col, ROW + mosse[i].endPos -> row, mosse[i].endPos -> col);
}
