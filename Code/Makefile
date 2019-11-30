all: Final Test Clear

Final: fonctions.o main.o
	gcc -lm -Wall -g -std=c99 fonctions.o main.o -o Final

Test: fonctions.o tests.o
	gcc -lm -Wall -g -std=c99 fonctions.o tests.o -o Test

Clear:
	rm *.o

fonctions.o: fonctions.c header.h
	gcc -lm -Wall -g -std=c99 -c fonctions.c -o fonctions.o

main.o: main.c header.h
	gcc -lm -Wall -g -std=c99 -c main.c -o main.o

purge:
	rm -rf Final Test
