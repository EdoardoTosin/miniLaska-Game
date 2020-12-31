#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
/*
#include <string.h>*/

#include "endGame.h"
#include "gameControl.h"
#include "objectCreation.h"
#include "printBoard.h"
#include "startGame.h"
#include "startMenu.h"

#define DIM 7
#define HEIGHT 3
#define ROW 65
#define MAX_DEPTH 4

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct Pedina{
    int team;
    char p;
    int rank;
};
/*
typedef struct Pedina* pedina_p;*/
struct Cella{
    int height;
    struct Pedina* piece;
};

/*
typedef struct Square*cella_c;*/

struct Board{
    struct Cella **mat;
};
typedef struct Board* BoardPointer;
/*
int partita=0;
int turno=1;
typedef struct Board board_b;*/

struct Posizione{
    int row;
    int col;
};
/*
typedef struct Posizione *posizione_p;*/

struct mossa{
    struct Posizione startPos;
    struct Posizione endPos;
};

/*
typedef struct mossa* mossa_m;*/
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
BoardPointer copyBoard(BoardPointer board) {
    int i, j, piece;
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(DIM * sizeof(struct Cella*));
    for(i=0; i<DIM; i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(DIM * sizeof(struct Cella));
        for(j=0; j<DIM; j++) {
            boardPointer->mat[i][j].piece = (struct Pedina*) malloc(HEIGHT*sizeof(struct Pedina));
            for(piece=0; piece<HEIGHT; piece++) {
                boardPointer->mat[i][j].piece[piece].team =  board->mat[i][j].piece[piece].team;
                boardPointer->mat[i][j].piece[piece].p = board->mat[i][j].piece[piece].p;
                boardPointer->mat[i][j].piece[piece].rank = board->mat[i][j].piece[piece].rank;
                boardPointer->mat[i][j].height = board->mat[i][j].height;
            }
        }
    }
    return boardPointer;
}
BoardPointer initialize() {
    int i, j, h;
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(DIM * sizeof(struct Cella*));
    for(i=0; i<DIM; i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(DIM * sizeof(struct Cella));
        for(j=0; j<DIM; j++) {
            boardPointer->mat[i][j].piece = (struct Pedina*) malloc(HEIGHT*sizeof(struct Pedina));
            for(h=0; h<HEIGHT; h++) {
                boardPointer->mat[i][j].piece[h].team = 0;
                boardPointer->mat[i][j].piece[h].p = '-';
                boardPointer->mat[i][j].piece[h].rank = 0;
                boardPointer->mat[i][j].height = 0;
            }
        }
    }
    return boardPointer;
}

void create_pedina(BoardPointer board) {
    int i,j;
    for (i=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
            if ((i + j) % 2 == 0 && i!=3) {
                board->mat[i][j].piece[0].team = i < 3 ? 1 : 2;
                board->mat[i][j].piece[0].p = i < 3 ? 'r' : 'g';
                board->mat[i][j].piece[0].rank = 1;
                board->mat[i][j].height=1;
            }
        }
    }
}

void print_board(BoardPointer board) {
    char white=1;
    int i, j, k, l;
    /*system(CLEAR);*/
    printf(" ");
    for (j=0; j<DIM; j++)
        printf("   %d", j);
    printf("\n");
    for (i=0; i<DIM; i++) {
        printf("  +");
        for (l=0; l<DIM; l++)
            printf("---+");
        printf("\n%c ", ROW+i);
        for (j=0; j<DIM; j++) {
            if ((i+j)%2==0) {
                printf("|");
                for (k=0; k<HEIGHT; k++)
                    if (board->mat[i][j].piece[k].p == '-')
                        printf(" ");
                    else
                        printf("%c", board->mat[i][j].piece[k].p);
                //printf("%d", board->mat[i][j].height);
            }
            else{
                printf("|");
                for (k=0; k<HEIGHT; k++)
                    printf("%c",white);
            }
        }
        printf("|\n");
    }
    printf("  +");
    for (l=0; l<DIM; l++)
        printf("---+");
    printf("\n");
}

int getHeight(BoardPointer board, int i, int j) {
    if (board->mat[i][j].height==0)
        return 0;
    else
        return board->mat[i][j].height;
}

