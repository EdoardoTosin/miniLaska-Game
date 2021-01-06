#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
/*
#include <string.h>*/

#include "definitions.h"
#include "struct.h"
#include "objectCreation.h"
#include "printGame.h"
#include "endGame.h"
#include "gameControl.h"
#include "startGame.h"
#include "printRules.h"
#include "printCredits.h"
#include "startMenu.h"


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
