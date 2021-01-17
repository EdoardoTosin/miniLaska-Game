/*!
   @mainpage miniLaska Documentation
*/
#include <stdio.h>

#include <stdlib.h>

#include "definitions.h"

#include "objectCreation.h"

#include "printGame.h"

#include "gameControl.h"

#include "startGame.h"

#include "printRules.h"

#include "printCredits.h"

#include "startMenu.h"

/*!
   \brief Main entry point of the program.
*/
int main(void) {
  system(CLEAR);
  puts("/====================/");
  puts("       miniLaska      ");
  puts("/====================/");
  delayTimer(1);
  controlMenu();
  return 0;
}
