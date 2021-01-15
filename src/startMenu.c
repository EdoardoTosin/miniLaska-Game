#include "startMenu.h"
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "printCredits.h"
#include "printRules.h"
#include "startGame.h"

void mainMenu(void){
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

int startGameMenu(void){
    int subChoice1 = 0;
    system(CLEAR);
    while (subChoice1 != 2) {
        puts("/====================/");
        puts("   START GAME MENU    ");
        puts("/====================/");
        puts("1. Player vs Player");
        puts("2. PC vs Player");
        puts("3. Return");
        puts("4. Exit");
        printf("\n");
        scanf("%d", &subChoice1);
        if (subChoice1 == 1) {
            puts("E' stato scelta l'opzione 1");
            /** Launch Player vs Player game mode
              */
            return 1;
        }
        else if (subChoice1 == 2) {
            puts("E' stato scelta l'opzione 2");
            /** Launch PC vs Player game mode
              */
            return 2;
        }
        else if (subChoice1 == 3) {
            puts("E' stato scelto di tornare al menu precedente");
            return 3;
        }
        else if (subChoice1 == 4) {
            puts("E' stato scelto di uscire");
            exit(0);
        }
        else
            puts("Invalid Input");
    }
}

void rulesMenu(void){
    int subChoice2 = 0;
    system(CLEAR);
    while (subChoice2 != 2) {
        puts("/====================/");
        puts("         RULES        ");
        puts("/====================/");

        printRules();

        puts("1. Return");
        puts("2. Exit");
        printf("\n");
        scanf("%d", &subChoice2);
        if (subChoice2 == 1) {
            puts("E' stato scelto di tornare al menu precedente");
            return;
        }
        else if (subChoice2 == 2) {
            puts("E' stato scelto di uscire");
            exit(0);
        }
        else
            puts("Invalid Input");
    }
    return;
}

void creditsMenu(void){
    int subChoice3 = 0;
    system(CLEAR);
    while (subChoice3 != 2) {
        puts("/====================/");
        puts("        CREDITS       ");
        puts("/====================/");

        printCredits();

        puts("1. Return");
        puts("2. Exit");
        printf("\n");
        scanf("%d", &subChoice3);
        if (subChoice3 == 1) {
            puts("E' stato scelto di tornare al menu precedente");
            return;
        }
        else if (subChoice3 == 2) {
            puts("E' stato scelto di uscire");
            exit(0);
        }
        else
            puts("Invalid Input");
    }
}

void printMenu(void) {
    int choice = 0;
    int res = 0;
    while (choice != 4) {
        mainMenu();
        do{
            scanf(" %d", &choice);
        } while (choice<=0 && choice>=4);

        if (choice == 1){
            res = startGameMenu();
            if (res == 1)
                match(1);
            else if (res == 2)
                match(2);
        }
        else if (choice == 2)
            rulesMenu();
        else if (choice == 3)
            creditsMenu();
        else if (choice == 4){
            printf("E' stato scelto di uscire");
            exit(0);
        }
        else
            puts("Invalid Input!");
    }
    return;
}
