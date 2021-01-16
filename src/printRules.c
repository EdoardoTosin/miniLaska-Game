#include <stdio.h>

void printRules(void) {
  puts("The major difference between Lasca and other draughts variants is that instead of pieces being");
  puts("removed from the board when they are jumped, they are placed under the piece that jumped them,");
  puts("forming a column. A column is under the control of the player whose piece is on top, and has the");
  puts("move and jump capabilities of that piece (so that, for instance, a column with a black officer on");
  puts("top is under Black's control, and can move and jump in either direction.) If a column is itself");
  puts("jumped, only the top piece is removed to go under the column doing the jumping.");
  puts("");
  puts("There are a few other changes in the rules, as well. Capturing is mandatory when possible; this");
  puts("means that a clever player may be able to force his opponent to capture several pieces of his");
  puts("color, then capture his opponent's piece from the top, leaving a powerful column composed of");
  puts("several pieces of his own color. A player wins the game when:");
  puts("");
  puts("- the opponent has no legal move, or");
  puts("- all the opponent's pieces have been captured, or");
  puts("- the opponent resigns.");
  printf("\n");
}
