#include "struct.h"

int getHeight(BoardPointer board, int i, int j);

int getTeam(BoardPointer board,int i,int j);

int getRank(BoardPointer board,int i,int j);

int cella_vuota(BoardPointer board,int i, int j);

void promozione(BoardPointer board, struct Pedina *piece, int i, int j);

int avanzamento(BoardPointer board,struct mossa *mosse, int turno);

void aggiorna_cella(BoardPointer board, int i, int j);

void svuota_cella(BoardPointer board, int i, int j);

void spostamento_soldato(BoardPointer board, struct mossa mosse);

void spostamento_mangiata(BoardPointer board, struct mossa mosse);

void eseguiSpostamento(BoardPointer board,struct mossa m);

void copyContent(BoardPointer board, struct Cella *cella,int row,int col);

void revert(BoardPointer board, struct Cella* iniziale,struct Cella*mezzo, struct Cella*finale, struct mossa mossa);

struct Cella * copyCella(struct Cella cella);

int minimax(BoardPointer board, int isMax, int depth,int somma);

int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize);
