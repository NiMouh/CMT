# Guião para o video da aplicação

Neste guia é explicado o que é demonstrado no vídeo da aplicação.

## Funcionalidades a mostrar

- [x] Criação/Remoção de *containers*.
- [x] Execução de comandos num *container*.
- [x] Listagem de *containers* em execução.
- [x] Provar isolamento entre o *container* e o *host* a nível de processos.
- [x] Provar isolamento entre o *container* e o *host* a nível de memória.
- [x] Definir/Visualizar recursos dentro do *container*.
- [x] Estabelecer uma conexão com o *container*.
- [x] Copia de um ficheiro para dentro do *container*

## Cronologia

1. Criação de um *container* LXC.
2. Executar o comando `ls -la`, para listar os ficheiros contidos, no *container* LXC.
3. Fazer o comando `ps -a`, para mostrar os processos a correr, no *container* LXC e no *host*.
4. Listar todos os *containers* ativos LXC.
5. Visualizar qual o valor do recursos de memória está a ser utilizado, no *container* LXC.
6. Definir um valor de 8 000 000 (8GB) de memória, para o *container* LXC.
7. Visualizar novamente qual o valor do recursos de memória está a ser utilizado, no *container* LXC.
8. Visualizar o valor visível pelo container através do comandos `free -h`.
9. Criar um ficheiro executável simples no *host* e copiar para o container.
10. Estabalecer uma conexão com o *container*.
11. Executar o ficheiro copiado no *container*.
12. Remover o *container* LXC.
