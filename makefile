src = ./src
matrizes = ./src/matrizes
obj = ./build
exec = aplicacao
html = ./doc/html

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

teste: $(obj)/$(exec).exe
	$(obj)/$(exec).exe

clean:
	@echo -e "\n=== Starting the repository cleaning ==="
	@echo -e "\n=== Removing files '.o' ==="
	rm -rf $(obj)/
	@echo -e "\n=== Removing files '.exe' ==="
	rm -rf $(obj)/*.exe
	@echo -e "\n=== Cleaning documentation directory ==="
	find doc -type f ! -path "doc/figures/*" -delete
	find doc -type d -empty -delete