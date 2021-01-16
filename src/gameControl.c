#include "gameControl.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "struct.h"
#include "definitions.h"

int getHeight(BoardPointer board, int i, int j) {
    if (board[i][j].height==0)
        return 0;
    else
        return board[i][j].height;
}

int getTeam(BoardPointer board, int i, int j) {
    if (board[i][j].height==0)
        return 0;
    else
        return board[i][j].piece[getHeight(board, i, j) - 1].team;
}

int getRank(BoardPointer board, int i,int j) {
    return board[i][j].piece[getHeight(board, i, j)-1].rank;
}

int isEmpty(BoardPointer board, int i, int j) {
    int k;
    for (k=0; k<HEIGHT; k++)
        if (board[i][j].piece[k].team!=0)
            return 0;
    return 1;
}

int step(BoardPointer board, MossaPointer mosse, int turno) {
    int index = 0;
    int i, j, i1, j1;
    int soloMangiata = 0; /*serve per vedere se è stata trovata almeno una mangiata*/
    int puntoMedioRiga;
    int puntoMedioColonna;
    int condizioneAnd;
    int condizioneOr;
    int isNormalStep;
    int teamPuntoMedio;
    int mangiata;
    for(i=0; i<DIM; i++) {
        for(j=0; j<DIM; j++) {
            if((i+j)%2==0 && getTeam(board, i, j) == turno)
                for(i1=i-2; i1<=i+2; i1++) {
                    for(j1=j-2; j1<=j+2; j1++) {
                        puntoMedioRiga = (i + i1)/2;
                        puntoMedioColonna = (j + j1)/2;
                        condizioneAnd = (i1+j1) %2 ==0 && i1 != i && j1 != j;
                        condizioneAnd = condizioneAnd && i1 < DIM && i1 >= 0;
                        condizioneAnd = condizioneAnd && j1 < DIM && j1 >= 0;
                        condizioneAnd = condizioneAnd && isEmpty(board, i1, j1);
                        condizioneOr = (turno==1) && i1 > i;
                        condizioneOr = condizioneOr || (turno == 2 && i1<i);
                        condizioneOr = condizioneOr || getRank(board, i, j) == 2;
                        condizioneAnd = condizioneAnd && condizioneOr;
                        isNormalStep = abs(i1-i)==1;
                        if(condizioneAnd) {
                            teamPuntoMedio = getTeam(board, puntoMedioRiga, puntoMedioColonna);
                            mangiata = (teamPuntoMedio != 0 && teamPuntoMedio != turno && !isNormalStep);
                            if((!soloMangiata && (isNormalStep || mangiata)) || (soloMangiata && mangiata)) {
                                if(!soloMangiata && mangiata) {
                                    index = 0;
                                    soloMangiata = mangiata;
                                }
                                mosse[index].startPos->row=i;
                                mosse[index].startPos->col=j;
                                mosse[index].endPos->row=i1;
                                mosse[index].endPos->col=j1;
                                index++;
                            }
                        }
                    }
                }
        }
    }
    return index;
}

void deleteCellContent(BoardPointer board, int i, int j) {
    int k;
    int height=getHeight(board, i, j);
    for (k=0; k<height; k++){
        board[i][j].piece[k].team = 0;
        board[i][j].piece[k].p = '-';
        board[i][j].piece[k].rank = 0;
    }
    board[i][j].height=0;
}

void updateCellContent(BoardPointer board, int i, int j) {
    int height=getHeight(board, i, j);
    board[i][j].piece[height-1].team = 0;
    board[i][j].piece[height-1].p = '-';
    board[i][j].piece[height-1].rank = 0;
    board[i][j].height=height-1;
}

void promotion(BoardPointer board, PedinaPointer piece, int i, int j) {
    int altezza=getHeight(board, i, j);
    if (piece[altezza-1].p=='g' && i==0) {
        piece[altezza-1].p='G';
        piece[altezza-1].rank=2;
    }
    if (piece[altezza-1].p=='r' && i==6) {
        piece[altezza-1].p='R';
        piece[altezza-1].rank=2;
    }
}

