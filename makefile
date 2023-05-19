src = ./src
matrizes = ./src/matrizes
obj = ./build
exec = aplicacao

all:$(exec)
#teste: ./build/main.o ./build/matrizes.o
#	gcc ./build/main.o ./build/matrizes.o -I ./build -o teste
$(exec):$(obj)/main.o $(matrizes)/matrizes.o
	@echo -e "\nGerando o arquivo executável $@..."
	gcc $< $(obj)/matrizes.o -I $(obj) -o $@.exe -W -Wall -pedantic
	@echo -e "\nPara rodar o codigo 'main.c' execute o arquivo ./$@.exe ou o comando 'make teste'!!"
#./build/objeto.o: ./src/source.c
#	gcc -c objeto.o -J ./build -o ./build/objeto.o
$(obj)/%.o:$(src)/%.c  
	@echo -e "\nGerando o aqruivo objeto $@..."
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic
$(matrizes)/%.o:$(matrizes)/%.c  
	@echo -e "\nGerando o aqruivo objeto $@..."
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic
#run: teste
#	./teste
teste: $(exec).exe
	./$(exec).exe

clean:
	@echo -e "\nRemovendo arquivos '.o'..."
	rm -rf $(obj)/*.o
	rm -rf *.o
allclean:clean
	@echo -e "\nRemovendo arquivos executáveis '.exe'"
	rm -rf *.exe

