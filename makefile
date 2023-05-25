src = ./src
matrizes = ./src/matrizes
obj = ./build
exec = aplicacao
html = ./doc/html

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 6b37fb6 (Arquivos)
=======
>>>>>>> f658f04e0ad30aace32c73d6749c5e4dbde399da
all:$(obj) $(exec) doc

$(exec):$(obj)/main.o $(obj)/matrizes.o
	@echo -e "\n=== Generanting the file $@... ==="
	gcc $< $(obj)/matrizes.o -I $(obj) -o $(obj)/$@.exe -W -Wall -pedantic
	@echo -e "\n=== To run the code from 'main.c': run the file $(obj)/$@.exe or the rule command 'make teste'!! ==="
	@echo -e "\n=== To run the project webpage: run the file $(html)/index.html or the rule command 'make webpage'!! ==="
$(obj)/main.o:$(src)/main.c  
	@echo -e "\n=== Generating the file $@... ==="
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic
	
$(obj)/matrizes.o:$(matrizes)/matrizes.c  
	@echo -e "\n=== Generating the file $@... ==="
<<<<<<< HEAD
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic

$(obj):
	mkdir $(obj)
	
.PHONY: doc
doc: Doxyfile
	@echo -e "\n=== Generating documentation files... ==="
	doxygen Doxyfile

.PHONY: webpage
webpage: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	start "$(html)/index.html"

.PHONY: cyg
cyg: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	cygstart "$(html)/index.html"
=======
all:$(exec) doc

$(exec):$(obj)/main.o $(obj)/matrizes.o
	@echo -e "\n=== Gerando o arquivo executável $@... ==="
	gcc $< $(obj)/matrizes.o -I $(obj) -o $(obj)/$@.exe -W -Wall -pedantic
	@echo -e "\n=== Para rodar o codigo 'main.c' execute o arquivo $(obj)/$@.exe ou o comando 'make teste' ===!!"

$(obj)/main.o:$(src)/main.c  
	@echo -e "\n=== Gerando o aqruivo objeto $@... ==="
=======
>>>>>>> f658f04e0ad30aace32c73d6749c5e4dbde399da
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic

$(obj):
	mkdir $(obj)
	
<<<<<<< HEAD
$(obj)/matrizes.o:$(matrizes)/matrizes.c  
	@echo -e "\n=== Gerando o aqruivo objeto $@... ==="
	gcc -c $< -J $(obj) -o $@ -W -Wall -pedantic

.PHONY: doc
doc: Doxyfile
	@echo -e "\n=== Gerando arquivos de documentação do projeto... ==="
	doxygen Doxyfile
<<<<<<< HEAD
#	@echo -e "\nAbrindo a página HTML da documentação..."
#	doc/html/index.html
>>>>>>> 1fd4aab (Makefile: implementação da regra 'doc', realocação da pasta 'figures' e atualização da regra 'clean')
=======

.PHONY: site
site: $(html)/index.html
	@echo -e "\n=== Abrindo a página de documentação do projeto... ==="
	start ./doc/html/index.html
>>>>>>> 3ce9845 (Doxyfile: ajuste após realocação da pasta 'figures'| Makefile: regra 'site')

.PHONY: cyg
cyg: $(html)/index.html
	@echo -e "\n=== Abrindo a página de documentação do projeto... ==="
	cygstart doc/html/index.html
=======
.PHONY: doc
doc: Doxyfile
	@echo -e "\n=== Generating documentation files... ==="
	doxygen Doxyfile

.PHONY: webpage
webpage: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	start "$(html)/index.html"

.PHONY: cyg
cyg: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	cygstart "$(html)/index.html"
>>>>>>> f658f04e0ad30aace32c73d6749c5e4dbde399da

teste: $(obj)/$(exec).exe
	$(obj)/$(exec).exe

clean:
<<<<<<< HEAD
<<<<<<< HEAD
	@echo -e "\n=== Starting the repository cleaning ==="
<<<<<<< HEAD
=======
	@echo -e "\n=== Removing files '.o' ==="
	rm -rf $(obj)/
>>>>>>> 6b37fb6 (Arquivos)
=======
	@echo -e "\n=== Starting the repository cleaning ==="
>>>>>>> f658f04e0ad30aace32c73d6749c5e4dbde399da
	@echo -e "\n=== Removing files '.exe' ==="
	rm -rf $(obj)/*.exe
	@echo -e "\n=== Removing files '.o' ==="
	rm -rf $(obj)/
	@echo -e "\n=== Cleaning documentation directory ==="
<<<<<<< HEAD
<<<<<<< HEAD
	find doc -type f ! -path "doc/figures/*" ! -path "doc/tema/*" -delete
	find doc -type d -empty -delete
=======
	@echo -e "\n	Removendo arquivos '.o'..."
	rm -rf $(obj)/*.o
	@echo -e "\n	Removendo arquivos executáveis '.exe'..."
	rm -rf $(obj)/*.exe
	@echo -e "\nRemovendo arquivos de documentação..."
	find doc -type f ! -path "doc/figures/*" -delete
	find doc -type d -empty -delete
>>>>>>> 1fd4aab (Makefile: implementação da regra 'doc', realocação da pasta 'figures' e atualização da regra 'clean')
=======
#	find doc -type f ! -path "doc/figures/*" -delete
#	find doc -type d -empty -delete
	rm -rf doc/html
	rm -rf doc/latex
>>>>>>> 74f59a5 (Arquivos: cópia de arquivos de 'documentação')
=======
	find doc -type f ! -path "doc/figures/*" ! -path "doc/tema/*" -delete
	find doc -type d -empty -delete
>>>>>>> f658f04e0ad30aace32c73d6749c5e4dbde399da
