# Banco de Dados Distribuído

A empresa de tecnologia Poxim Tech está desenvolvendo um banco de dados distribuído para
arquivos baseado em blockchain e árvore B.
* Os arquivos possuem nomes + extensão com até 30 caracteres, compostos exclusivamente por letras
* A codificação do código hash é feita em hexadecimal de 128 bits com caracteres maiúsculos,
  sendo utilizado como chave para buscas
* Operações disponíveis:
  * INSERT nome tamanho hash
  * SELECT hash

## Formato do arquivo de entrada 

```c
// ordem da árvore
3
// quantidade de arquivos
5
// nome, tamanho e hash
f.b 1 00000000000000000000000000000000
f.c 2 00000000000000000000000000000001
f.d 3 00000000000000000000000000000002
f.e 4 00000000000000000000000000000003
f.f 5 00000000000000000000000000000004
// número de operações
3
// operação
INSERT f.a 0 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
SELECT 00000000000000000000000000000004
SELECT 123456789ABCDEF0123456789ABCDEF0
```

## Formato do arquivo de saída

```
// conteúdo armazenado pelo nó da arvore
[00000000000000000000000000000004]
f.f:size=5,hash=00000000000000000000000000000004
f.a:size=0,hash=FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
[123456789ABCDEF0123456789ABCDEF0]
-
```
