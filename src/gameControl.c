#include "gameControl.h"

#include <stdlib.h>

#include <limits.h>

#include <stdio.h>

#include "definitions.h"

int getHeight(BoardPtr board, int i, int j) {
  if (board[i][j].height == 0)
    return 0;
  else
    return board[i][j].height;
}

int getTeam(BoardPtr board, int i, int j) {
  if (board[i][j].height == 0)
    return 0;
  else
    return board[i][j].piece[getHeight(board, i, j) - 1].team;
}

int getRank(BoardPtr board, int i, int j) {
  return board[i][j].piece[getHeight(board, i, j) - 1].rank;
}

int isEmpty(BoardPtr board, int i, int j) {
  int k;
  for (k = 0; k < HEIGHT; k++)
    if (board[i][j].piece[k].team != 0)
      return 0;
  return 1;
}

int step(BoardPtr board, MovePtr moves, int turn) {
  int index = 0;
  int i, j, i1, j1;
  int onlyEat = 0; /*serve per vedere se è stata trovata almeno una mangiata*/
  int middlePointRow;
  int middlePointCol;
  int andCondition;
  int orCondition;
  int isNormalStep;
  int middlePointTeam;
  int eat;
  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) {
      if ((i + j) % 2 == 0 && getTeam(board, i, j) == turn)
        for (i1 = i - 2; i1 <= i + 2; i1++) {
          for (j1 = j - 2; j1 <= j + 2; j1++) {
            middlePointRow = (i + i1) / 2;
            middlePointCol = (j + j1) / 2;
            andCondition = (i1 + j1) % 2 == 0 && i1 != i && j1 != j;
            andCondition = andCondition && i1 < DIM && i1 >= 0;
            andCondition = andCondition && j1 < DIM && j1 >= 0;
            andCondition = andCondition && isEmpty(board, i1, j1);
            orCondition = (turn == 1) && i1 > i;
            orCondition = orCondition || (turn == 2 && i1 < i);
            orCondition = orCondition || getRank(board, i, j) == 2;
            andCondition = andCondition && orCondition;
            isNormalStep = abs(i1 - i) == 1;
            if (andCondition) {
              middlePointTeam = getTeam(board, middlePointRow, middlePointCol);
              eat = (middlePointTeam != 0 && middlePointTeam != turn && !isNormalStep);
              if ((!onlyEat && (isNormalStep || eat)) || (onlyEat && eat)) {
                if (!onlyEat && eat) {
                  index = 0;
                  onlyEat = eat;
                }
                moves[index].startPos -> row = i;
                moves[index].startPos -> col = j;
                moves[index].endPos -> row = i1;
                moves[index].endPos -> col = j1;
                index++;
              }
            }
          }
        }
    }
  }
  return index;
}

void deleteCellContent(BoardPtr board, int i, int j) {
  int k;
  int height = getHeight(board, i, j);
  for (k = 0; k < height; k++) {
    board[i][j].piece[k].team = 0;
    board[i][j].piece[k].p = '-';
    board[i][j].piece[k].rank = 0;
  }
  board[i][j].height = 0;
}

void updateCellContent(BoardPtr board, int i, int j) {
  int height = getHeight(board, i, j);
  board[i][j].piece[height - 1].team = 0;
  board[i][j].piece[height - 1].p = '-';
  board[i][j].piece[height - 1].rank = 0;
  board[i][j].height = height - 1;
}

void promotion(BoardPtr board, PiecePtr piece, int i, int j) {
  int height = getHeight(board, i, j);
  if (piece[height - 1].p == 'g' && i == 0) {
    piece[height - 1].p = 'G';
    piece[height - 1].rank = 2;
  }
  if (piece[height - 1].p == 'r' && i == 6) {
    piece[height - 1].p = 'R';
    piece[height - 1].rank = 2;
  }
}

void normalStep(BoardPtr board, struct mossa moves) {
  int i;
  int height = getHeight(board, moves.startPos -> row, moves.startPos -> col);
  for (i = 0; i < height; i++) {
    board[moves.endPos -> row][moves.endPos -> col].piece[i].team = board[moves.startPos -> row][moves.startPos -> col].piece[i].team;
    board[moves.endPos -> row][moves.endPos -> col].piece[i].p = board[moves.startPos -> row][moves.startPos -> col].piece[i].p;
    board[moves.endPos -> row][moves.endPos -> col].piece[i].rank = board[moves.startPos -> row][moves.startPos -> col].piece[i].rank;
  }
  board[moves.endPos -> row][moves.endPos -> col].height = height;
  deleteCellContent(board, moves.startPos -> row, moves.startPos -> col);
  promotion(board, board[moves.endPos -> row][moves.endPos -> col].piece, moves.endPos -> row, moves.endPos -> col);
}