void normalStep(BoardPointer board, struct mossa mosse) {
    int i;
    int height=getHeight(board, mosse.startPos->row, mosse.startPos->col);
    for (i=0; i<height; i++) {
        board[mosse.endPos->row][mosse.endPos->col].piece[i].team = board[mosse.startPos->row][mosse.startPos->col].piece[i].team;
        board[mosse.endPos->row][mosse.endPos->col].piece[i].p = board[mosse.startPos->row][mosse.startPos->col].piece[i].p;
        board[mosse.endPos->row][mosse.endPos->col].piece[i].rank = board[mosse.startPos->row][mosse.startPos->col].piece[i].rank;
    }
    board[mosse.endPos->row][mosse.endPos->col].height=height;
    deleteCellContent(board,mosse.startPos->row,mosse.startPos->col);
    promotion(board,board[mosse.endPos->row][mosse.endPos->col].piece,mosse.endPos->row,mosse.endPos->col);
}

void eatStep(BoardPointer board, struct mossa mosse) {
    int k;
    int i=(mosse.startPos->row+mosse.endPos->row)/2;
    int j=(mosse.startPos->col+mosse.endPos->col)/2;
    int altezzattuale=getHeight(board, mosse.startPos->row, mosse.startPos->col);
    int altezzapmedio=getHeight(board, i, j);
    board[mosse.endPos->row][mosse.endPos->col].piece[0].team = board[i][j].piece[altezzapmedio-1].team;
    board[mosse.endPos->row][mosse.endPos->col].piece[0].p = board[i][j].piece[altezzapmedio-1].p;
    board[mosse.endPos->row][mosse.endPos->col].piece[0].rank = board[i][j].piece[altezzapmedio-1].rank;
    if (altezzattuale==HEIGHT) {
        for (k=1; k<altezzattuale; k++) {
            board[mosse.endPos->row][mosse.endPos->col].piece[k].team = board[mosse.startPos->row][mosse.startPos->col].piece[k].team;
            board[mosse.endPos->row][mosse.endPos->col].piece[k].p = board[mosse.startPos->row][mosse.startPos->col].piece[k].p;
            board[mosse.endPos->row][mosse.endPos->col].piece[k].rank = board[mosse.startPos->row][mosse.startPos->col].piece[k].rank;
        }
        board[mosse.endPos->row][mosse.endPos->col].height=HEIGHT;
    }
    else{
        for (k=0; k<altezzattuale; k++) {
            board[mosse.endPos->row][mosse.endPos->col].piece[k+1].team = board[mosse.startPos->row][mosse.startPos->col].piece[k].team;
            board[mosse.endPos->row][mosse.endPos->col].piece[k+1].p = board[mosse.startPos->row][mosse.startPos->col].piece[k].p;
            board[mosse.endPos->row][mosse.endPos->col].piece[k+1].rank = board[mosse.startPos->row][mosse.startPos->col].piece[k].rank;
        }
        board[mosse.endPos->row][mosse.endPos->col].height=altezzattuale+1;
    }
    deleteCellContent(board, mosse.startPos->row, mosse.startPos->col);
    updateCellContent(board, i, j);
    promotion(board, board[mosse.endPos->row][mosse.endPos->col].piece, mosse.endPos->row,mosse.endPos->col);
}

void executeStep(BoardPointer board, struct mossa m) {
    if (abs(m.endPos->row-m.startPos->row)==1)
        normalStep(board, m);
    else
        eatStep(board, m);
}


void copyContent(BoardPointer board, struct Cella *cella, int row, int col) {
    int i;
    for(i=0;i<HEIGHT;i++) {
        board[row][col].piece[i].team = cella->piece[i].team;
        board[row][col].piece[i].p = cella->piece[i].p;
        board[row][col].piece[i].rank = cella->piece[i].rank;
        board[row][col].height = cella->height;
    }
}

void revert(BoardPointer board, struct Cella* iniziale, struct Cella*mezzo, struct Cella*finale, struct mossa mossa) {
    int i,j;
    copyContent(board,iniziale,mossa.startPos->row,mossa.startPos->col);
    copyContent(board,finale,mossa.endPos->row,mossa.endPos->col);
    if(mezzo != NULL) {
        i=(mossa.startPos->row+mossa.endPos->row)/2;
        j=(mossa.startPos->col+mossa.endPos->col)/2;
        copyContent(board,mezzo,i,j);
    }
}

struct Cella* copyCella(struct Cella cella) {
    int i;
    struct Cella * c = (struct Cella*) malloc(sizeof(struct Cella));
    c->piece = (PedinaPointer) malloc(HEIGHT*sizeof(struct Pedina));
    for(i=0;i<HEIGHT;i++) {
        c->piece[i].team = cella.piece[i].team;
        c->piece[i].p = cella.piece[i].p;
        c->piece[i].rank = cella.piece[i].rank;
        c->height = cella.height;
    }
    return c;
}