struct Cella * copyCella(struct Cella cella) {
    struct Cella * c = (struct Cella*) malloc(sizeof(struct Cella));
    c->piece = (struct Pedina*) malloc(HEIGHT*sizeof(struct Pedina));
    for(int i=0;i<HEIGHT;i++) {
        c->piece[i].team = cella.piece[i].team;
        c->piece[i].p = cella.piece[i].p;
        c->piece[i].rank = cella.piece[i].rank;
        c->height = cella.height;
    }
    return c;
}

int getTeam(BoardPointer board,int i,int j) {
    if (board->mat[i][j].height==0)
        return 0;
    else
        return board->mat[i][j].piece[getHeight(board, i, j) - 1].team;
}

int getRank(BoardPointer board,int i,int j) {
    return board->mat[i][j].piece[getHeight(board, i, j)-1].rank;
}

bool cella_vuota(BoardPointer board,int i, int j) {
    int k;
    for (k=0; k<HEIGHT; k++)
        if (board->mat[i][j].piece[k].team!=0)
            return false;
    return true;
}

void promozione(BoardPointer board, struct Pedina *piece, int i, int j) {
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
void promozionereverse(BoardPointer board, struct Pedina *piece, int i, int j, int rank) {
    int altezza=getHeight(board, i, j);
    if (rank==1) {
        if (piece[altezza - 1].p == 'G') {
            piece[altezza - 1].p = 'g';
            piece[altezza - 1].rank = 1;
        }
        if (piece[altezza - 1].p == 'R') {
            piece[altezza - 1].p = 'r';
            piece[altezza - 1].rank = 1;
        }
    }
}

void print_mosse(struct mossa *mosse, int dim) {
    int i;
    for (i=0; i<dim; i++)
        printf("Mossa n.%d %c %d - %c %d\n", i + 1, ROW+mosse[i].startPos.row, mosse[i].startPos.col, ROW+mosse[i].endPos.row, mosse[i].endPos.col);
}

int avanzamento(BoardPointer board,struct mossa *mosse, int turno) {
    int index = 0;
    int i, j, i1, j1;
    bool soloMangiata = false; /*serve per vedere se è stata trovata almeno una mangiata*/
    for(i=0; i<DIM; i++) {
        for(j=0; j<DIM; j++) {
            if((i+j)%2==0 && getTeam(board, i, j) == turno)
                for(i1=i-2; i1<=i+2; i1++) {
                    for(j1=j-2; j1<=j+2; j1++) {
                        int puntoMedioRiga = (i + i1)/2;
                        int puntoMedioColonna = (j + j1)/2;
                        bool condizioneAnd = (i1+j1) %2 ==0 && i1 != i && j1 != j;
                        condizioneAnd = condizioneAnd && i1 < DIM && i1 >= 0;
                        condizioneAnd = condizioneAnd && j1 < DIM && j1 >= 0;
                        condizioneAnd = condizioneAnd && cella_vuota(board, i1, j1);
                        bool condizioneOr = (turno==1) && i1 > i;
                        condizioneOr = condizioneOr || (turno == 2 && i1<i);
                        condizioneOr = condizioneOr || getRank(board, i, j) == 2;
                        condizioneAnd = condizioneAnd && condizioneOr;
                        bool isNormalStep = abs(i1-i)==1;
                        if(condizioneAnd) {
                            int teamPuntoMedio = getTeam(board, puntoMedioRiga, puntoMedioColonna);
                            bool mangiata = (teamPuntoMedio != 0 && teamPuntoMedio != turno && !isNormalStep);
                            if((!soloMangiata && (isNormalStep || mangiata)) || (soloMangiata && mangiata)) {
                                if(!soloMangiata && mangiata) {
                                    index = 0;
                                    soloMangiata = mangiata;
                                }
                                mosse[index].startPos.row=i;
                                mosse[index].startPos.col=j;
                                mosse[index].endPos.row=i1;
                                mosse[index].endPos.col=j1;
                                index++;
                            }
                        }
                    }
                }
        }
    }
    return index;
}

void aggiorna_cella(BoardPointer board, int i, int j) {
    int height=getHeight(board, i, j);
    board->mat[i][j].piece[height-1].team = 0;
    board->mat[i][j].piece[height-1].p = '-';
    board->mat[i][j].piece[height-1].rank = 0;
    board->mat[i][j].height=height-1;
}

void svuota_cella(BoardPointer board, int i, int j) {
    int k;
    int height=getHeight(board, i, j);
    for (k=0; k<height; k++){
        board->mat[i][j].piece[k].team = 0;
        board->mat[i][j].piece[k].p = '-';
        board->mat[i][j].piece[k].rank = 0;
    }
    board->mat[i][j].height=0;
}

void spostamento_soldato(BoardPointer board, struct mossa mosse) {
    int i;
    int height=getHeight(board, mosse.startPos.row, mosse.startPos.col);
    for (i=0; i<height; i++) {
        board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].team = board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].team;
        board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].p = board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].p;
        board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].rank = board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].rank;
    }
    board->mat[mosse.endPos.row][mosse.endPos.col].height=height;
    svuota_cella(board,mosse.startPos.row,mosse.startPos.col);
    promozione(board,board->mat[mosse.endPos.row][mosse.endPos.col].piece,mosse.endPos.row,mosse.endPos.col);
}
void spostamento_soldatoreverse(BoardPointer board, struct mossa mosse,int altezzastart,int rank) {
    int i;
    promozionereverse(board,board->mat[mosse.endPos.row][mosse.endPos.col].piece, mosse.endPos.row,mosse.endPos.col,rank);
    for (i=0; i<altezzastart; i++) {
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].team=board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].team;
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].p=board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].p;
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[i].rank=board->mat[mosse.endPos.row][mosse.endPos.col].piece[i].rank;
    }
    board->mat[mosse.startPos.row][mosse.startPos.col].height=altezzastart;
    svuota_cella(board,mosse.endPos.row,mosse.endPos.col);
}

