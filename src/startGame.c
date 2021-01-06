#include "startGame.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "definitions.h"
#include "printGame.h"
#include "gameControl.h"
#include "objectCreation.h"

void match(void) {
    int choice, index;
    int end=0, turno=1, i=0, j=0;
    char player='R';
    BoardPointer board = initialize();
    printBoard(board);
    while (!end) {
        printf("\n");
        MossaPointer mosse=(MossaPointer)malloc(sizeof(struct mossa)*15);
        index=avanzamento(board, mosse, turno);
        if (index==0) {
            end=1;
            if (turno==1)
                printf("Ha vinto il giocatore G in %d mosse\n\n", i);
            else
                printf("Ha vinto il giocatore R in %d mosse\n\n", j);
        }
        else{
            if (turno==1) {
                printf("TURNO GIOCATORE %c\n", player);
                printMoves(mosse,index);
                int mossa=findBestMove(board, mosse, index);
                printf("mossa%d\n",mossa+1);
                eseguiSpostamento(board, mosse[mossa]);
                printBoard(board);
                printf("Il giocatore %c ha eseguito la mossa %d\n", player, mossa+1);
                turno=2;
                player='G';
                i++;
            }
            else{
                printf("TURNO GIOCATORE %c\n", player);
                printMoves(mosse, index);
                printf("\nInserire numero mossa: ");
                do{
                    scanf/*_s*/("%d", &choice);
                } while (choice<1 || choice>index);
                eseguiSpostamento(board, mosse[choice -1 ]);
                printBoard(board);
                printf("Il giocatore %c ha eseguito la mossa %d\n", player, choice);
                turno=1;
                player='R';
                j++;
            }
        }
        free(mosse);
    }
    free(board);
}
