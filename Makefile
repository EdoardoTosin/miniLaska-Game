all: miniLaska clean

miniLaska: src/miniLaska.o src/endGame.o src/gameControl.o src/objectCreation.o src/printGame.o src/startGame.o src/printRules.o src/printCredits.o src/startMenu.o
	cc src/miniLaska.o src/endGame.o src/gameControl.o src/objectCreation.o src/printGame.o src/startGame.o src/printRules.o src/printCredits.o src/startMenu.o -o miniLaska

objectCreation.o: src/objectCreation.c src/objectCreation.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm objectCreation.c

printGame.o: printGame.c printGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm printGame.c

endGame.o: src/endGame.c src/endGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm endGame.c

gameControl.o: src/gameControl.c src/gameControl.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm gameControl.c

startGame.o: src/startGame.c src/startGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm startGame.c

printRules.o: src/printRules.c src/printRules.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm printRules.c

printCredits.o: src/printCredits.c src/printCredits.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm printCredits.c

startMenu.o: src/startMenu.c src/startMenu.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm startMenu.c

miniLaska.o: src/miniLaska.c
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm miniLaska.c

.PHONY: clean
clean:
	rm -rf src/*.o
