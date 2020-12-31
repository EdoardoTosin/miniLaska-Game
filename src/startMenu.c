#include "startMenu.h"

#include <stdio.h>
#include <stdlib.h>

void printStartMenu(){
  system(CLEAR);
  puts("/====================/");
  puts("       MAIN MENU      ");
  puts("/====================/");
  puts("1. Start Game");
  puts("2. Rules");
  puts("3. Credits");
  puts("4. Exit");
  printf(">>");
  return;
}

void printStartGame(){
  system(CLEAR);
  puts("E' stato scelto il submenu 1");
  int subChoice1 = 0;
  while (subChoice1 != 2) {
    puts("/====================/");
    puts("          START MENU    ");
    puts("/====================/");
    puts("1. Player vs Player");
    puts("2. PC vs Player");
    puts("3. Return");
    puts("4. Exit");
    printf(">>>");
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

void printRules(){
  system(CLEAR);
  puts("E' stato scelto il submenu 2");
  int subChoice2 = 0;
  while (subChoice2 != 2) {
    puts("/====================/");
    puts("           RULES    ");
    puts("/====================/");
    /*
    Print rules*/
    puts("1. Return");
    puts("2. Exit");
    printf(">>>");
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

void printCredits(){
  system("cls");
  puts("E' stato scelto il submenu 3");
  int subChoice3 = 0;
  while (subChoice3 != 2) {
    puts("/====================/");
    puts("           CREDITS    ");
    puts("/====================/");
    /*
    Print credits*/
    puts("1. Return");
    puts("2. Exit");
    printf(">>>");
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

int startMenu() {
  int choice = 0;
  while (StartMenu();
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
