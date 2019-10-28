all: Final Test Clear

Final: fonctions.o master_pointer.o main.o
	gcc -lm -Wall -g -std=c99 fonctions.o master_pointer.o main.o -o Final

Test: fonctions.o master_pointer.o tests.o
	gcc -lm -Wall -g -std=c99 fonctions.o master_pointer.o tests.o -o Test

Clear:
	rm *.o

fonctions.o: fonctions.c header.h
	gcc -lm -Wall -g -std=c99 -c fonctions.c -o fonctions.o

master_pointer.o: master_pointer.c header.h
	gcc -lm -Wall -g -std=c99 -c master_pointer.c -o master_pointer.o

main.o: main.c header.h
	gcc -lm -Wall -g -std=c99 -c main.c -o main.o

purge:
	rm -rf Final Test