void eatStep(BoardPtr board, struct mossa moves) {
  int k;
  int i = (moves.startPos -> row + moves.endPos -> row) / 2;
  int j = (moves.startPos -> col + moves.endPos -> col) / 2;
  int currentHeight = getHeight(board, moves.startPos -> row, moves.startPos -> col);
  int middlePieceHeight = getHeight(board, i, j);
  board[moves.endPos -> row][moves.endPos -> col].piece[0].team = board[i][j].piece[middlePieceHeight - 1].team;
  board[moves.endPos -> row][moves.endPos -> col].piece[0].p = board[i][j].piece[middlePieceHeight - 1].p;
  board[moves.endPos -> row][moves.endPos -> col].piece[0].rank = board[i][j].piece[middlePieceHeight - 1].rank;
  if (currentHeight == HEIGHT) {
    for (k = 1; k < currentHeight; k++) {
      board[moves.endPos -> row][moves.endPos -> col].piece[k].team = board[moves.startPos -> row][moves.startPos -> col].piece[k].team;
      board[moves.endPos -> row][moves.endPos -> col].piece[k].p = board[moves.startPos -> row][moves.startPos -> col].piece[k].p;
      board[moves.endPos -> row][moves.endPos -> col].piece[k].rank = board[moves.startPos -> row][moves.startPos -> col].piece[k].rank;
    }
    board[moves.endPos -> row][moves.endPos -> col].height = HEIGHT;
  } else {
    for (k = 0; k < currentHeight; k++) {
      board[moves.endPos -> row][moves.endPos -> col].piece[k + 1].team = board[moves.startPos -> row][moves.startPos -> col].piece[k].team;
      board[moves.endPos -> row][moves.endPos -> col].piece[k + 1].p = board[moves.startPos -> row][moves.startPos -> col].piece[k].p;
      board[moves.endPos -> row][moves.endPos -> col].piece[k + 1].rank = board[moves.startPos -> row][moves.startPos -> col].piece[k].rank;
    }
    board[moves.endPos -> row][moves.endPos -> col].height = currentHeight + 1;
  }
  deleteCellContent(board, moves.startPos -> row, moves.startPos -> col);
  updateCellContent(board, i, j);
  promotion(board, board[moves.endPos -> row][moves.endPos -> col].piece, moves.endPos -> row, moves.endPos -> col);
}

void executeStep(BoardPtr board, struct mossa m) {
  if (abs(m.endPos -> row - m.startPos -> row) == 1)
    normalStep(board, m);
  else
    eatStep(board, m);
}

void copyContent(BoardPtr board, struct Cell * cella, int row, int col) {
  int i;
  for (i = 0; i < HEIGHT; i++) {
    board[row][col].piece[i].team = cella -> piece[i].team;
    board[row][col].piece[i].p = cella -> piece[i].p;
    board[row][col].piece[i].rank = cella -> piece[i].rank;
    board[row][col].height = cella -> height;
  }
}

void revert(BoardPtr board, struct Cell * begin, struct Cell * middle, struct Cell * end, struct mossa mossa) {
  int i, j;
  copyContent(board, begin, mossa.startPos -> row, mossa.startPos -> col);
  copyContent(board, end, mossa.endPos -> row, mossa.endPos -> col);
  if (middle != NULL) {
    i = (mossa.startPos -> row + mossa.endPos -> row) / 2;
    j = (mossa.startPos -> col + mossa.endPos -> col) / 2;
    copyContent(board, middle, i, j);
  }
}

struct Cell * copyCella(struct Cell cella) {
  int i;
  struct Cell * c = (struct Cell * ) malloc(sizeof(struct Cell));
    if(c==NULL) {
        printf("Error! memory not allocated.");
        exit(EXIT_FAILURE);
    }
  c -> piece = (PiecePtr) malloc(HEIGHT * sizeof(struct Pedina));
    if(c -> piece==NULL) {
        printf("Error! memory not allocated.");
        exit(EXIT_FAILURE);
    }
  for (i = 0; i < HEIGHT; i++) {
    c -> piece[i].team = cella.piece[i].team;
    c -> piece[i].p = cella.piece[i].p;
    c -> piece[i].rank = cella.piece[i].rank;
    c -> height = cella.height;
  }
  return c;
}

