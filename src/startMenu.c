#include "startMenu.h"
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

void printStartMenu(void){
  system(CLEAR);
  puts("/====================/");
  puts("       MAIN MENU      ");
  puts("/====================/");
  puts("1. Start Game");
  puts("2. Rules");
  puts("3. Credits");
  puts("4. Exit");
  printf("\n");
  return;
}

void printStartGame(void){
  int subChoice1 = 0;
  system(CLEAR);
  puts("E' stato scelto il submenu 1");
  while (subChoice1 != 2) {
    puts("/====================/");
    puts("          START MENU    ");
    puts("/====================/");
    puts("1. Player vs Player");
    puts("2. PC vs Player");
    puts("3. Return");
    puts("4. Exit");
    printf("\n");
    scanf("%d", &subChoice1);
    if (subChoice1 == 1) {
      puts("E' stato scelta l'opzione 1");
      /*
      Launch Player vs Player game mode*/
    }
    else if (subChoice1 == 2) {
      puts("E' stato scelta l'opzione 2");
      /*
      Launch PC vs Player game mode*/
    }
    else if (subChoice1 == 3) {
      puts("E' stato scelto di tornare al menu precedente");
      return;
    }
    else if (subChoice1 == 4) {
      puts("E' stato scelto di uscire");
      exit(0);
    }
    else {
      puts("Invalid Input");
    }
  }
  return;
}

void printRules(void){
  int subChoice2 = 0;
  system(CLEAR);
  puts("E' stato scelto il submenu 2");
  while (subChoice2 != 2) {
    puts("/====================/");
    puts("           RULES    ");
    puts("/====================/");
    /*
    Print rules*/
    puts("1. Return");
    puts("2. Exit");
    printf("\n");
    scanf("%d", &subChoice2);
    if (subChoice2 == 1) {
      puts("E' stato scelto di tornare al menu precedente");
      return;
    } else if (subChoice2 == 2) {
      puts("E' stato scelto di uscire");
      exit(0);
    } else {
      puts("Invalid Input");
    }
  }
  return;
}

void printCredits(void){
  int subChoice3 = 0;
  system(CLEAR);
  puts("E' stato scelto il submenu 3");
  while (subChoice3 != 2) {
    puts("/====================/");
    puts("           CREDITS    ");
    puts("/====================/");
    /*
    Print credits*/
    puts("1. Return");
    puts("2. Exit");
    printf("\n");
    scanf("%d", &subChoice3);
    if (subChoice3 == 1) {
      puts("E' stato scelto di tornare al menu precedente");
      return;
    } else if (subChoice3 == 2) {
      puts("E' stato scelto di uscire");
      exit(0);
    } else {
      puts("Invalid Input");
    }
  }
  return;
}

int startMenu(void) {
  int choice = 0;
  while (choice != 4) {
    printStartMenu();
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        printStartGame();
        break;
      case 2:
        printRules();
        break;
      case 3:
        printCredits();
        break;
      case 4:
        printf("E' stato scelto di uscire");
        exit(0);
        break;
      default:
        puts("Invalid Input!");
      }
  }
  return 0;
}
