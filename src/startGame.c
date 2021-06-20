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
  int indexBestMove;
  MovePtr moves;
  BoardPtr board = initialize();
  printBoard(board);
  while (!end) {
    printf("\n");
    moves = (MovePtr) malloc(sizeof(struct Move) * 15);
      if(moves==NULL) {
          printf("Error! memory not allocated.");
          exit(EXIT_FAILURE);
      }
    for (k = 0; k < 15; ++k) {
      moves[k].startPos = (PositionPtr) malloc(sizeof(PositionPtr));
        if(moves[k].startPos==NULL) {
            printf("Error! memory not allocated.");
            exit(EXIT_FAILURE);
        }
      moves[k].endPos = (PositionPtr) malloc(sizeof(PositionPtr));
        if(moves[k].endPos==NULL) {
            printf("Error! memory not allocated.");
            exit(EXIT_FAILURE);
        }
    }
    index = step(board, moves, turno);
    if (index == 0) {
      end = 1;
      if (turno == 1)
          printf("Player G wins the game with %d moves!!!\n\n", j);
      else {
        if (mode == 0)
          printf("Player R wins the game with %d moves!!!\n\n", i);
        else
          printf("Computer wins the game with %d moves!!!\n\n", i);
      }
      delayTimer(4);
    } else {
      if (turno == 1) {
        printf("TURN PLAYER %c\n", player);
        printMoves(moves, index);
        if (mode == 0) {
          do {
              printf("\nInsert number: ");
            scanf("%d", & choice);
          } while (choice < 1 || choice > index);
          executeStep(board, moves[choice - 1]);
          printBoard(board);
          printf("Player %c made the move number %d\n", player, choice);
        } else {
          indexBestMove = findBestMove(board, moves, index, mode);
          printf("Move%d\n", indexBestMove + 1);
          executeStep(board, moves[indexBestMove]);
          printBoard(board);
          printf("Computer made the move number %d: %c %d -> %c %d\n", indexBestMove + 1, ROW + moves[indexBestMove].startPos -> row, moves[indexBestMove].startPos -> col, ROW + moves[indexBestMove].endPos -> row, moves[indexBestMove].endPos -> col);
        }

        turno = 2;
        player = 'G';
        i++;
      } else {
        printf("TURN PLAYER %c\n", player);
        printMoves(moves, index);
        do {
            printf("\nInsert number: ");
          scanf("%d", & choice);
        } while (choice < 1 || choice > index);
        executeStep(board, moves[choice - 1]);
        printBoard(board);
        printf("Player %c made the move number %d\n", player, choice);
        turno = 1;
        player = 'R';
        j++;
      }
    }
    for (k = 0; k < 15; ++k) {
      free(moves[k].startPos);
      free(moves[k].endPos);
    }
    free(moves);
  }
  free(board);
}
