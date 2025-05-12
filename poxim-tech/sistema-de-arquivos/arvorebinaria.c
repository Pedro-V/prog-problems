#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct no {
    char nome[51], permissao[3];
    uint32_t tamanho;
    uint32_t posicao_ordem;
    struct no* D;
    struct no* E;
} no;

FILE* input = 0;
FILE* output = 0;

uint32_t quant_nos = 1;
no* raiz = 0;

// função para printar de maneira formatada as informações do nó
void print_no_info(no* node){
    if(node->tamanho == 1)
        fprintf(output, "%d %s %s %d byte\n", node->posicao_ordem, node->nome, node->permissao, node->tamanho);
    else
        fprintf(output, "%d %s %s %d bytes\n", node->posicao_ordem, node->nome, node->permissao, node->tamanho);

    return;
}


void modifica_no(no* node_original, no* node_novo){
    if(strcmp(node_original->permissao, "rw") == 0){
        strcpy(node_original->permissao, node_novo->permissao);
        node_original->tamanho = node_novo->tamanho;
        node_original->posicao_ordem = node_novo->posicao_ordem;
    }
    return;
}

void insert_arvore(no* node_cabeca, no* novo_node){
    // se forem iguais, iremos tentar realizar a operação de modificação
    if(strcmp(novo_node->nome, node_cabeca->nome) == 0)
        modifica_no(node_cabeca, novo_node);
    // se o novo node for menor, iremos à esquerda do node_cabeca
    else if(strcmp(novo_node->nome, node_cabeca->nome) < 0){
        if(!node_cabeca->E)
            node_cabeca->E = novo_node;
        else
            insert_arvore(node_cabeca->E, novo_node);
    }
    // se o novo node for maior, iremos à direita do node_cabeca
    else{
        if(!node_cabeca->D)
            node_cabeca->D = novo_node;
        else
            insert_arvore(node_cabeca->D, novo_node);
    }
    
    return;
}


void em_ordem(no* P){
    if(!P){
        return;
    }
    em_ordem(P->E);
    print_no_info(P);
    em_ordem(P->D);
}

void pre_ordem(no* P){
    if(!P){
        return;
    }
    print_no_info(P);
    pre_ordem(P->E);
    pre_ordem(P->D);
}

void pos_ordem(no* P){
    if(!P){
        return;
    }
    pos_ordem(P->E);
    pos_ordem(P->D);
    print_no_info(P);
}

int main(int argc, char** argv){
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if(!input){
        fprintf(stdout, "Não foi possível abrir o arquivo de input\n");
        exit(EXIT_FAILURE);
    }

    char* linha_atual = 0;
    size_t len = 0;
    uint32_t quant_entradas, i = 1;
    fscanf(input, "%d\n", &quant_entradas);
    
    // RAIZ DA ARVORE
    raiz = malloc(sizeof(no));
    getline(&linha_atual, &len, input);
    linha_atual[strlen(linha_atual) - 1] = '\0';
    sscanf(linha_atual, "%s %s %d", raiz->nome,
                raiz->permissao, &(raiz->tamanho));
    raiz->posicao_ordem = 0;

    // PREENCHIMENTO DA ARVORE
    while(i < quant_entradas){
        getline(&linha_atual, &len, input);
        no* atual = malloc(sizeof(no));
        linha_atual[strlen(linha_atual) - 1] = '\0';
        sscanf(linha_atual, "%s %s %d", atual->nome,
                atual->permissao, &(atual->tamanho));
        atual->posicao_ordem = i;
        insert_arvore(raiz, atual);
        i++;
    }

    fclose(input);

    fprintf(output, "EPD:\n");
    em_ordem(raiz);
    fprintf(output, "PED:\n");
    pre_ordem(raiz);
    fprintf(output, "EDP:\n");
    pos_ordem(raiz);

    fclose(output);
}