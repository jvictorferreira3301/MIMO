src = ./src
matrizes = ./src/matrizes
obj = ./build
out = aplicacao
w = -W -Wall -pedantic
gsl = -lgslcblas -lgsl
math = -lm
font = ./src/MIMO/pds_telecom.c
teste_arq = Teste_*

all: $(obj) $(out)

$(out): $(obj)/matrizes.o $(font)
	@echo -e "\n=== Generanting the file $@... ==="
	gcc $< -o $(obj)/$@ $(font) $(gsl) $(math) $(w)
	@echo -e "\n=== To run the code from 'pds_telecom.c': run the file $(obj)/$@.exe or the rule command 'make teste'!! ==="

$(obj)/matrizes.o: $(matrizes)/matrizes.c  
	@echo -e "\n=== Generating the file $@... ==="
	gcc -c $< -J $(obj) -o $@ $(gsl) $(w)

$(obj):
	mkdir $(obj)
	
teste: $(obj)/$(out)
	@ $(obj)/$(out)

clean:
	@echo -e "\n=== Starting the repository cleaning ==="
	rm -rf $(obj)/*.exe
	rm -rf $(obj)/
	rm -rf $(teste_arq)

