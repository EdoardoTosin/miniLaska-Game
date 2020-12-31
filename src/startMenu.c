#include "startMenu.h"

#include <stdio.h>
#include <stdlib.h>

void print_menu(){
  puts("\n\n\n");
  puts("/====================/");
  puts("       MAIN MENU      ");
  puts("/====================/");
  puts("1. Player vs Player");
  puts("2. PC vs Player");
  puts("3. PC vs Player");
  puts("4. Exit");
  printf(">>");
  return;
}

void print_submenu1(){
  puts("E' stato scelto il submenu 1");
  int sub_choice1 = 0;
  while (sub_choice1 != 2) {
    puts("/====================/");
    puts("          MENU   1    ");
    puts("/====================/");
    puts("1. Submenu 1");
    puts("2. Exit");
    printf(">>>");
    scanf("%d", &sub_choice1);
    if (sub_choice1 == 1) {
      puts("E' stato scelto il subsubmenu 1");
    } else if (sub_choice1 == 2) {
      puts("E' stato scelto di uscire");
    } else {
      puts("Invalid Input");
    }
  }
  return;
}

void print_submenu2(){
  puts("E' stato scelto il submenu 2");
  int sub_choice2 = 0;
  while (sub_choice2 != 2) {
    puts("/====================/");
    puts("           MENU  2    ");
    puts("/====================/");
    puts("1. Submenu 1");
    puts("2. Exit");
    printf(">>>");
    scanf("%d", &sub_choice2);
    if (sub_choice2 == 1) {
      puts("E' stato scelto il subsubmenu 1");
    } else if (sub_choice2 == 2) {
      puts("E' stato scelto di uscire");
    } else {
      puts("Invalid Input");
    }
  }
  return;
}

void print_submenu2(){
  puts("E' stato scelto il submenu 3");
  int sub_choice3 = 0;
  while (sub_choice3 != 2) {
    puts("/====================/");
    puts("           MENU  3    ");
    puts("/====================/");
    puts("1. Submenu 1");
    puts("2. Exit");
    printf(">>>");
    scanf("%d", &sub_choice3);
    if (sub_choice3 == 1) {
      puts("E' stato scelto il subsubmenu 1");
    } else if (sub_choice3 == 2) {
      puts("E' stato scelto di uscire");
    } else {
      puts("Invalid Input");
    }
  }
  return;
}

int startMenu() {
  system(CLEAR);
  int choice = 0;
  while (choice != 4) {
    print_menu();
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        print_submenu1();
        break;
      case 2:
        print_submenu2();
        break;
      case 3:
        print_submenu3();
        break;
      case 4:
        printf("E' stato scelto di uscire");
        break;
      default:
        puts("Invalid Input!");
      }
  }
  return 0;
}
