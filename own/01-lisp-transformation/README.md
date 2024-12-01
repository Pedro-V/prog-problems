# Lisp Transformation

![Trying to save a princess with Lisp](https://images.uncyc.org/pt/d/d7/Lisp-salvando-princesa.png)

A sintaxe de LISP segue uma ideia bastante simples: cada par de parênteses representa
uma chamada de função: a primeira “palavra” dentro dos parênteses é a função sendo
chamada, e as demais são os argumentos:

```lisp
( foo bar baz 123 )
```

Corresponde a chamar a função “foo” com argumentos “bar”, “baz” e 123, por exemplo. Na
maneira "convencional" a expressão anterior seria equivalente a:

```
foo(bar, baz, 123)
```

Você não gosta de Lisp, e por isso resolveu criar um conversor de Lisp para o formato
convencional com os parênteses do lado certo!

Sua tarefa é: Dado N programas em Lisp (com sintaxe simplificada), reescrevê-los na forma
sintática revisada, mais familiar aos programadores do século XXI. Claro, você deve
também validar que cada programa de entrada é sintaticamente válido (isto é, possui parênteses balanceados).

Cada programa será escrito numa linha.

## Exemplos

### Exemplo 1

Entrada: 
```
2
( ( foo ) bar ) )
( ( foo bar ) baz 123 )
```

Saída:
```
syntax error
foo(bar)(baz, 123)
```
