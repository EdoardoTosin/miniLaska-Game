#include "startMenu.h"

#include <stdio.h>

#include <stdlib.h>

#include "definitions.h"

#include "printCredits.h"

#include "printRules.h"

#include "startGame.h"

void consume(void) {
  int ch;
  while ((ch = getchar()) != '\n' || ch != '\n');
}

void mainMenu(void) {
  system(CLEAR);
  puts("/====================/");
  puts("       MAIN MENU      ");
  puts("/====================/");
  puts("1. Start Game");
  puts("2. Rules");
  puts("3. Credits");
  puts("4. Exit");
  printf("\n");
}

int startGameMenu(void) {
  int subChoice1 = 0;
  int ch;
  while (subChoice1 != 2) {
    system(CLEAR);
    puts("/====================/");
    puts("   START GAME MENU    ");
    puts("/====================/");
    puts("1. Player vs Player");
    puts("2. PC vs Player");
    puts("3. Return");
    puts("4. Exit");
    printf("\n");
    scanf(" %d", & subChoice1);
    if (subChoice1 == 1)
      /**
       * Launch Player vs Player game mode
       */
      return 1;
    else if (subChoice1 == 2)
      /**
       * Launch PC vs Player game mode
       */
      return 2;
    else if (subChoice1 == 3)
      return 3;
    else if (subChoice1 == 4) {
      system(CLEAR);
      puts("Bye Bye!!!");
      exit(0);
    } else
      puts("Invalid Input");
    while ((ch = getchar()) != '\n' || ch != '\n');
  }
}

void rulesMenu(void) {
  int subChoice2 = 0;
  while (subChoice2 != 2) {
    system(CLEAR);
    puts("/====================/");
    puts("         RULES        ");
    puts("/====================/");

    printRules();

    puts("1. Return");
    puts("2. Exit");
    printf("\n");
    scanf(" %d", & subChoice2);
    consume();
    if (subChoice2 == 1)
      return;
    else if (subChoice2 == 2) {
      system(CLEAR);
      puts("Bye Bye!!!");
      exit(0);
    } else
      puts("Invalid Input");
  }
}

void creditsMenu(void) {
  int subChoice3 = 0;
  while (subChoice3 != 2) {
    system(CLEAR);
    puts("/====================/");
    puts("        CREDITS       ");
    puts("/====================/");

    printCredits();

    puts("1. Return");
    puts("2. Exit");
    printf("\n");
    scanf(" %d", & subChoice3);
    consume();
    if (subChoice3 == 1) {
      puts("E' stato scelto di tornare al menu precedente");
      return;
    } else if (subChoice3 == 2) {
      system(CLEAR);
      puts("Bye Bye!!!");
      exit(0);
    } else
      puts("Invalid Input");
  }
}

void printMenu(void) {
  int choice = 0;
  int res = 0;
  while (choice != 4) {
    mainMenu();
    do {
      scanf(" %d", & choice);
      consume();
    } while (choice <= 0 && choice >= 4);

    if (choice == 1) {
      res = startGameMenu();
      if (res == 1)
        match(1);
      else if (res == 2)
        match(2);
    } else if (choice == 2)
      rulesMenu();
    else if (choice == 3)
      creditsMenu();
    else if (choice == 4) {
      system(CLEAR);
      puts("Bye Bye!!!");
      exit(0);
    } else
      puts("Invalid Input!");
  }
}
