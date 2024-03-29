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
  delayTimer(1);
  system(CLEAR);
  return;
}

void consume() {
  int ch;
  while ((ch = getchar()) != '\n' || ch != '\n');
}

void printMainMenu() {
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

int difficultyMenu () {
    int subChoice1 = 0;
    int ch;
    while (subChoice1 != 2) {
        system(CLEAR);
        puts("/====================/");
        puts("      DIFFICULTY      ");
        puts("/====================/");
        puts("1. Easy");
        puts("2. Normal");
        puts("3. Hard");
        puts("4. Return");
        puts("5. Exit");
        printf("\n");
        scanf(" %d", & subChoice1);
        if (subChoice1 == 1)
            return EASY;
        else if (subChoice1 == 2)
            return NORMAL;
        else if (subChoice1 == 3)
            return HARD;
        else if (subChoice1 == 4)
            return -1;
        else if (subChoice1 == 5) {
            printExit();
            exit(0);
        } else
            puts("Invalid Input");
        while ((ch = getchar()) != '\n' || ch != '\n');
    }
    return 3;
}

int startGameMenu() {
  int subChoice1 = 0;
  int ch, strength;
  while (subChoice1 != 2) {
    system(CLEAR);
    puts("/====================/");
    puts("   START GAME MENU    ");
    puts("/====================/");
    puts("1. Player vs Player");
    puts("2. Computer vs Player");
    puts("3. Return");
    puts("4. Exit");
    printf("\n");
    scanf(" %d", & subChoice1);
    if (subChoice1 == 1)
      return 1;
    else if (subChoice1 == 2) {
      strength = difficultyMenu()+1;
      return (strength);
    }
    else if (subChoice1 == 3)
      return -1;
    else if (subChoice1 == 4) {
      printExit();
      exit(0);
    } else
      puts("Invalid Input");
    while ((ch = getchar()) != '\n' || ch != '\n');
  }
  return 3;
}

void rulesMenu() {
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

void creditsMenu() {
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
      puts("You choosed to return to the previous menu");
      return;
    } else if (subChoice3 == 2) {
      printExit();
      exit(0);
    } else
      puts("Invalid Input");
  }
}

void controlMenu() {
  int choice = 0;
  int mode;
  while (choice != 4) {
    printMainMenu();
    scanf(" %d", & choice);
    consume();

    if (choice == 1) {
      do{
        mode = startGameMenu();
      } while (mode == 0);
      if (mode > 0)
        match(mode-1);
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
