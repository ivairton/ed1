/**
 * UFMT - Ciencia da Computacao
 * ED1 - PRof. Ivairton
 *
 * Implementacao da estrutura Tabela Hash
 * com tratamento de colisao baseada em lista ligada
 */

//Inclusao de bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Constante
#define N 10

//Definicao de tipo da tabela Hash
//A estrutura irá considerar o armazenamento de um numero
//inteiro por registro.
struct estrutura_hash {
    int valor;
    struct estrutura_hash *prox;
};
typedef struct estrutura_hash tipoHash;

//Prototipacao
void inicializaHash(tipoHash**);
int funcHash(int);
int insereHash(tipoHash**, int);
int buscaHash(tipoHash**, int);
int removeHash(tipoHash**, int);
void imprimeHash(tipoHash**);

//Funcao principal
int main(int argc, char *argv[]) {
    tipoHash *tabHash[N];
    inicializaHash(tabHash);

    insereHash(tabHash, 77);
    insereHash(tabHash, 33);
    insereHash(tabHash, 99);
    insereHash(tabHash, 333);
    insereHash(tabHash, 999);
    insereHash(tabHash, 9999);

    imprimeHash(tabHash);

    int valor;
    valor = 9999;
    if ( buscaHash(tabHash, valor) )
        printf("Valor %d ENCONTRADO\n", valor);
    else
        printf("Valor %d NAO encontrado\n", valor);

    removeHash(tabHash, 33);
    removeHash(tabHash, 333);
    imprimeHash(tabHash);

    return 1;
}


//Funcao que inicializa a tabela hash
void inicializaHash(tipoHash **tabHash) {
    int i;
    for (i=0; i<N; i++) {
        tabHash[i] = NULL;
    }
}


//Funcao Hash
//Funcao com metodo matematico mais simples possivel
//que consiste apenas de considerar como indice o
//resto da divisao do ID do dado pela capacidade da
//tabela hash. Ha outros metodos estatisticamente mais
//eficiente
int funcHash(int id) {
    return id%N; //Resto da divisiao do ID pelo tamanho da tab hash
}


//Insere um novo valor na tabela hash, tratando colisao com lista ligada
int insereHash(tipoHash** tabHash, int id) {
    int pos;
    tipoHash *aux;

    pos = funcHash(id);
    //Verifica se a posicao esta livre
    if ( tabHash[pos] == NULL) {
        tabHash[pos] = (tipoHash*) malloc(sizeof(tabHash));
        tabHash[pos]->valor = id;
        tabHash[pos]->prox = NULL;
    } else {
        //Trata a colisao percorrendo a lista e inserindo ao final
        aux  = tabHash[pos];
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = (tipoHash*) malloc(sizeof(tipoHash));
        aux = aux->prox;
        aux->valor = id;
        aux->prox = NULL;
    }
    return 1;
}


//Funcao de impressao da Tabela
void imprimeHash(tipoHash** tabHash) {
    int i;
    tipoHash *aux;
    for(i=0; i<N; i++) {
        if (tabHash[i] == NULL) {
            printf( "Pos[%d]: [NULO]\n", i );
        } else {
            aux = tabHash[i];
            printf( "Pos[%d]: ", i);
            while (aux != NULL) {
                printf("[%d]->", aux->valor);
                aux = aux->prox;
            }
            printf("[NULO]\n");
        }
    }
}



//Busca valor na tab hash
//Retorna 1 se encontrado, 0 se ausente
//Em um contexto com dados, a busca deve retornar todo o conjunto de dados
int buscaHash(tipoHash** tabHash, int id) {
    int pos;
    tipoHash *aux;
    pos = funcHash(id);

    aux = tabHash[pos];
    //Se posicao na hash estiver com valor
    while (aux != NULL) {
        if (aux->valor == id)
            return 1;
        aux = aux->prox;
    }
    return 0;
}


//Remove dado da tab Hash
//Retorna 1 para sucesso, ou 0 para falha
int removeHash(tipoHash** tabHash, int id) {
    int pos;
    tipoHash *aux, *auxAnt;

    if ( buscaHash(tabHash,id) ) {
        pos = funcHash(id);
        aux = tabHash[pos];
        if (aux->valor == id) {
            tabHash[pos] = aux->prox;
            free(aux);
            return 1;
        } else {
            while ( (aux != NULL) && (aux->valor != id) ) {
                auxAnt = aux;
                aux = aux->prox;
            }
            if (aux->valor == id) {
                auxAnt->prox = aux->prox;
                free(aux);
                return 1;
            }
        }
    }
    return 0;
}
