#ifndef STRUCT_H
#define STRUCT_H

struct Piece {
  int team;
  char p;
  int rank;
};
typedef struct Piece * PiecePtr;

struct Cell {
  int height;
  PiecePtr piece;
};
typedef struct Cell ** BoardPtr;

struct Position {
  int row;
  int col;
};
typedef struct Position * PositionPtr;

struct move {
  PositionPtr startPos;
  PositionPtr endPos;
};
typedef struct move * MovePtr;

#endif
