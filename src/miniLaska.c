#include <stdio.h>
#include <stdlib.h>
/*
#include <conio.h>
*/
#include <stdbool.h>
/*
#include <string.h>
*/

#include "endGame.h"
#include "gameControl.h"
#include "objectCreation.h"
#include "printBoard.h"
#include "startGame.h"

struct Pedina{
    /*
    enum colore colore;*/
    int team;
    char p;
    int grado;
};
/*
typedef struct Pedina* pedina_p;*/
struct Cella{
    int height;
    struct Pedina* pedina;
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
    int riga;
    int colonna;
};
/*
typedef struct Posizione *posizione_p;*/

struct mossa{
    struct Posizione posizioneattuale;
    struct Posizione posizionearrivo;
};
/*
typedef struct mossa* mossa_m;*/
BoardPointer initialize() {
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(7 * sizeof(struct Cella*));
    for(int i=0;i<7;i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(7*sizeof(struct Cella));
        for(int j=0;j<7;j++) {
            boardPointer->mat[i][j].pedina = (struct Pedina*) malloc(3*sizeof(struct Pedina));
            for(int pedina=0;pedina<3;pedina++) {
                boardPointer->mat[i][j].pedina[pedina].team = 0;
                boardPointer->mat[i][j].pedina[pedina].p = '-';
                boardPointer->mat[i][j].pedina[pedina].grado = 0;
                boardPointer->mat[i][j].height = 0;
            }
        }
    }
    return boardPointer;
}

