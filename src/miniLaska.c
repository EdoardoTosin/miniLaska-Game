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
    int i,j,pedina;
    BoardPointer boardPointer = (struct Board*) malloc(sizeof(struct Board));
    boardPointer->mat = (struct Cella**)malloc(7 * sizeof(struct Cella*));
    for(i=0;i<7;i++) {
        boardPointer->mat[i] = (struct Cella*) malloc(7*sizeof(struct Cella));
        for(j=0;j<7;j++) {
            boardPointer->mat[i][j].pedina = (struct Pedina*) malloc(3*sizeof(struct Pedina));
            for(pedina=0;pedina<3;pedina++) {
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
    int i,j;
    int dim=7;
    for(i=0;i<dim;i++) {
        for(j=0;j<dim;j++) {
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
    int i,j,k;
    for (i = 0; i < 7; ++i) {
        for (j = 0; j < 7; ++j) {
            printf("|");
            for (k = 0; k < 3; ++k) {
                printf("%c",board->mat[i][j].pedina[k].p);
                /*
                if (board->mat[i][j].pedina[1].p=='r'){
                    setcolor(RED);
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
    int k;
    for (k = 0; k < 3; ++k) {
        if (board->mat[i][j].pedina[k].team!=0){
            return false;
        }
    }
    return true;
}
void print_mosse(struct mossa *mosse, int dim){
    int i;
    for (i = 0; i < dim; ++i) {
        printf("Mossa n.%d %d %d - %d %d\n", i + 1, mosse[i].posizioneattuale.riga, mosse[i].posizioneattuale.colonna,
               mosse[i].posizionearrivo.riga, mosse[i].posizionearrivo.colonna);
    }
}
int avanzamento(BoardPointer board,struct mossa *mosse,int turno) {
    int dim = 7;
    int indice =0;
    int i,j,i1,j1;
    bool soloMangiata = false;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++) {
            if((i+j)%2==0 && get_team(board,i,j) == turno) {
                for(i1=i-2; i1<=i+2 ; i1++) {
                    for(j1=j-2; j1<=j+2 ; j1++) {
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
    int dim=get_altezza(board,i,j);
    int k;
    for (k = 0; k < dim; ++k) {
        board->mat[i][j].pedina[k].team = 0;
        board->mat[i][j].pedina[k].p = '-';
        board->mat[i][j].pedina[k].grado = 0;
    }
    board->mat[i][j].height=0;
}
void aggiorna_cella(BoardPointer board, int i,int j){
    int altezza=get_altezza(board,i,j);
    board->mat[i][j].pedina[altezza-1].team = 0;
    board->mat[i][j].pedina[altezza-1].p = '-';
    board->mat[i][j].pedina[altezza-1].grado = 0;
    board->mat[i][j].height=altezza-1;
}
void spostamento_soldato(BoardPointer board,struct mossa mosse){
    int dim=get_altezza(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    int i;
    for (i = 0; i < dim; ++i) {
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[i].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[i].team;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[i].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[i].p;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[i].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[i].grado;
    }
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].height=dim;
    svuota_cella(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    promozione(board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina,mosse.posizionearrivo.riga);
}
void spostamento_mangiata(BoardPointer board,struct mossa mosse){
    int i=(mosse.posizioneattuale.riga+mosse.posizionearrivo.riga)/2;
    int j=(mosse.posizioneattuale.colonna+mosse.posizionearrivo.colonna)/2;
    int altezzattuale=get_altezza(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    int altezzapmedio=get_altezza(board,i,j);
    int altezzatotale=altezzattuale+altezzapmedio;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].team = board->mat[i][j].pedina[altezzapmedio-1].team;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].p = board->mat[i][j].pedina[altezzapmedio-1].p;
    board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[0].grado = board->mat[i][j].pedina[altezzapmedio-1].grado;
    if (altezzattuale==3){
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[1].team;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[1].p;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[1].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[1].grado;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[2].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[2].team;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[2].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[2].p;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[2].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[2].grado;
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].height=3;
    }else{
        int k;
        for (k = 0; k < altezzattuale; ++k) {
            board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[k+1].team = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[k].team;
            board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[k+1].p = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[k].p;
            board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].pedina[k+1].grado = board->mat[mosse.posizioneattuale.riga][mosse.posizioneattuale.colonna].pedina[k].grado;
        }
        board->mat[mosse.posizionearrivo.riga][mosse.posizionearrivo.colonna].height=altezzattuale+1;
    }
    svuota_cella(board,mosse.posizioneattuale.riga,mosse.posizioneattuale.colonna);
    aggiorna_cella(board,i,j);
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
