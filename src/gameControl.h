#include "struct.h"

int getHeight(BoardPointer board, int i, int j);
/**
  * Data la matrice e date le coordinate, restituisce l'altezza della cella.
**/
int getTeam(BoardPointer board,int i,int j);
/**
  * Data la matrice e date le coordinate, restituisce il team della pedina comandante.
**/
int getRank(BoardPointer board,int i,int j);
/**
  * Data la matrice e date le coordinate, restituisce il grado della pedina in posizione più alta.
**/
int isEmpty(BoardPointer board,int i, int j);
/**
  * Data la matrice e le coordinate, controlla se la cella è vuota
**/
void promotion(BoardPointer board, PedinaPointer piece, int i, int j);
/**
  * Esegue la promozione della pedina data alla funzione.
**/
int step(BoardPointer board, struct mossa *mosse, int turno);
/**
  * Trova tutte le possibili per il giocatore del turno corrente.
**/
void updateCellContent(BoardPointer board, int i, int j);
/**
  * Rimuove la pedina più in alto (comandante) dalla cella data.
**/
void deleteCellContent(BoardPointer board, int i, int j);
/**
  * Svuota l'intera celle dalle pedine.
**/
void normalStep(BoardPointer board, struct mossa mosse);
/**
  * Esegue la normale mossa di spostamento.
**/
void eatStep(BoardPointer board, struct mossa mosse);
/**
  * Esegue la mossa di mangiata.
**/
void executeStep(BoardPointer board,struct mossa m);
/**
  * Controlla quale mossa eseguire tra lo spostamento e la mangiata.
**/
void copyContent(BoardPointer board, struct Cella *cella,int row,int col);
/**
  * Copia il contenuto da una cella all'altra.
**/
void revert(BoardPointer board, struct Cella* iniziale,struct Cella*mezzo, struct Cella*finale, struct mossa mossa);
/**
  * Torna indietro di una mossa (per il PC).
**/
struct Cella * copyCella(struct Cella cella);
/**
  * Torna a una cella uguale a quella che voglio copiare.
**/
int minimax(BoardPointer board, int isMax, int depth,int somma);
/**
  * Algoritmo per trovare i punteggi delle mosse.
**/
int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize);
/**
  * Trova la mossa migliore in base al punteggio.
**/
