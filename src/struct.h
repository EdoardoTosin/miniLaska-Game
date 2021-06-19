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

struct Move {
  PositionPtr startPos;
  PositionPtr endPos;
};
typedef struct Move * MovePtr;

#endif
