miniLaska: miniLaska.o endGame.o gameControl.o objectCreation.o printGame.o startGame.o startMenu.o
	cc miniLaska.o endGame.o gameControl.o objectCreation.o printGame.o startGame.o startMenu.o -o miniLaska

objectCreation.o: objectCreation.c objectCreation.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm objectCreation.c

printGame.o: printGame.c printGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm printGame.c

endGame.o: endGame.c endGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm endGame.c

gameControl.o: gameControl.c gameControl.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm gameControl.c

startGame.o: startGame.c startGame.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm startGame.c

startMenu.o: startMenu.c startMenu.h
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm startMenu.c

miniLaska.o: miniLaska.c
	cc -c -ansi -pedantic -O2 -Wall -Wextra -lm miniLaska.c

clean:
	rm *.o
