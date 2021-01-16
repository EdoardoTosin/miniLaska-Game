/*!
   @mainpage Variant of the game called Lasca
*/
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

/**
 * Main entry point of the program.
 */
int main(void) {
  int i, j;
  int timeDelay = 5;
  system(CLEAR);
  puts("/====================/");
  puts("       miniLaska      ");
  puts("/====================/");
  delayTimer(timeDelay);
  printMenu();
  return 0;
}
