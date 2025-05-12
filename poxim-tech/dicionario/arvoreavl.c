#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef struct no{
    char palavra[31];
    int32_t quant_sinonimos;
    char* sinonimos;
    uint8_t nivel_max_esq, nivel_max_dir;
    struct no* D;
    struct no* E;
} no;

uint8_t max(uint8_t nivel1, uint8_t nivel2){
    return nivel1 > nivel2 ? nivel1 : nivel2;
}

void rotacao_E ( no** raiz ) {
    no * eixo = (*raiz)->D ;
    (*raiz)->D = eixo->E;
    eixo->E = (*raiz);
    *raiz = eixo ;
}

void rotacao_D ( no** raiz ) {
    no * eixo = (*raiz)->E;
    (*raiz)->E = eixo->D;
    eixo->D = (*raiz);
    *raiz = eixo;
}

void rotacao_E_D ( no** raiz ) {
    rotacao_E (&(*raiz)->E ) ;
    rotacao_D ( raiz ) ;
}

void rotacao_D_E ( no** raiz ) {
    rotacao_D ( &(*raiz)->D ) ;
    rotacao_E ( raiz ) ;
}
// função que substitui as ocorrências de c1 por c2 na string str
char* substitute(char* str, char c1, char c2){
    while(*str != '\0'){
        if(*str == c1)
            *str = c2;
        str++;
    }

    return str;
}

// Inicializa um nó
void init_no(no* node, char* linha_atual){
    char* sp = strchr(linha_atual, ' ');
    sp++;
    sp = strchr(sp, ' ');
    sp++;
    sscanf(linha_atual, "%s %d", node->palavra, &(node->quant_sinonimos));
    node->sinonimos = malloc(node->quant_sinonimos * 33);
    strcpy(node->sinonimos, sp);
    substitute(node->sinonimos, ' ', ',');
    node->nivel_max_dir = 0;
    node->nivel_max_esq = 0;

    return;
}

uint8_t rebalanceamento(no* node, uint8_t nivel_atual){
    if(!node->E)
        node->nivel_max_esq = nivel_atual;
    else
        node->nivel_max_esq = rebalanceamento(node->E, nivel_atual + 1);
    
    if(!node->D)
        node->nivel_max_dir = nivel_atual;
    else
        node->nivel_max_dir = rebalanceamento(node->D, nivel_atual + 1);

    return max(node->nivel_max_dir, node->nivel_max_esq);
    
}

int8_t calcula_fator(no* node){
    return node->nivel_max_dir - node->nivel_max_esq;
}

void rotaciona_arvore(no** node, uint8_t nivel_atual){
    if(calcula_fator((*node)) <= -2){
        if(calcula_fator((*node)->E) > 0)
            rotacao_E_D(node);
        else
            rotacao_D(node);
    }
    if(calcula_fator((*node)) >= 2){
        if(calcula_fator((*node)->D) < 0)
            rotacao_D_E(node);
        else
            rotacao_E(node);
    }
    rebalanceamento((*node), nivel_atual);
}


void insert_arvore(no** node_cabeca, no* novo_node, uint8_t nivel_atual){
    if(strcmp(novo_node->palavra, (*node_cabeca)->palavra) < 0){
        if(!(*node_cabeca)->E){
            novo_node->nivel_max_dir = nivel_atual + 1;
            novo_node->nivel_max_esq = nivel_atual + 1;
            (*node_cabeca)->E = novo_node;
        }
        else
            insert_arvore(&(*node_cabeca)->E, novo_node, nivel_atual + 1);
        
        (*node_cabeca)->nivel_max_esq = max((*node_cabeca)->E->nivel_max_dir,
                                            (*node_cabeca)->E->nivel_max_esq);
    }
    // se o novo node for maior, iremos à direita do node_cabeca
    else{
        if(!(*node_cabeca)->D){
            novo_node->nivel_max_dir = nivel_atual + 1;
            novo_node->nivel_max_esq = nivel_atual + 1;
            (*node_cabeca)->D = novo_node;
        }
        else
            insert_arvore(&(*node_cabeca)->D, novo_node, nivel_atual + 1);
        
        (*node_cabeca)->nivel_max_dir = max((*node_cabeca)->D->nivel_max_dir,
                                            (*node_cabeca)->D->nivel_max_esq);
    }
    if( abs(calcula_fator((*node_cabeca))) >= 2)
        rotaciona_arvore(node_cabeca, nivel_atual);
    return;
}

// busca
char* busca(no* node, char* palavra, char** caminho){
    if(!node){
        strcat(*caminho, "?]");
        return "-";
    }
    else if(strcmp(node->palavra, palavra) == 0){
        strcat(*caminho, node->palavra);
        strcat(*caminho, "]");
        return node->sinonimos;
    }
    else if(strcmp(palavra, node->palavra) < 0){
        strcat(*caminho, node->palavra);
        strcat(*caminho, "->");
        return busca(node->E, palavra, caminho);
    }
    else{
        strcat(*caminho, node->palavra);
        strcat(*caminho, "->");
        return busca(node->D, palavra, caminho);
    }
}

FILE* input = 0;
FILE* output = 0;


int main(int agrc, char** argv){
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if(!input){
        fprintf(stdout, "Não foi possível abrir o arquivo de input\n");
        exit(EXIT_FAILURE);
    }
    char* linha_atual = 0;
    size_t len = 0;

    uint32_t num_palavras, max_levels, i = 1;
    fscanf(input, "%d\n", &num_palavras);
    max_levels = 20;

    // criando o primeiro elemento da arvore
    no* cabeca = malloc(sizeof(no));
    getline(&linha_atual, &len, input);
    linha_atual[strlen(linha_atual) - 1] = '\0';
    init_no(cabeca, linha_atual);
    
    while (i < num_palavras)
    {
        no* atual = malloc(sizeof(no));
        getline(&linha_atual, &len, input);
        linha_atual[strlen(linha_atual) - 1] = '\0';
        init_no(atual, linha_atual);
        insert_arvore(&cabeca, atual, 0);
        i++;
    }

    int32_t num_consultas;
    fscanf(input, "%d\n", &num_consultas);
    i = 0;
    while(i < num_consultas){
        getline(&linha_atual, &len, input);
        linha_atual[strlen(linha_atual) - 1] = '\0';
        char* caminho = malloc(max_levels * 35);
        strcat(caminho, "[");
        char* sinonimos = busca(cabeca, linha_atual, &caminho);
        fprintf(output, "%s\n%s\n", caminho, sinonimos);
        i++;
    }

    fclose(input);
    fclose(output);
}