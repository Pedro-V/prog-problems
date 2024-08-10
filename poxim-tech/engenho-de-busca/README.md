# Hash

A empresa de tecnologia Poxim Tech está criando
um engenho de busca experimental para retornar
ocorrências de texto em uma interface web

* De acordo com o valor de chave gerado pelo texto é
feito o mapeamento da requisição de busca para um
dos servidores dedicados, utilizando um cálculo de
checksum com 8 bits para cada um dos caracteres
* Para atender as solicitações em tempo real, cada um
dos servidores só é capaz de atender um número
máximo de requisições ao mesmo tempo, sendo feita
uma realocação do servidor por double hashing
definida por $H_1(x) = 7919 × checksum(x) \mod T$
$H_2(x) = 104729 × checksum(x) + 123 \mod T$,
onde $T$ representa o número de servidores
* Função de double hash: $H(x, i) = H_1(x) + i×H_2(x)$
* Todos os padrões pesquisados são compostos
somente por letras e números com até 100 caracteres

## Função de checksum com 8 bits

Realiza a operação de ou-exclusivo ou xor ($⊕$) com os
valores numéricos ASCII dos caracteres
```c
checksum("ufs") = 'u' ^ 'f' ^ 's';
```
Probabilidade de duas strings diferentes gerarem o
mesmo valor numérico é de $1/2^8 ≈ 0,4\%$

## Formato do arquivo de entrada

```c
// número de servidores e capacidade máxima de cada um
3 2
// quantidade de padrões e string
1 ufs
3 a b c
2 cd ef
2 e d
1 hash
```

## Formato do arquivo de saída

```c
// servidor alocado e palavras já alocadas naquele servidor
[S0] ufs
[S0] ufs, a b c
[S2] cd ef
[S2] cd ef, e d
// Ocorre o double hash aqui
S0 -> S1
[S1] hash
```
