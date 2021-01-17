#include "startMenu.h"

#include <stdio.h>

#include <stdlib.h>

#include "definitions.h"

#include "printCredits.h"

#include "printRules.h"

#include "startGame.h"

void delayTimer(int timeDelay) {
  #ifdef _WIN32
  Sleep(timeDelay);
  #else
  sleep(timeDelay);
  #endif
}

void printExit() {
  system(CLEAR);
  puts("/====================/");
  puts("      BYE BYE!!!      ");
  puts("/====================/");
  delayTimer(2);
  system(CLEAR);
  return;
}

void consume(void) {
  int ch;
  while ((ch = getchar()) != '\n' || ch != '\n');
}

void printMainMenu(void) {
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
      return 1;
    else if (subChoice1 == 2)
      return 2;
    else if (subChoice1 == 3)
      return 3;
    else if (subChoice1 == 4) {
      printExit();
      exit(0);
    } else
      puts("Invalid Input");
    while ((ch = getchar()) != '\n' || ch != '\n');
  }
  return 3;
}

int difficultyenu (void) {
    int subChoice1 = 0;
    int ch;
    while (subChoice1 != 2) {
        system(CLEAR);
        puts("/====================/");
        puts("      DIFFICOLTA      ");
        puts("/====================/");
        puts("1. Principiante");
        puts("2. Dilettante");
        puts("3. Campione");
        puts("4. Return");
        puts("5. Exit");
        printf("\n");
        scanf(" %d", & subChoice1);
        if (subChoice1 == 1)
            return 1;
        else if (subChoice1 == 2)
            return 2;
        else if (subChoice1 == 3)
            return 3;
        else if (subChoice1 == 4)
            return 4;
        else if (subChoice1 == 5) {
            printExit();
            exit(0);
        } else
            puts("Invalid Input");
        while ((ch = getchar()) != '\n' || ch != '\n');
    }
    return 3;
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
      printExit();
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
      printExit();
      exit(0);
    } else
      puts("Invalid Input");
  }
}

void controlMenu(void) {
  int choice = 0;
  int mode;
  while (choice != 4) {
    printMainMenu();
    scanf(" %d", & choice);
    consume();

    if (choice == 1) {
      mode = startGameMenu();
      if (mode == 1 || mode == 2) {
        match(mode);
      }
    } else if (choice == 2)
      rulesMenu();
    else if (choice == 3)
      creditsMenu();
    else if (choice == 4) {
      printExit();
      exit(0);
    } else {
      system(CLEAR);
      puts("/====================/");
      puts("     Invalid Input!   ");
      puts("/====================/");
      delayTimer(1);
    }
  }
}
