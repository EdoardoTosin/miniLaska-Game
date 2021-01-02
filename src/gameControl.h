#include "struct.h"
#include <stdbool.h>

/* da spostare in file utility
bool isDiff(BoardPointer board1, BoardPointer board2) {
    for(int i=0;i<7;i++) {
        for(int j=0;j<7;j++) {
            for(int k=0;k<3;k++) {
                if(board1->mat[i][k].piece[k].p != board2->mat[i][k].piece[k].p) {
                    return true;
                }
            }
        }
    }
    return false;
}
*/

int getHeight(BoardPointer board, int i, int j);

int getTeam(BoardPointer board,int i,int j);

int getRank(BoardPointer board,int i,int j);

bool cella_vuota(BoardPointer board,int i, int j);

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

int minimax(BoardPointer board, bool isMax, int depth,int somma);

int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize);
