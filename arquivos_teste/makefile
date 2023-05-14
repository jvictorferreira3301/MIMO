#makefile#

all: meucomplexo

meucomplexo: meucomplexo.o meucomplexo_teste.o
		gcc -o meucomplexo meucomplexo.o meucomplexo_teste.o

meucomplexo.o: meucomplexo.c
		gcc -o meucomplexo.o -c meucomplexo.c -W -Wall -ansi -pedantic

meucomplexo_teste: meucomplexo_teste.c meucomplexo.h
		gcc -o meucomplexo_teste.o -c meucomplexo_teste.c -W -Wall -ansi -pedantic

clean:
		rm -rf *.o
mrproper: clean
		rm -rf meucomplexo
