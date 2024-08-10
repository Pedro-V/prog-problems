# Lista linkada

A empresa de tecnologia Poxim Tech está
desenvolvendo uma rede social para os melhores
amigos, com a ideia de unir as pessoas como se
estivessem de mãos dadas através de um círculo de
pessoas que interagem com os vizinhos

* Os nomes dos usuários desta rede são compostos
exclusivamente por letras com até 50 caracteres
* Quando um usuário é adicionado ele sempre será
amigo do último e do primeiro usuário da rede social
* Caso seja removido da rede social, os amigos do
usuário passam a ser amigos entre si
* É possível buscar uma determinada pessoa através
do seu nome e mostrar os nomes de seus amigos

## Exemplo de entrada

```markdown
ADD Jose da Silva
SHOW Jose da Silva
ADD Jose da Silva
ADD Joao dos Santos
ADD Maria da Penha
REMOVE Joao dos Santos
REMOVE Maria da Silva
ADD Alan Turing
SHOW Maria da Penha
SHOW Bruno Prado
```

## Exemplo de saída

```markdown
[ OK  ] ADD Jose da Silva
[ OK  ] Jose da Silva<-Jose da Silva->Jose da Silva
[ERROR] ADD Jose da Silva
[ OK  ] ADD Joao dos Santos
[ OK  ] ADD Maria da Penha
[ OK  ] REMOVE Joao dos Santos
[ERROR] REMOVE Maria da Silva
[ OK  ] ADD Alan Turing
[ OK  ] Jose da Silva<-Maria da Penha->Alan Turing
[ERROR] ?<-Bruno Prado->?
```
