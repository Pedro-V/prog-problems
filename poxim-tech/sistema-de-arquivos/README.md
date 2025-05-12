# Árvore Binária de Busca

A empresa de tecnologia Poxim Tech está
desenvolvendo um sistema de armazenamento de
arquivos baseado em árvore binária de busca
* O formato de nome dos arquivos é definido por uma
cadeia com 1 até 50 caracteres, composta somente
por letras, números e os símbolos `_`  e `.`
* Cada arquivo possui também informações de
permissão de acesso para somente leitura (`ro`) e
escrita e leitura (`rw`), além do tamanho em bytes
* Caso um nome de arquivo repetido seja inserido, é
feita a substituição das informações desde que o
arquivo permita a escrita (`rw`)

## Formato do arquivo de entrada

```c
// número de arquivos
6
// nome tipo tamanho
lista_ed.c rw 1123
senhas.txt rw 144
foto.jpg rw 8374719
documento.doc rw 64732
lista_ed.c ro 1
senhas.txt ro 130
```

## Formato do arquivo de saída

```c
// percurso em ordem
EPD:
3 documento.doc rw 64732 bytes
2 foto.jpg rw 8374719 bytes
4 lista_ed.c ro 1 byte
5 senhas.txt ro 13 bytes
// percurso pré-ordem 
PED:
4 lista_ed.c ro 1 byte
2 foto.jpg rw 8374719 bytes
3 documento.doc rw 64732 bytes
5 senhas.txt ro 13 bytes
// percurso pós-ordem
EDP:
3 documento.doc rw 64732 bytes
2 foto.jpg rw 8374719 bytes
5 senhas.txt ro 13 bytes
4 lista_ed.c ro 1 byte
```