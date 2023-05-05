#makefile#

all: teste

meucomplexo: meucomplexo.o meucomplexo_teste.0
		gcc -o meucomplexo meuxomplexo.o meucomplexo_teste.o

meucomplexo.o: meucomplexo.c
		gcc -o meucomplexo.o -c teste.c -W -Wall -ansi -pedantic

meucomplexo_teste: meucomplexo_teste.c meucomplexo.h
		gcc -o meucomplexo_teste.o -c meucomplexo_teste.c -W -Wall -ansi -pedantic

clean:
		rm -rf *.o
mrproper: clean
		rm -rf meucomplexo
