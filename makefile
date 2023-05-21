src = ./src
matrizes = ./src/matrizes
obj = ./build
exec = aplicacao

all:$(exec) doc

$(exec):$(obj)/main.o $(obj)/matrizes.o
	@echo -e "\n	Gerando o arquivo executável $@..."
	gcc $< $(obj)/matrizes.o -I $(obj) -o $(obj)/$@.exe -W -Wall -pedantic
	@echo -e "\n	Para rodar o codigo 'main.c' execute o arquivo ./$@.exe ou o comando 'make teste'!!"

$(obj)/main.o:$(src)/main.c  
	@echo -e "\n	Gerando o aqruivo objeto $@..."
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic
	
$(obj)/matrizes.o:$(matrizes)/matrizes.c  
	@echo -e "\n	Gerando o aqruivo objeto $@..."
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic

.PHONY: doc
doc: Doxyfile
	@echo -e "\n	Gerando arquivos de documentação do projeto..."
	doxygen Doxyfile
#	@echo -e "\nAbrindo a página HTML da documentação..."
#	doc/html/index.html

teste: $(obj)/$(exec).exe
	$(obj)/$(exec).exe

clean:
	@echo -e "\n	Removendo arquivos '.o'..."
	rm -rf $(obj)/*.o
	@echo -e "\n	Removendo arquivos executáveis '.exe'..."
	rm -rf $(obj)/*.exe
	@echo -e "\nRemovendo arquivos de documentação..."
	find doc -type f ! -path "doc/figures/*" -delete
	find doc -type d -empty -delete