void spostamento_mangiata(BoardPointer board, struct mossa mosse) {
    int k;
    int i=(mosse.startPos.row+mosse.endPos.row)/2;
    int j=(mosse.startPos.col+mosse.endPos.col)/2;
    int altezzattuale=getHeight(board, mosse.startPos.row, mosse.startPos.col);
    int altezzapmedio=getHeight(board, i, j);
    board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].team = board->mat[i][j].piece[altezzapmedio-1].team;
    board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].p = board->mat[i][j].piece[altezzapmedio-1].p;
    board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].rank = board->mat[i][j].piece[altezzapmedio-1].rank;
    if (altezzattuale==HEIGHT) {
        for (k=1; k<altezzattuale; k++) {
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].team = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].team;
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].p = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].p;
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].rank = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].rank;
        }
        board->mat[mosse.endPos.row][mosse.endPos.col].height=HEIGHT;
    }
    else{
        for (k=0; k<altezzattuale; k++) {
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].team = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].team;
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].p = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].p;
            board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].rank = board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].rank;
        }
        board->mat[mosse.endPos.row][mosse.endPos.col].height=altezzattuale+1;
    }
    svuota_cella(board, mosse.startPos.row, mosse.startPos.col);
    aggiorna_cella(board, i, j);
    promozione(board, board->mat[mosse.endPos.row][mosse.endPos.col].piece, mosse.endPos.row,mosse.endPos.col);
}
void spostamento_mangiatareverse(BoardPointer board, struct mossa mosse,int altezzastart,int rank) {
    int k;
    int i=(mosse.startPos.row+mosse.endPos.row)/2;
    int j=(mosse.startPos.col+mosse.endPos.col)/2;
    int altezzattuale=getHeight(board, mosse.endPos.row, mosse.endPos.col);
    int altezzapmedio=getHeight(board, i, j);
    promozionereverse(board,board->mat[mosse.endPos.row][mosse.endPos.col].piece, mosse.endPos.row,mosse.endPos.col,rank);
    board->mat[i][j].piece[altezzapmedio].team = board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].team;
    board->mat[i][j].piece[altezzapmedio].p =board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].p;
    board->mat[i][j].piece[altezzapmedio].rank = board->mat[mosse.endPos.row][mosse.endPos.col].piece[0].rank;
    if (altezzastart==HEIGHT) {
        for (k=0; k<altezzastart; k++) {
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].team=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].team;
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].p=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].p;
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].rank=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k].rank;
        }
        board->mat[mosse.startPos.row][mosse.startPos.col].height=HEIGHT;
    }else if (altezzastart==2){
        for (k=0; k<altezzastart; k++) {
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].team=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].team;
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].p=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].p;
            board->mat[mosse.startPos.row][mosse.startPos.col].piece[k].rank=board->mat[mosse.endPos.row][mosse.endPos.col].piece[k+1].rank;
        }
        board->mat[mosse.startPos.row][mosse.startPos.col].height=altezzastart;
    }else{
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[0].team=board->mat[mosse.endPos.row][mosse.endPos.col].piece[1].team;
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[0].p=board->mat[mosse.endPos.row][mosse.endPos.col].piece[1].p;
        board->mat[mosse.startPos.row][mosse.startPos.col].piece[0].rank=board->mat[mosse.endPos.row][mosse.endPos.col].piece[1].rank;
        board->mat[mosse.startPos.row][mosse.startPos.col].height=altezzastart;
    }
    board->mat[i][j].height=getHeight(board,i,j)+1;
    svuota_cella(board,mosse.endPos.row,mosse.endPos.col);
}