void create_pedina(BoardPointer board){
    int dim=7;
    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            if ((i + j) % 2 == 0 && i!=3) {
                board->mat[i][j].pedina[0].team = i < 3 ? 1 : 2;
                board->mat[i][j].pedina[0].p = i < 3 ? 'r' : 'g';
                board->mat[i][j].pedina[0].grado = 1;
                board->mat[i][j].height=1;
            }
        }
    }
}
void print_board(BoardPointer board){
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            printf("|");
            for (int k = 0; k < 3; ++k) {
                printf("%c",board->mat[i][j].pedina[k].p);
                /*
                if (board->mat[i][j].pedina[1].p=='r'){
                    //setcolor(RED);
                }
                */
            }
        }
        printf("|\n");
    }
}
void promozione(struct Pedina *pedina,int i){
    if (pedina[0].p=='g' && i==0){
        pedina[0].p='G';
        pedina[0].grado=2;
        pedina[0].team=2;
    }
    if (pedina[0].p=='r' && i==6){
        pedina[0].p='R';
        pedina[0].grado=2;
        pedina[0].team=1;
    }
}
int get_altezza(BoardPointer board,int i, int j){
    if(board->mat[i][j].height==0){
        return 0;
    }else{
        return board->mat[i][j].height;
    }
}
int get_team(BoardPointer board,int i,int j){
    if(board->mat[i][j].height==0){
        return 0;
    }else {
        return board->mat[i][j].pedina[get_altezza(board, i, j) - 1].team;
    }
}
int get_grado(BoardPointer board,int i,int j){
    return board->mat[i][j].pedina[get_altezza(board,i,j)-1].grado;
}
bool cella_vuota(BoardPointer board,int i, int j){
    for (int k = 0; k < 3; ++k) {
        if (board->mat[i][j].pedina[k].team!=0){
            return false;
        }
    }
    return true;
}
void print_mosse(struct mossa *mosse, int dim){
    for (int i = 0; i < dim; ++i) {
        printf("Mossa n.%d %d %d - %d %d\n", i + 1, mosse[i].posizioneattuale.riga, mosse[i].posizioneattuale.colonna,
               mosse[i].posizionearrivo.riga, mosse[i].posizionearrivo.colonna);
    }
}
int avanzamento(BoardPointer board,struct mossa *mosse,int turno) {
    int dim = 7;
    int indice =0;
    bool soloMangiata = false;
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++) {
            if((i+j)%2==0 && get_team(board,i,j) == turno) {
                for(int i1=i-2; i1<=i+2 ; i1++) {
                    for(int j1=j-2; j1<=j+2 ; j1++) {
                        int puntoMedioRiga = (i + i1)/2;
                        int puntoMedioColonna = (j + j1)/2;
                        bool condizioneAnd = (i1+j1) %2 ==0 && i1 != i;
                        condizioneAnd = condizioneAnd && i1 < dim && i1 >= 0;
                        condizioneAnd = condizioneAnd && j1 < dim && j1 >= 0;
                        condizioneAnd = condizioneAnd && cella_vuota(board,i1,j1);
                        bool condizioneOr = turno == 1 && i1 > i;
                        condizioneOr = condizioneOr || (turno == 2 && i1<i);
                        condizioneOr = condizioneOr || get_grado(board,i,j) == 2;
                        condizioneAnd = condizioneAnd && condizioneOr;
                        bool isNormalStep = (i1-i)==1;
                        if(condizioneAnd) {
                            int teamPuntoMedio = get_team(board,puntoMedioRiga,puntoMedioColonna);
                            bool mangiata = (teamPuntoMedio != 0 && teamPuntoMedio != turno && !isNormalStep);
                            if((!soloMangiata && (isNormalStep || mangiata)) || (soloMangiata && mangiata)) {
                                if(!soloMangiata && mangiata) {
                                    indice = 0;
                                    soloMangiata = mangiata;
                                }
                                mosse[indice].posizioneattuale.riga=i;
                                mosse[indice].posizioneattuale.colonna=j;
                                mosse[indice].posizionearrivo.riga=i1;
                                mosse[indice].posizionearrivo.colonna=j1;
                                indice++;
                            }
                        }
                    }
                }
            }
        }
    }
    return indice;
}
void svuota_cella(BoardPointer board, int i, int j){
    board->mat[i][j].pedina[0].team = 0;
    board->mat[i][j].pedina[0].p = '-';
    board->mat[i][j].pedina[0].grado = 0;
    board->mat[i][j].height=0;
}
void spostamento_soldato(BoardPointer board,struct mossa mosse){
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].team;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].p;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].grado;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].height=board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].height;
    svuota_cella(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    promozione(board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina,mosse.posizionearrivo.riga);
}
void spostamento_mangiata(BoardPointer board,struct mossa mosse){
    int i=(mosse.posizioneattuale.riga+mosse.posizionearrivo.riga)/2;
    int j=(mosse.posizioneattuale.colonna+mosse.posizionearrivo.colonna)/2;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].team = board->mat[i][j].pedina[0].team;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].p = board->mat[i][j].pedina[0].p;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].grado = board->mat[i][j].pedina[0].grado;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].team;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].p;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[0].grado;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].height=board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].height+board->mat[i][j].height;
    svuota_cella(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    svuota_cella(board,i,j);
}
/*
void vincente(BoardPointer board){

}
*/
int main() {
    int end=0;
    int mossa;
    int turno=1;
    int i=0;
    int j=0;
    BoardPointer board = initialize();
    create_pedina(board);
    print_board(board);
    printf("\n");
    while (!end){
        struct mossa *mosse=(struct mossa *)malloc(sizeof(struct mossa)*11);
        /*
        system("cls");
        print_board(board);*/
        int indice=avanzamento(board,mosse,turno);
        if (indice==0){
            end=1;
            if (turno==2){
                printf("Ha vinto il giocatore 1 in %d mosse",i);
            }else{
                printf("Ha vinto il giocatore 2 in %d mosse",j);
            }
        }
        print_mosse(mosse,indice);
        printf("Seleziona una mossa");
        scanf_s("%d",&mossa);
        if (mosse->posizionearrivo.riga-mosse->posizioneattuale.riga==1){
            spostamento_soldato(board,mosse[mossa-1]);
        }else{
            spostamento_mangiata(board,mosse[mossa-1]);
        }
        printf("il giocatore %d ha eseguito la mossa%d\n",turno,mossa);
        print_board(board);
        if (turno==1){
            turno=2;
            i++;
        }else{
            turno=1;
            j++;
        }
    }

    /*Ricordarsi di fare la free di board*/
    return 0;
}
