all:teste

teste:main.o matrizes.o
	gcc -o teste main.o matrizes.o
main.o:main.c
	gcc -o main.o -c main.c -W -Wall -pedantic
matrizes.o:matrizes.c
	gcc -o matrizes.o -c matrizes.c -W -Wall -pedantic