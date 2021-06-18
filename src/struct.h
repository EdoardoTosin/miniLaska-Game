#ifndef STRUCT_H
#define STRUCT_H

struct Pedina {
  int team;
  char p;
  int rank;
};
typedef struct Pedina * PiecePtr;

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

struct mossa {
  PositionPtr startPos;
  PositionPtr endPos;
};
typedef struct mossa * MovePtr;

#endif