int minimax(BoardPtr board, int isMax, int depth, int sum, int mode) {
  int i, best;
  int index;
  int eat;
  struct Cell * begin;
  struct Cell * end;
  int iMiddle;
  int jMiddle;
  int j;
  struct Cell * middle;
  MovePtr moves = (MovePtr) malloc(sizeof(struct mossa) * 15);
    if(moves==NULL) {
        printf("Error! memory not allocated.");
        exit(EXIT_FAILURE);
    }
  for (j = 0; j < 15; ++j) {
    moves[j].startPos = (PositionPtr) malloc(sizeof(PositionPtr));
      if(moves[j].startPos==NULL) {
          printf("Error! memory not allocated.");
          exit(EXIT_FAILURE);
      }
    moves[j].endPos = (PositionPtr) malloc(sizeof(PositionPtr));
      if(moves[j].endPos==NULL) {
          printf("Error! memory not allocated.");
          exit(EXIT_FAILURE);
      }
  }
  index = step(board, moves, isMax ? 1 : 2);

  if (index == 0 && !isMax)
    return INT_MAX;

  if (index == 0 && isMax)
    return INT_MIN;

  if (depth == mode)
    return sum;

  eat = abs(moves -> endPos -> row - moves -> startPos -> row) != 1;

  if (isMax) {
    best = INT_MIN;
    for (i = 0; i < index; i++) {
      begin = copyCella(board[moves[i].startPos -> row][moves[i].startPos -> col]);
      end = copyCella(board[moves[i].endPos -> row][moves[i].endPos -> col]);
      iMiddle = (moves[i].startPos -> row + moves[i].endPos -> row) / 2;
      jMiddle = (moves[i].startPos -> col + moves[i].endPos -> col) / 2;
      middle = eat ? copyCella(board[iMiddle][jMiddle]) : NULL;
      executeStep(board, moves[i]);
      best = MAX(best, minimax(board, !isMax, depth + 1, sum + (eat ? 1 : 0), mode));
      revert(board, begin, middle, end, moves[i]);
      free(begin);
      free(end);
      if (middle != NULL) {
        free(middle);
      }
    }
    for (j = 0; j < 15; ++j) {
      free(moves[j].startPos);
      free(moves[j].endPos);
    }
    free(moves);
    return best;
  } else {
    best = INT_MAX;
    for (i = 0; i < index; i++) {
      begin = copyCella(board[moves[i].startPos -> row][moves[i].startPos -> col]);
      end = copyCella(board[moves[i].endPos -> row][moves[i].endPos -> col]);
      iMiddle = (moves[i].startPos -> row + moves[i].endPos -> row) / 2;
      jMiddle = (moves[i].startPos -> col + moves[i].endPos -> col) / 2;
      middle = eat ? copyCella(board[iMiddle][jMiddle]) : NULL;
      executeStep(board, moves[i]);
      best = MIN(best, minimax(board, !isMax, depth + 1, sum + (eat ? -1 : 0), mode));
      revert(board, begin, middle, end, moves[i]);
      free(begin);
      free(end);
      if (middle != NULL) {
        free(middle);
      }
    }
    for (j = 0; j < 15; ++j) {
      free(moves[j].startPos);
      free(moves[j].endPos);
    }
    free(moves);
    return best;
  }
}

int findBestMove(BoardPtr board, MovePtr moves, int movesSize, int mode) {
  int i;
  int moveVal = 0;
  int bestVal = INT_MIN;
  int bestMove = 0;
  int eat;
  struct Cell * begin;
  struct Cell * end;
  int iMiddle;
  int jMiddle;
  struct Cell * middle;
  for (i = 0; i < movesSize; i++) {
    eat = abs(moves -> endPos -> row - moves -> startPos -> row) != 1;
    begin = copyCella(board[moves[i].startPos -> row][moves[i].startPos -> col]);
    end = copyCella(board[moves[i].endPos -> row][moves[i].endPos -> col]);
    iMiddle = (moves[i].startPos -> row + moves[i].endPos -> row) / 2;
    jMiddle = (moves[i].startPos -> col + moves[i].endPos -> col) / 2;
    middle = eat ? copyCella(board[iMiddle][jMiddle]) : NULL;
    executeStep(board, moves[i]);
    if (movesSize == 1) {
      moveVal = eat ? 1 : 0;
    } else {
      moveVal = minimax(board, 0, 0, eat ? 1 : 0, mode);
    }
    if (moveVal > bestVal) {
      bestMove = i;
      bestVal = moveVal;
    }

    revert(board, begin, middle, end, moves[i]);
    free(begin);
    free(end);
    if (middle != NULL) {
      free(middle);
    }
  }
  printf("The value of the best move is : %d\n\n", bestVal);

  return bestMove;
}
