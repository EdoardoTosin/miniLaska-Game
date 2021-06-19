#include "struct.h"


/*!
   \brief Count the number of pieces inside a cell.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of pieces contained inside the cell (integer up to 3 included, 0 otherwise when there is no piece).
*/
int getHeight(BoardPtr board, int i, int j);
/*!
   \brief Find which team the topmost piece belongs to
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of the player the piece belongs to (0 if there is any piece inside the cell).
*/
int getTeam(BoardPtr board, int i, int j);
/*!
   \brief Find the rank the topmost piece has.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return the number of rank of the piece (1 for a normal piece, 2 if it's a commander).
*/
int getRank(BoardPtr board, int i, int j);
/*!
   \brief Check if the cell is empty from any piece.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
   \return Return 0 if empty, 1 otherwise.
*/
int isEmpty(BoardPtr board, int i, int j);
/*!
   \brief Find all possible moves of the current player.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse Struct to store the start and end coordinates for a given move.
   @param[in] turn Value containing the player of the current turn.
   \return Return the number of moves that have been found.
*/
int step(BoardPtr board, struct move* mosse, int turn);
/*!
   \brief Remove any piece from the given cell of the board.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void deleteCellContent(BoardPtr board, int i, int j);
/*!
   \brief Remove the topmost piece from the given cell of the board.
   @param[in] board Struct where all pieces are located.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void updateCellContent(BoardPtr board, int i, int j);
/*!
   \brief Promote the topmost piece to rank 2.
   @param[in] board Struct where all pieces are located.
   @param[in] piece Piece that need to be promoted.
   @param[in] i Coordinate of the board row.
   @param[in] j Coordinate of the board column.
*/
void promotion(BoardPtr board, PiecePtr piece, int i, int j);
/*!
   \brief Execute the normal move.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse Struct containing the start and end coordinates to make the move.
*/
void normalStep(BoardPtr board, struct move mosse);
/*!
   \brief Execute the eat move.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse Struct containing the start and end coordinates to make the move.
*/
void eatStep(BoardPtr board, struct move mosse);
/*!
   \brief Check which move to do between a normal move and an eat move.
   @param[in] board Struct where all pieces are located.
   @param[in] m Struct containing the start and end coordinates of a given move.
*/
void executeStep(BoardPtr board, struct move m);
/*!
   \brief Copy the content from cella to board.
   @param[in] board Struct where all pieces are located.
   @param[in] cella Struct where will be copied the cell from.
   @param[in] row Coordinate of the board where to find the cell that need to be copied.
   @param[in] col Coordinate of the board where to find the cell that need to be copied.
*/
void copyContent(BoardPtr board, struct Cell* cella, int row, int col);
/*!
   \brief Revert a single move (for PC).
   @param[in] board Struct where all pieces are located.
   @param[in] begin
   @param[in] middle
   @param[in] end
   @param[in] mossa
*/
void revert(BoardPtr board, struct Cell* begin, struct Cell* middle, struct Cell* end, struct move mossa);
/*!
   \brief Copy a cell from board
   @param[in] cella
   @param[out] c Copy of the cell
*/
struct Cell* copyCella(struct Cell cella);
/*!
   \brief Algorithm for finding move scores
   @param[in] board Struct where all pieces are located.
   @param[in] isMax
   @param[in] depth
   @param[in] sum
   @param[in] mode
   @param[out] best
*/
int minimax(BoardPtr board, int isMax, int depth, int sum, int mode);
/*!
   \brief Find the best move based on the score.
   @param[in] board Struct where all pieces are located.
   @param[in] mosse
   @param[in] movesSize
   @param[in] mode
   @param[out] bestMove
*/
int findBestMove(BoardPtr board, struct move* mosse, int movesSize, int mode);
