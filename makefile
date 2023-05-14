all:teste

teste:main.o matrizes.o
	@echo "Gerando o arquivo executável 'teste.exe'..."
	gcc -o teste ./build/main.o ./build/matrizes.o -W -Wall -pedantic
	@echo "Para rodar o codigo 'main.c' execute o arquivo ./main.exe!!"

main.o:./src/main.c
	@echo "Gerando o arquivo 'main.o'..."
	gcc -o ./build/main.o -c ./src/main.c -W -Wall -pedantic

matrizes.o:./src/matrizes.c
	@echo "Gerando o aqruivo 'matrizes.o...'"
	gcc -o ./build/matrizes.o -c ./src/matrizes.c -W -Wall -pedantic
	
clean:
	@echo "Removendo arquivos '.o'..."
	rm -rf ./build/*.o
mrproper:clean
	@echo "Removendo arquivos executáveis '.exe'"
	rm -rf *.exe