void eseguiSpostamento(BoardPointer board,struct mossa m) {
    if (abs(m.endPos.row-m.startPos.row)==1)
        spostamento_soldato(board, m);
    else
        spostamento_mangiata(board, m);
}


void copyContent(BoardPointer board, struct Cella *cella,int row,int col) {
    for(int i=0;i<HEIGHT;i++) {
        board->mat[row][col].piece[i].team = cella->piece[i].team;
        board->mat[row][col].piece[i].p = cella->piece[i].p;
        board->mat[row][col].piece[i].rank = cella->piece[i].rank;
        board->mat[row][col].height = cella->height;
    }
}

void revert(BoardPointer board, struct Cella* iniziale,struct Cella*mezzo, struct Cella*finale, struct mossa mossa) {
    copyContent(board,iniziale,mossa.startPos.row,mossa.startPos.col);
    copyContent(board,finale,mossa.endPos.row,mossa.endPos.col);
    if(mezzo != NULL) {
        int i=(mossa.startPos.row+mossa.endPos.row)/2;
        int j=(mossa.startPos.col+mossa.endPos.col)/2;
        copyContent(board,mezzo,i,j);

    }

}
int minimax(BoardPointer board, bool isMax, int depth,int somma) {
    int i, best;
    struct mossa *mosse=(struct mossa*) malloc(sizeof(struct mossa)*15);
    int index=avanzamento(board, mosse, isMax ? 1:2);

    if (index == 0 && !isMax)
        return INT_MAX;

    if (index == 0 && isMax)
        return INT_MIN;

    if (depth == MAX_DEPTH)
        return somma;

    bool mangiata = abs(mosse->endPos.row-mosse->startPos.row)!=1;

    if (isMax) {
        best = INT_MIN;
        for (i=0; i<index; i++) {
            int altezzastart=getHeight(board,mosse[i].startPos.row,mosse[i].startPos.col);
            int rank=getRank(board,mosse[i].startPos.row,mosse[i].startPos.col);
            struct Cella*iniziale = copyCella(board ->mat[mosse[i].startPos.row][mosse[i].startPos.col]);
            struct Cella*finale = copyCella(board ->mat[mosse[i].endPos.row][mosse[i].endPos.col]);
            int imezzo=(mosse[i].startPos.row+mosse[i].endPos.row)/2;
            int jmezzo=(mosse[i].startPos.col+mosse[i].endPos.col)/2;
            struct Cella*mezzo = mangiata ? copyCella(board->mat[imezzo][jmezzo]): NULL;
            BoardPointer boarddd=copyBoard(board);
            eseguiSpostamento(board,mosse[i]);
            BoardPointer boardSpostamento=copyBoard(board);
            best = MAX(best, minimax(board, !isMax,depth + 1, somma + (mangiata ? 1 : 0)) );
            revert(board,iniziale,mezzo,finale,mosse[i]);
            free(iniziale);
            free(finale);
            if(mezzo != NULL) {
                free(mezzo);
            }
            if (isDiff(boarddd,board)){
                printf("*********************************************************************************************************************************************");
                printf("start row %d - start col %d - end row %d - end col %d\n",mosse[i].startPos.row,mosse[i].startPos.col,mosse[i].endPos.row,mosse[i].endPos.col);
                print_board(boarddd);
                print_board(boardSpostamento);
                print_board(board);
            }
        }
        free(mosse);
        return best;
    }

    else{
        best = INT_MAX;
        for (i=0; i<index; i++) {
            int altezzastart=getHeight(board,mosse[i].startPos.row,mosse[i].startPos.col);
            int rank=getRank(board,mosse[i].startPos.row,mosse[i].startPos.col);
            struct Cella*iniziale = copyCella(board ->mat[mosse[i].startPos.row][mosse[i].startPos.col]);
            struct Cella*finale = copyCella(board ->mat[mosse[i].endPos.row][mosse[i].endPos.col]);
            int imezzo=(mosse[i].startPos.row+mosse[i].endPos.row)/2;
            int jmezzo=(mosse[i].startPos.col+mosse[i].endPos.col)/2;
            struct Cella*mezzo = mangiata ? copyCella(board->mat[imezzo][jmezzo]): NULL;
            BoardPointer boarddd=copyBoard(board);
            eseguiSpostamento(board, mosse[i]);
            BoardPointer boardSpostamento=copyBoard(board);
            best = MIN(best, minimax(board, !isMax, depth+1, somma + (mangiata ? -1 : 0)));
            revert(board,iniziale,mezzo,finale,mosse[i]);
            free(iniziale);
            free(finale);
            if(mezzo != NULL) {
                free(mezzo);
            }
            if (isDiff(boarddd,board)){
                printf("*********************************************************************************************************************************************");
                printf("start row %d - start col %d - end row %d - end col %d\n",mosse[i].startPos.row,mosse[i].startPos.col,mosse[i].endPos.row,mosse[i].endPos.col);
                print_board(boarddd);
                print_board(boardSpostamento);
                print_board(board);
            }
        }
        free(mosse);
        return best;
    }
}

