#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

FILE* input = 0;
FILE* output = 0;

uint32_t ordem_arvore = 0;
uint32_t MAX = 0;
uint32_t MIN = 0;
uint32_t quant_arquivos = 0;

typedef struct arquivo{
    char nome_arquivo[32], hash[34];
    uint32_t size;
} arquivo;

typedef struct no{
    arquivo* arquivos;
    struct no** filhos;
    // quantidade utilizada
    uint32_t n;
} no;

no* raiz = 0;

no* create_node(arquivo new_arq, no* filho){
    no* new_node = calloc(1, sizeof(no));
    new_node->arquivos = calloc(MAX + 1, sizeof(arquivo));
    new_node->filhos = calloc(ordem_arvore, sizeof(no*));

    new_node->arquivos[1] = new_arq;
    new_node->n = 1;
    new_node->filhos[0] = raiz;
    new_node->filhos[1] = filho;
    return new_node;
}

void insert_node(arquivo new_arq, int pos, no* node, no* filho){
    int j = node->n;
    while (j > pos) {
        node->arquivos[j + 1] = node->arquivos[j];
        node->filhos[j + 1] = node->filhos[j];
        j--;
    }
    node->arquivos[j + 1] = new_arq;
    node->filhos[j + 1] = filho;
    node->n++;
}

void split_node(arquivo new_arq, arquivo* p_arq, uint8_t pos, no* node, no* filho, no** new_node){
    int median, j;
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;
    
    *new_node = calloc(1, sizeof(no));
    (*new_node)->arquivos = calloc(MAX + 1, sizeof(arquivo));
    (*new_node)->filhos = calloc(ordem_arvore, sizeof(no*));
    j = median + 1;
    while (j <= MAX){
        (*new_node)->arquivos[j - median] = node->arquivos[j];
        (*new_node)->filhos[j - median] = node->filhos[j];
        j++;
    }
    node->n = median;
    (*new_node)->n = MAX - median;

    if (pos <= MIN)
        insert_node(new_arq, pos, node, filho);    
    else
        insert_node(new_arq, pos - median, *new_node, filho);
    
    *p_arq = node->arquivos[node->n];
    (*new_node)->filhos[0] = node->filhos[node->n];
    node->n--;
}

uint8_t set_value(arquivo new_arq, arquivo* parq, no* node, no** filho){
    uint32_t pos;

    if (!node){
        *parq = new_arq;
        *filho = 0;
        return 1;
    }
    for(pos = node->n; (strcmp(new_arq.hash, node->arquivos[pos].hash) < 0 && pos > 0); pos--);
    
    if (set_value(new_arq, parq, node->filhos[pos], filho)) {
        if (node->n < MAX)
            insert_node(*parq, pos, node, *filho);
        else{
            split_node(*parq, parq, pos, node, *filho, filho);
            return 1;
        }
    }
    return 0;
}

void init_arquivo(arquivo* arq, char* linha_info_arquivo){
    sscanf(linha_info_arquivo, "%s %d %s", arq->nome_arquivo, &(arq->size), arq->hash);
    return;
}

void print_node_info(no* node){
    int i = 1;
    if (!node) {
        fprintf(output, "-\n");
        return;
    }
    while (i <= node->n) {
        fprintf(output, "%s:size=%d,hash=%s\n", node->arquivos[i].nome_arquivo,
                                                node->arquivos[i].size,
                                                node->arquivos[i].hash);
        i++;
    }
    return;
}

no* busca(no* x, char* hash){
    no* r = 0;
    if(x){
        uint32_t i = 0;
        // se o hash buscado for maior que o da chave atual, incrementamos
        while(i < x->n && strcmp(hash, x->arquivos[i+1].hash) > 0){
            i++;
        }
        // se pararmos de incrementar e for igual os hashs, encontramos
        if(i <= x->n && strcmp(hash, x->arquivos[i+1].hash) == 0)
            r = x;
        // caso contrario buscamos no nó filho daquele indice
        else
            r = busca(x->filhos[i], hash);
    }
    return r;
}

void insert(arquivo new_arq){
    uint8_t val;
    arquivo p_arq;
    no* child;

    val = set_value(new_arq, &p_arq, raiz, &child);
    if (val)
        raiz = create_node(p_arq, child);    
}


int main(int argc, char** argv){
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if(!input){
        fprintf(stdout, "Não foi possivel abrir o arquivo de entrada\n");
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d\n%d\n", &ordem_arvore, &quant_arquivos);
    MAX = ordem_arvore - 1;
    MIN = ordem_arvore / 2;

    char* linha_atual = 0;
    size_t len = 0;
    int i = 0;
    while (i < quant_arquivos){
        getline(&linha_atual, &len, input);
        linha_atual[strlen(linha_atual) - 1] = '\0';
        arquivo new_arq;
        init_arquivo(&new_arq, linha_atual);
        /* if(i == 2){
            int num = 10;
            num++;
        } */
        insert(new_arq);
        i++;
        free(linha_atual);
        linha_atual = 0;
    }
    uint32_t quant_operacoes;
    fscanf(input, "%d\n", &quant_operacoes);
    i = 0;
    char* sp = 0;
    while (i < quant_operacoes){
        getline(&linha_atual, &len, input);
        linha_atual[strlen(linha_atual) - 1] = '\0';
        sp = strchr(linha_atual, ' ');
        sp++;
        if (linha_atual[0] == 'S'){
            no* result = busca(raiz, sp);
            fprintf(output, "[%s]\n", sp);
            print_node_info(result);
        }
        else {
            arquivo new_arq;
            init_arquivo(&new_arq, sp);
            insert(new_arq);
        }
        i++;
        free(linha_atual);
        linha_atual = 0;
    }
    
    fclose(input);
    fclose(output);
}