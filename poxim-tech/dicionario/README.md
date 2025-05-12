# Árvore AVL

A empresa de tecnologia Poxim Tech está
desenvolvendo um sistema de dicionário de
sinônimos baseado em árvore AVL.

* As palavras do dicionário e a lista de sinônimos de
cada palavra são compostas exclusivamente por
letras minúsculas com até 30 caracteres
* A listagem de sinônimos para cada palavra possui
capacidade máxima de 10 palavras
* Para demonstrar a eficiência da busca no dicionário
de sinônimos é exibido o percurso realizado na árvore

## Formato do arquivo de entrada

```c
// número de palavras
5
// palavra quant_sinonimos sinonimos
demais 5 bastante numeroso demasiado abundante excessivo
facil 2 simples ed
elegante 3 natural descomplicado trivial
nada 4 zero vazio osso nulo
trabalho 3 atividade tarefa missao
// numero de consultas
3
// consulta
facil
demais
zero
```
## Formato do arquivo de saída

```c
// percurso realizado pela busca
[elegante->nada->facil]
// listagem de sinônimos da palavra pesquisada
simples,ed
[elegante->demais]
bastante,numeroso,demasiado,abundante,excessivo
[elegante->nada->trabalho->?]
-
```