int findBestMove(BoardPointer board, struct mossa* mosse, int mosseSize) {
    int i;
    int bestVal = INT_MIN;
    int bestMove = 0;
    for (i=0; i<mosseSize; i++) {
        bool mangiata = abs(mosse->endPos.row-mosse->startPos.row)!=1;
        int altezzastart=getHeight(board,mosse[i].startPos.row,mosse[i].startPos.col);
        int rank=getRank(board,mosse[i].startPos.row,mosse[i].startPos.col);
        struct Cella*iniziale = copyCella(board ->mat[mosse[i].startPos.row][mosse[i].startPos.col]);
        struct Cella*finale = copyCella(board ->mat[mosse[i].endPos.row][mosse[i].endPos.col]);
        int imezzo=(mosse[i].startPos.row+mosse[i].endPos.row)/2;
        int jmezzo=(mosse[i].startPos.col+mosse[i].endPos.col)/2;
        struct Cella*mezzo = mangiata ? copyCella(board->mat[imezzo][jmezzo]): NULL;
        BoardPointer boarddd=copyBoard(board);
        eseguiSpostamento(board,mosse[i]);

        int moveVal = minimax(board, false,0,mangiata ? 1 : 0);
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
    printf("The value of the best Move is : %d\n\n", bestVal);

    return bestMove;
}

void match(void) {
    int choice, index;
    int end=0, turno=1, i=0, j=0;
    char player='R';
    BoardPointer board = initialize();
    create_pedina(board);
    print_board(board);
    while (!end) {
        printf("\n");
        struct mossa *mosse=(struct mossa *)malloc(sizeof(struct mossa)*15);
        index=avanzamento(board, mosse, turno);
        if (index==0) {
            end=1;
            if (turno==2)
                printf("Ha vinto il giocatore G in %d mosse\n\n", i);
            else
                printf("Ha vinto il giocatore R in %d mosse\n\n", j);
        }
        else{
            if (turno==1) {
                printf("TURNO GIOCATORE %c\n", player);
                print_mosse(mosse,index);
                int mossa=findBestMove(board, mosse, index);
                printf("mossa%d\n",mossa+1);
                eseguiSpostamento(board, mosse[mossa]);
                print_board(board);
                printf("Il giocatore %c ha eseguito la mossa %d\n", player, mossa+1);
                turno=2;
                player='G';
                i++;
            }
            else{
                printf("TURNO GIOCATORE %c\n", player);
                print_mosse(mosse, index);
                printf("\nInserire numero mossa: ");
                do{
                    scanf/*_s*/("%d", &choice);
                } while (choice<1 || choice>index);
                eseguiSpostamento(board, mosse[choice -1 ]);
                print_board(board);
                printf("Il giocatore %c ha eseguito la mossa %d\n", player, choice);
                turno=1;
                player='R';
                j++;
            }
        }
    }
    free(board);
    /*
    Ricordarsi di fare la free di mosse*/
}

int main(void) {
    char start='0';
    do{
        /*system(CLEAR);*/
        printf("\nminiLaska GAME\n\nPress F to start the game\n\n");
        scanf(" %c", &start);
    } while(start!='f' && start!='F');
    do{
        match();
        printf("Do you want to play again? (y for yes)\n\n");
        scanf(" %c", &start);
    } while(start=='y' || start=='Y');
    return 0;
}
