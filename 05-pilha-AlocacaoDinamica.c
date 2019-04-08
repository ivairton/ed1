/***
 ** UFMT - Ciencia da Computacao
 ** Disciplina ED1 - Prof Ivairton
 **
 ** Implementacao da estrutura PILHA com alocacao
 ** dinamica e encadeada
 **
 */

//Inclusao das bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Definicao da estrutura
struct estruturaNo {
    int dado;
    struct estruturaNo *prox;
};
typedef struct estruturaNo tipoNo;

//Prototipacao das funcoes
tipoNo *empilha(tipoNo*, int);
tipoNo *desempilha(tipoNo*);
int topo(tipoNo*);
void imprimePilha(tipoNo*);

//Funcao principal
int main(int argc, char *argv[]) {
    //Ponteiro para a Pilha
    tipoNo *pilha;
    pilha = NULL;

    pilha = empilha(pilha, 7);
    pilha = empilha(pilha, 1);
    pilha = empilha(pilha, 4);
    pilha = empilha(pilha, 2);

    imprimePilha(pilha);

    printf("Valor do topo: %d\n", topo(pilha) );

    pilha = desempilha(pilha);
    pilha = desempilha(pilha);

    imprimePilha(pilha);

    return 1;
}


//Funcao que EMPILHA um novo valor
tipoNo *empilha(tipoNo *pilha, int valor) {
    tipoNo *novoNo;

    //Aloca novo no
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = pilha;

    return novoNo;
}


//Desempilha
tipoNo *desempilha(tipoNo *pilha) {
    tipoNo *aux;
    if ( pilha != NULL ) {
        aux = pilha;
        pilha = pilha->prox;
        free(aux);
        return pilha;
    } else {
        return NULL;
    }
}


//Funcao que retorna o elemento do TOPO
int topo(tipoNo* pilha) {
    if (pilha != NULL) {
        return pilha->dado;
    } else {
        return -1;
    }
}

//Funcao para imprimir a pilha (apenas para debug)
void imprimePilha(tipoNo *pilha) {
    //Como o ponteiro *pilha nao interfere no ponteiro
    //pilha da funcao main, nao serah usado um Ponteiro
    //auxiliar para percurso da estrutura encadeada
    printf("TOPO => ");
    while (pilha != NULL) {
        printf("[%d]->", pilha->dado);
        pilha = pilha->prox;
    }
    printf("|BASE|\n");
}
