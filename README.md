# *Container Management Tool*

## Autores

- Simão Andrade: 118345

## Objetivos

Consiste na implementação de uma ferramenta de gestão, usando uma CLI (*Command Line Interface*), que permite executar aplicações num ambiente isolado (*container*) empregando *Linux Containers* (LXC), a funcionalidade *chroot*, *namespaces* e *cgroups*.

O uso de *namespaces*, garante que cada *container* tenha a sua própria visão isolada dos recursos do sistema, como PID's, interfaces de rede e montagens do sistema de arquivos.

O uso do *chroot* permite que o LXC altere o diretório raiz de um *container*, limitando o seu acesso a apenas um subconjunto do sistema de arquivos e aumentando a segurança acesso não autorizado a arquivos críticos do sistema. 

Além disso, os *cgroups* desempenham um papel de gestão de recursos, impondo limites à CPU, memória, disco, I/O e largura de banda de rede para cada *container*.

O programa deve ser capaz de:
- [ ] Criar/Remover *containers*;
- [ ] Executar comandos num *container* (e.g. listar ficheiros) e visualizar o output;
- [ ] Copiar ficheiros para dentro de um *container*;
- [ ] Estabelecer uma ligação de rede com o *container*;
- [ ] Executar aplicações num *container*.

Extras:
- [ ] Criação de *logs* de atividade.
- [ ] Dinamicamente alterar os limites de recursos de um *container*;

## Implementação

## Testes e Resultados

## Documentação

A documentação do código foi feita com o *Doxygen*. Para gerar a documentação, basta executar o seguinte comando:

```bash
$ doxygen Doxyfile
```

A documentação será gerada na pasta `docs/`.

## Execução

Primeiramente, é necessário instalar o *LXC*:
```bash	
$ sudo apt-get install lxc
```

Ou, atualizar o *LXC*, caso já esteja instalado:
```bash
$ sudo apt-get update
$ sudo apt-get upgrade lxc
```

Para verificar se o *LXC* foi instalado corretamente, execute o seguinte comando:
```bash
$ lxc-checkconfig
```

Para compilar o programa, basta executar os seguintes comandos:
```bash
$ make
$ ./program
```

## Conclusão

Em suma, bla bla bla...

## Referências

- [LXC (Linux Container)](https://linuxcontainers.org/lxc/documentation/)
- [CGroups](https://www.kernel.org/doc/Documentation/cgroup-v1/cgroups.txt)
- [Chroot](https://man7.org/linux/man-pages/man1/chroot.1.html)