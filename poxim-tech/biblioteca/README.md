# Busca Binária e interpolada

A empresa de tecnologia Poxim Tech está realizando
um estudo comparativo entre a busca binária e
interpolada para um sistema de biblioteca, para
determinar qual das abordagens é mais eficiente

* Os livros são identificados unicamente pelo
International Standard Book Number (ISBN) que é
composto de 13 dígitos numéricos
* Para realização de consulta dos livros é utilizado o
ISBN, contabilizando o número total de chamadas
realizadas para realização da busca binária e
interpolada e retornando o nome do autor (até 50
caracteres) e do título do livro (até 100 caracteres)
* A busca interpolada é feita da função de heurística $h(i, j) = \lfloor (i + ISBN_j − ISBN_i) \mod (j − i + 1) \rfloor$ para determinar o provável índice do livro procurado
* Para cada consulta realizada é exibida a quantidade
de chamadas realizadas pela busca binária e
interpolada, com informações sobre o livro
* Após a realização das consultas é exibido a
quantidade de vitórias e a média truncada de
chamadas de cada algoritmo, onde em caso de
empate a busca interpolada é vencedora

## Exemplo de entrada
```c
5
9780130224187 Niklaus Wirth&Algorithms + Data Structures = Programs
9780201416077 Gaston Gonnet&Handbook of Algorithms and Data Structures
9780262033848 Thomas Cormen&Introduction to Algorithms
9780321751041 Donald Knuth&The Art of Computer Programming
9781584884354 Dinesh Mehta&Handbook of Data Structures and Applications
3
9780130224187
9781584884354
1234567890123
```

## Exemplo de saída
```c
[9780130224187]B=2,I=2:Author:Niklaus Wirth,Title:Algorithms + Data Structures = Programs
[9781584884354]B=3,I=2:Author:Dinesh Mehta,Title:Handbook of Data Structures and Applications
[1234567890123]B=3,I=2:ISBN_NOT_FOUND
BINARY=0:2
INTERPOLATION=3:2
```
