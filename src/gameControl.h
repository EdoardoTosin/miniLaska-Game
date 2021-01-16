#include "struct.h"


/*!
   \brief Count the number of pieces inside a cell.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of pieces contained inside the cell (integer up to 3 included, 0 otherwise when there is no piece).
*/
int getHeight(BoardPointer board, int i, int j);
/*!
   \brief Find which team the topmost piece belongs to
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of the player the piece belongs to (0 if there is any piece inside the cell).
*/
int getTeam(BoardPointer board, int i, int j);
/*!
   \brief Find the rank the topmost piece has.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of rank of the piece (1 for a normal piece, 2 if it's a commander).
*/
int getRank(BoardPointer board, int i, int j);
/*!
   \brief Check if the cell is empty from any piece.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return 0 if empty, 1 otherwise.
*/
int isEmpty(BoardPointer board, int i, int j);
/*!
   \brief Find all possible moves of the current player.
   @param[in] board Struct where all pieces are located.
   @param[in] *mosse Struct to store the start and end coordinates for a given move.
   @param[in] turno Value containing the player of the current turn.
   \return Return the number of moves that have been found.
*/
int step(BoardPointer board, struct mossa *mosse, int turno);
/*!
   \brief Remove any piece from the given cell of the board.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void deleteCellContent(BoardPointer board, int i, int j);
/*!
   \brief Remove the topmost piece from the given cell of the board.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void updateCellContent(BoardPointer board, int i, int j);
/*!
   \brief Promote the topmost piece to rank 2.
   @param[in] board Struct where all pieces are located.
   @param[in] piece Piece that need to be promoted.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void promotion(BoardPointer board, PedinaPointer piece, int i, int j);
/*!
   \brief Execute the normal move.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse Struct containing the start and end coordinates to make the move.
*/
void normalStep(BoardPointer board, struct mossa mosse);
/*!
   \brief Execute the eat move.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse Struct containing the start and end coordinates to make the move.
*/
void eatStep(BoardPointer board, struct mossa mosse);
/*!
   \brief Check which move to do between a normal move and an eat move.
   @param[in] board Struct where all pieces are located.
   @param[in] m Struct containing the start and end coordinates of a given move.
*/
void executeStep(BoardPointer board, struct mossa m);
/**
  * Controlla quale mossa eseguire tra lo spostamento e la mangiata.
**/
void copyContent(BoardPointer board, struct Cella *cella, int row, int col);
/**
  * Copia il contenuto da una cella all'altra.
**/
void revert(BoardPointer board, struct Cella* iniziale, struct Cella* mezzo, struct Cella* finale, struct mossa mossa);
/**
  * Torna indietro di una mossa (per il PC).
**/
struct Cella* copyCella(struct Cella cella);
/**
  * Torna a una cella uguale a quella che voglio copiare.
**/
int minimax(BoardPointer board, int isMax, int depth, int somma);
/**
  * Algoritmo per trovare i punteggi delle mosse.
**/
int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize);
/**
  * Trova la mossa migliore in base al punteggio.
**/
