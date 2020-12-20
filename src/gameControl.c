#include "gameControl.h"

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
