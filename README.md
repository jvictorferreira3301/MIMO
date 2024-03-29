Link do site com a documentação feita pelo doxygen: https://jvictorferreira3301.github.io/MIMO/

# Projeto de Engenharia II - Implementação de Sistema de Comunicação Digital MIMO

Projeto feito para a disciplina de Projeto de Engenharia II ministrada no segundo semestre na Faculdade de Computação e Telecomunicações da Universidade Federal do Pará. O objetivo deste projeto é desenvolver uma biblioteca em C contendo funções que implementam operações matriciais. A biblioteca resultante será utilizada para implementar um sistema de Comunicação Digital MIMO (Multiple-in, Multiple-out) em Linguagem C. O sistema a ser implementado é o descrito na imagem abaixo:

<img src="Doxyfiles/figures/mimosystem.png" alt="mimo-implementação">

### 🚀 Etapas de desenvolvimento

Ao longo da disciplina foram propostas as seguintes tarefas:

- [x] Tarefa 1 - Criação e configuração de conta e envio de contribuições no código (Tutorial Github).
- [x] Tarefa 2 - Implementação de funções para álgebra matricial e operações com matrizes.	
- [x] Tarefa 3 - Documentação do código com comentários e doxygen e automação com makefile.
- [x] Tarefa 4 - Integração de cálculo de SVD na biblioteca matrizes a partir de biblioteca externa.
- [x] Tarefa 5 - Implementação de Sistema de Comunicação Digital MIMO

### 💻 Pré-requisitos

- Biblioteca GSL (`gsl/gsl_linalg.h`): A Biblioteca Científica GNU (GSL) é uma biblioteca numérica para C e C++. Neste caso, está sendo usada a parte de álgebra linear.

- Makefile: utilitário que automatiza o processo de compilação de programas, gerenciando dependências entre arquivos fonte. 

## Guia para o Makefile
O Makefile neste projeto é usado para automatizar o processo de construção do projeto em C. Aqui está um guia de como usá-lo:

### Variáveis

O Makefile configura algumas variáveis para diretórios e flags usadas no processo de compilação:

- `src`: O diretório contendo os arquivos de origem.
- `matrizes`: O diretório contendo os arquivos de matrizes.
- `obj`: O diretório onde os arquivos de objeto e o executável serão armazenados.
- `out`: O nome do arquivo executável.
- `w`: Flags de aviso para o compilador gcc.
- `gsl`: Flags para linkar a biblioteca GSL (GNU Scientific Library).
- `math`: Flag para linkar a biblioteca matemática.
- `font`: O arquivo de origem principal do projeto.
- `teste_arq`: Padrão de nome de arquivo para arquivos de teste.

### Comandos

- `all`: Este é o comando padrão. Ele cria o diretório `obj` (se não existir) e compila o projeto.
- `$(out)`: Este comando compila o arquivo de origem principal e linka com a biblioteca GSL e a biblioteca matemática.
- `$(obj)/matrizes.o`: Este comando compila o arquivo de matrizes e gera um arquivo de objeto.
- `$(obj)`: Este comando cria o diretório `obj` se ele não existir.
- `teste`: Este comando executa o arquivo executável.
- `clean`: Este comando limpa o diretório `obj` e remove todos os arquivos de teste.

Para usar o Makefile, você pode digitar `make <comando>` no terminal, substituindo `<comando>` pelo comando que você deseja executar. Por exemplo, `make all` para compilar o projeto, ou `make clean` para limpar o diretório de construção.
  
### Estrutura do diretório
O Makefile assume a seguinte estrutura de diretórios:

- src: Diretório principal que contém os arquivos de origem do código fonte.
- matrizes: Subdiretório dentro de src que contém os arquivos relacionados às operações matriciais.
- MIMO: Subdiretório dentro de src que contém os arquivos relacionados ao código pds_telecom.c que implementa o sistema de comunicação MIMO
- build: Diretório onde os arquivos de objeto e executáveis serão gerados.

