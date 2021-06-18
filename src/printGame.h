#include "struct.h"

/*!
   \brief Print board and the pieces contained in the cells.
   @param[in] board Struct where all pieces are located.
*/
void printBoard(BoardPtr board);
/*!
   \brief Print a list of the possible moves the player of that turn can do.
   @param[in] moves
   @param[in] dim
*/
void printMoves(MovePtr moves, int dim);
