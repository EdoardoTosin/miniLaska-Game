#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

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
    system(CLEAR);
    puts("/====================/");
    puts("       miniLaska      ");
    puts("/====================/");
    int c, d;
    for (c = 1; c <= 32767; c++)
       for (d = 1; d <= 32767; d++)
       {}
    printMenu();
    return 0;
}
