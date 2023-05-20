all:teste 

teste:main.o matrizes.o
	gcc -o main main.o matrizes.o
	@echo "Para rodar o codigo main.c execute o ./main.exe"
main.o:main.c
	gcc -o main.o -c main.c -W -Wall -pedantic
	
matrizes.o:matrizes.c
	gcc -o matrizes.o -c matrizes.c -W -Wall -pedantic
	
clean:
	rm -rf *.o
mrproper:clean
	rm -rf *.exe