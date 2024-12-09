from collections import defaultdict
from functools import partial

COMUM = 0
TIPICO = 1
NAO_DEFINIDO = 2

def eh_tipico(tabela_porcoes: dict, tipicos: set, porcao: str) -> bool:
    if porcao in tipicos:
        return True
    if porcao not in tabela_porcoes:
        return False

    tipo, componentes = tabela_porcoes[porcao]
    if tipo == COMUM:
        return False
    if tipo == TIPICO:
        return True

    num_tipicos = sum(map(partial(eh_tipico, tabela_porcoes, tipicos), componentes))
    if num_tipicos * 2 > len(componentes):
        tabela_porcoes[porcao] = (TIPICO, componentes)
        return True
    else:
        tabela_porcoes[porcao] = (COMUM, componentes)
        return False


def preenche_porcoes(tabela_porcoes):
    num_porcoes = int(input())
    for _ in range(num_porcoes):
        porcao, _ = input().split()
        componentes = input().split()
        if type(componentes) == str:
            componentes = list(componentes)
        tabela_porcoes[porcao] = (NAO_DEFINIDO, componentes)

def main():
    # Hash table de porções para seus tipos e sub-componentes.
    tabela_porcoes = {}

    input()
    tipicos = set(input().split())
    preenche_porcoes(tabela_porcoes)

    for porcao in tabela_porcoes:
        if eh_tipico(tabela_porcoes, tipicos, porcao):
            print('porcao tipica')
        else:
            print('porcao comum')

if __name__ == '__main__':
    main()
