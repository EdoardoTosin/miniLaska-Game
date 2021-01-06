#include "struct.h"

int getHeight(BoardPointer board, int i, int j);

int getTeam(BoardPointer board,int i,int j);

int getRank(BoardPointer board,int i,int j);

int isEmpty(BoardPointer board,int i, int j);

void promotion(BoardPointer board, struct Pedina *piece, int i, int j);

int step(BoardPointer board,struct mossa *mosse, int turno);

void updateCellContent(BoardPointer board, int i, int j);

void deleteCellContent(BoardPointer board, int i, int j);

void normalStep(BoardPointer board, struct mossa mosse);

void eatStep(BoardPointer board, struct mossa mosse);

void executeStep(BoardPointer board,struct mossa m);

void copyContent(BoardPointer board, struct Cella *cella,int row,int col);

void revert(BoardPointer board, struct Cella* iniziale,struct Cella*mezzo, struct Cella*finale, struct mossa mossa);

struct Cella * copyCella(struct Cella cella);

int minimax(BoardPointer board, int isMax, int depth,int somma);

int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize);
