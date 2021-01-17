#include "startGame.h"

#include <stdio.h>

#include <stdlib.h>

#include "struct.h"

#include "definitions.h"

#include "printGame.h"

#include "gameControl.h"

#include "objectCreation.h"

#include "startMenu.h"

void match(int mode) {
  int choice, index;
  int end = 0, turno = 1, i = 0, j = 0, k;
  char player = 'R';
  int mossa;
  MossaPointer mosse;
  BoardPointer board = initialize();
  printBoard(board);
  while (!end) {
    printf("\n");
    mosse = (MossaPointer) malloc(sizeof(struct mossa) * 15);
      if(mosse==NULL) {
          printf("Error! memory not allocated.");
          exit(EXIT_FAILURE);
      }
    for (k = 0; k < 15; ++k) {
      mosse[k].startPos = (PosizionePointer) malloc(sizeof(struct Posizione));
        if(mosse[k].startPos==NULL) {
            printf("Error! memory not allocated.");
            exit(EXIT_FAILURE);
        }
      mosse[k].endPos = (PosizionePointer) malloc(sizeof(struct Posizione));
        if(mosse[k].endPos==NULL) {
            printf("Error! memory not allocated.");
            exit(EXIT_FAILURE);
        }
    }
    index = step(board, mosse, turno);
    if (index == 0) {
      end = 1;
      if (turno == 1)
          printf("Player G wins the game with %d moves!!!\n\n", j);
      else {
        if (mode == 1)
          printf("Player R wins the game with %d moves!!!\n\n", i);
        else
          printf("Computer wins the game with %d moves!!!\n\n", i);
      }
      delayTimer(4);
    } else {
      if (turno == 1) {
        printf("TURN PLAYER %c\n", player);
        printMoves(mosse, index);
        if (mode == 0) {
          do {
              printf("\nInsert number: ");
            scanf("%d", & choice);
          } while (choice < 1 || choice > index);
          executeStep(board, mosse[choice - 1]);
          printBoard(board);
          printf("Player %c made the move number %d\n", player, choice);
        } else {
          mossa = findBestMove(board, mosse, index, mode);
          printf("Move%d\n", mossa + 1);
          executeStep(board, mosse[mossa]);
          printBoard(board);
          printf("Computer made the move number %d: %c %d -> %c %d\n", mossa + 1, ROW + mosse[mossa].startPos -> row, mosse[mossa].startPos -> col, ROW + mosse[mossa].endPos -> row, mosse[mossa].endPos -> col);
        }

        turno = 2;
        player = 'G';
        i++;
      } else {
        printf("TURN PLAYER %c\n", player);
        printMoves(mosse, index);
        do {
            printf("\nInsert number: ");
          scanf("%d", & choice);
        } while (choice < 1 || choice > index);
        executeStep(board, mosse[choice - 1]);
        printBoard(board);
        printf("Player %c made the move number %d\n", player, choice);
        turno = 1;
        player = 'R';
        j++;
      }
    }
    for (k = 0; k < 15; ++k) {
      free(mosse[k].startPos);
      free(mosse[k].endPos);
    }
    free(mosse);
  }
  free(board);
}