int minimax(BoardPointer board, int isMax, int depth, int somma) {
    int i, best;
    int index;
    int mangiata;
    struct Cella*iniziale;
    struct Cella*finale;
    int imezzo;
    int jmezzo;
    int j;
    struct Cella*mezzo;
    MossaPointer mosse=(MossaPointer) malloc(sizeof(struct mossa)*15);
    for (j = 0; j < 15; ++j) {
        mosse[j].startPos= (PosizionePointer) malloc(sizeof(struct Posizione));
        mosse[j].endPos= (PosizionePointer) malloc(sizeof(struct Posizione));
    }
    index=step(board, mosse, isMax ? 1:2);

    if (index == 0 && !isMax)
        return INT_MAX;

    if (index == 0 && isMax)
        return INT_MIN;

    if (depth == MAX_DEPTH)
        return somma;

    mangiata = abs(mosse->endPos->row-mosse->startPos->row)!=1;

    if (isMax) {
        best = INT_MIN;
        for (i=0; i<index; i++) {
            iniziale = copyCella(board[mosse[i].startPos->row][mosse[i].startPos->col]);
            finale = copyCella(board[mosse[i].endPos->row][mosse[i].endPos->col]);
            imezzo=(mosse[i].startPos->row+mosse[i].endPos->row)/2;
            jmezzo=(mosse[i].startPos->col+mosse[i].endPos->col)/2;
            mezzo = mangiata ? copyCella(board[imezzo][jmezzo]): NULL;
            executeStep(board,mosse[i]);
            best = MAX(best, minimax(board, !isMax,depth + 1, somma + (mangiata ? 1 : 0)) );
            revert(board,iniziale,mezzo,finale,mosse[i]);
            free(iniziale);
            free(finale);
            if(mezzo != NULL) {
                free(mezzo);
            }
        }
        for (j = 0; j < 15; ++j) {
            free(mosse[j].startPos);
            free(mosse[j].endPos);
        }
        free(mosse);
        return best;
    }

    else{
        best = INT_MAX;
        for (i=0; i<index; i++) {
            iniziale = copyCella(board[mosse[i].startPos->row][mosse[i].startPos->col]);
            finale = copyCella(board[mosse[i].endPos->row][mosse[i].endPos->col]);
            imezzo=(mosse[i].startPos->row+mosse[i].endPos->row)/2;
            jmezzo=(mosse[i].startPos->col+mosse[i].endPos->col)/2;
            mezzo = mangiata ? copyCella(board[imezzo][jmezzo]): NULL;
            executeStep(board, mosse[i]);
            best = MIN(best, minimax(board, !isMax, depth+1, somma + (mangiata ? -1 : 0)));
            revert(board,iniziale,mezzo,finale,mosse[i]);
            free(iniziale);
            free(finale);
            if(mezzo != NULL) {
                free(mezzo);
            }
        }
        for (j = 0; j < 15; ++j) {
            free(mosse[j].startPos);
            free(mosse[j].endPos);
        }
        free(mosse);
        return best;
    }
}

int findBestMove(BoardPointer board, MossaPointer mosse, int mosseSize) {
    int i;
    int moveVal=0;
    int bestVal = INT_MIN;
    int bestMove = 0;
    int mangiata;
    struct Cella*iniziale;
    struct Cella*finale;
    int imezzo;
    int jmezzo;
    struct Cella*mezzo;
    for (i=0; i<mosseSize; i++) {
        mangiata = abs(mosse->endPos->row-mosse->startPos->row)!=1;
        iniziale = copyCella(board[mosse[i].startPos->row][mosse[i].startPos->col]);
        finale = copyCella(board[mosse[i].endPos->row][mosse[i].endPos->col]);
        imezzo=(mosse[i].startPos->row+mosse[i].endPos->row)/2;
        jmezzo=(mosse[i].startPos->col+mosse[i].endPos->col)/2;
        mezzo = mangiata ? copyCella(board[imezzo][jmezzo]): NULL;
        executeStep(board,mosse[i]);
        if (mosseSize==1){
            moveVal= mangiata? 1:0;
        }else{
            moveVal = minimax(board, 0,0,mangiata ? 1 : 0);
        }
        if (moveVal > bestVal) {
            bestMove = i;
            bestVal=moveVal;
        }

        revert(board,iniziale,mezzo,finale,mosse[i]);
        free(iniziale);
        free(finale);
        if(mezzo != NULL) {
            free(mezzo);
        }
    }
    printf("The value of the best move is : %d\n\n", bestVal);

    return bestMove;
}
