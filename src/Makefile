all: miniLaska clean

miniLaska: miniLaska.o endGame.o gameControl.o objectCreation.o printGame.o startGame.o readFile.o startMenu.o
	cc miniLaska.o endGame.o gameControl.o objectCreation.o printGame.o startGame.o readFile.o startMenu.o -o miniLaska

objectCreation.o: objectCreation.c objectCreation.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm objectCreation.c

printGame.o: printGame.c printGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm printGame.c

endGame.o: endGame.c endGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm endGame.c

gameControl.o: gameControl.c gameControl.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm gameControl.c

startGame.o: startGame.c startGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm startGame.c

readFile.o: readFile.c readFile.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm readFile.c

startMenu.o: startMenu.c startMenu.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm startMenu.c

miniLaska.o: miniLaska.c
	cc -c -ansi -pedantic -O2 -Wall -Wextra -g -lm miniLaska.c

.PHONY: clean
clean:
	rm -rf *.o
