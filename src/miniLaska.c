#include <stdio.h>
#include <stdlib.h>
/*
#include <conio.h>
*/
#include <stdbool.h>
/*
#include <string.h>
*/

#include "startGame.h"
#include "endGames.h"
#include "gameControl.h"
#include "structSquare.h"
#include "printBoard.h"

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
        print_board(board);
        */
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

    /*
    Ricordarsi di fare la free di board
    */
    return 0;
}
