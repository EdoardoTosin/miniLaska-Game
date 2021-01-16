/*!
   \brief Call the system sleep with closs-platform compatibility.
   @param timeDelay Time of the sleep.
*/
void delayTimer(int timeDelay);
/*!
   \brief Consume every residue from a previous scanf.
*/
void consume(void);
/*!
   \brief Print the main menu when launching the game.
*/
void printMainMenu(void);
/*!
   \brief Print the match mode menu to select beetween PC vs Player or Player vs Player.
   \return Return the number selected (1, 2 or 3).
*/
int startGameMenu(void);
/*!
   \brief Print the rule menu page.
*/
void rulesMenu(void);
/*!
   \brief Print the credits menu page.
*/
void creditsMenu(void);
/*!
   \brief Check the choice selected from the the main menu.
*/
void controlMenu(void);
