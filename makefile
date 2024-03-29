src = ./src
matrizes = ./src/matrizes
obj = ./build
out = aplicacao
html = ./doc/html
w = -W -Wall -pedantic
gsl = -lgslcblas -lgsl

all:$(obj) $(out) doc

$(out): $(obj)/matrizes.o $(font)
	@echo -e "\n=== Generanting the file $@... ==="
	gcc $< $(obj)/matrizes.o -I $(obj) -o $(obj)/$@ $(gsl) $(w)
	@echo -e "\n=== To run the code from 'main.c': run the file $(obj)/$@.exe or the rule command 'make teste'!! ==="

	@echo -e "\n=== To run the project webpage: run the file $(html)/index.html or the rule command 'make webpage'!! ==="

$(obj)/main.o:$(src)/main.c  
	@echo -e "\n=== Generating the file $@... ==="
	gcc -c $< -J $(obj) -o $@ $(w)
	
$(obj)/matrizes.o:$(matrizes)/matrizes.c  
	@echo -e "\n=== Generating the file $@... ==="
	gcc -c $< -J $(obj) -o $@ $(gsl) $(w)

$(obj):
	mkdir $(obj)
	
.PHONY: doc
doc: Doxyfile
	@echo -e "\n=== Generating documentation files... ==="
	doxygen Doxyfile

.PHONY: doxy
doxy: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	start "$(html)/index.html"

.PHONY: cyg
cyg: $(html)/index.html
	@echo -e "\n=== Openning the documentation web page... ==="
	cygstart "$(html)/index.html"

<<<<<<< HEAD
teste: $(obj)/$(exec)
	$(obj)/$(exec)


clean:
	@echo -e "\n=== Starting the repository cleaning ==="
	rm -rf $(obj)/*.exe
	rm -rf $(obj)/
	rm -rf $(teste_arq)
	@echo -e "\n=== Cleaning documentation directory ==="
	find doc -type f ! -path "doc/figures/*" ! -path "doc/tema/*" -delete
	find doc -type d -empty -delete