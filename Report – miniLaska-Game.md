# Report – miniLaska-Game

**by Singh Baljinder & Edoardo Tosin**

## Introduction

In this project, a variant of the game Lasca (or Laska) has been developed, where the only difference is that the maximum height of the towers is three tokens. The game code is written in standard ANSI C.

## Development

During the development of the project, we ran into several problems, which were progressively solved.

To simplify code sharing, we opted to create a private repository on the well-known website GitHub.

Next, we chose the type of data structure to use to create the board and checkers.

To adhere to the Ansi C standard (-ansi) we decided to insert additional flags (-pedantic -O2 -Wall -Wextra -g -lm) to keep the code cleaner as it was written and tested.

The Linux debugger "gdb" allowed us to solve a segmentation fault in the terminal print of the chessboard after a change in the definition of a struct.

The first step was to create a version of the code where two players could play with each other via a terminal interface. This allowed us to better understand the dynamics of the game and then insert an algorithm for computer versus player mode.

For the computer vs. player mode, we decided to use the minimax algorithm. This has allowed an integration not too difficult even if it has increased the complexity of the code. This is because the algorithm is recursive.

The next step was to split the code into several files to make it more manageable, especially after the inclusion of the algorithm for anti-computer mode.

To maintain cross-platform compatibility between Windows, Linux, and Mac of the entire code, we chose to stay in the terminal for the program interface. This led us to look for a solution to two problems: cleaning up the terminal interface and the sleep function; both of which were solved by inserting a control into the pre-processor.

When we arrived at a working code that allowed to play without any problem then we tried to create the documentation using Doxygen and insert the comments.

As a last implementation we inserted three levels of difficulty to choose when you want to start a game against the computer.

## Structure

Inside the src folder you will find the following source code files:

  - definitions.h: Definition of macros and Windows/POSIX compatibility

  - gameControl.c: Game control functions

  - gameControl.h: Declaration of the functions present in gameControl.c

  - miniLaska.c: Contains the main function that launches the main menu

  - objectCreation.c: Functions of creation of the board and token at the beginning of the game

  - objectCreation.h: Declaration of the functions present in ojectCreation.c

  - printCredits.c: Print on screen the text of the credits of the game

  - printCredits.h: Declaration of the function present in rintCredits.c

  - printGame.c: Print on screen the chessboard and the moves

  - printGame.h: Declaration of the functions present in printGame.c

  - printRules.c: Print on screen the text of the rules of the game

  - printRules.h: Declaration of the function present in printRules.c

  - startGame.c: Function to control the players turns

  - startGame.h: Declaration of the function present in startGame.c

  - startMenu.c: Print the choice menus

  - startMenu.h: Declaration of functions present in startMenu.c

  - struct.h: Declaration of scructs

## ADT description

Struct Piece represents the information related to every single token and is composed:

  - int team (variable containing the team to which the token belongs, which can be 0 in case of empty cell otherwise 1 or 2)

  - char p (used to define the symbol of the team, with an upgrade it could also be used to insert a custom symbol for your team at the beginning of the game)

  - int rank (represents the rank of the pawn i, 0 for empty cell, 1 for soldier, 2 for officer)

PiecePtr represents the set of pawns inside a cell.

Struct Cell is composed of:

  - int height -\> represents the current height inside the cell (this variable takes up to 4 different values during the game: 0 for empty cell, 1 for the presence of one token, 2 for the presence of two tokens and finally 3 for the presence of 3 tokens).

  - PiecePtr piece (the array containing the tokens of each cell)

Our board is represented by a double pointer struct Cell \*\*.

When the board is initialized, all values are set to 0, then we call another function, which allows us to prepare the board for the game, which allows us to insert the checkers.

## Minimax algorithm

Minimax is one of the most famous and used algorithms for artificial intelligence, decision theory, game theory, statistics. When dealing with earnings, it is referred to as maximin, to maximize minimum earnings. Originally formulated for zero-sum game theory for n players, covering both cases in which players take alternate moves and those in which they make simultaneous moves, it has been extended to more complex games and general decision making in the presence of uncertainty.

In our case minimax is a function present in the gameControl.c file and allows us to assign a score to each move of the pc (1 for hit, 0 for normal move, INT MAX for win) and for those of the player (-1 for hit, 0 for normal move, INT MIN for win).

It is recursive, i.e., it calls itself simulating the next moves.

It is recalled inside findBestMove, a function present in the same file, which allows the PC to execute the best move.

## Game interaction

To interact with the game, just use the numbers and the Enter key to confirm your input.

![](https://raw.githubusercontent.com/EdoardoTosin/miniLaska-Game/main/example/example.jpg)

## Possible future improvements

Ever since the recursive function of the minimax algorithm was added, we were aware that performance depended on the depth to which we wanted to make the move control go. To solve this problem it was thought to exploit the pthread function in POSIX systems, but for reasons of insufficient time we preferred to leave it as a future addition.

Another possible improvement is to insert the minimax algorithm to suggest the best moves to the player.
