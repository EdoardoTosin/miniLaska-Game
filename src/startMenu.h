/*!
   \brief Call the system sleep with closs-platform compatibility.
   @param timeDelay Time of the sleep.
*/
void delayTimer(int timeDelay);
/*!
   \brief Print a message before exiting the program
*/
void printExit();
/*!
   \brief Consume every residue from a previous scanf.
*/
void consume();
/*!
   \brief Print the main menu when launching the game.
*/
void printMainMenu();
/*!
   \brief Print the difficulty mode menu against computer.
   \return Return 0 or the strength of the selected difficulty.
*/
int difficultyMenu ();
/*!
   \brief Print the match mode menu to select beetween Computer vs Player or Player vs Player.
   \return Return a number depending on the selected menu.
*/
int startGameMenu();
/*!
   \brief Print the rule menu page.
*/
void rulesMenu();
/*!
   \brief Print the credits menu page.
*/
void creditsMenu();
/*!
   \brief Check the choice selected from the the main menu.
*/
void controlMenu();
