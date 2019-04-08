/***
 ** UFMT - Ciencia da Computacao
 ** Disciplina ED1 - Prof Ivairton
 **
 ** Implementacao da estrutura LISTA com alocacao
 ** dinamica e encadeada - CIRCULAR
 **
 */

/*** Inclusao das bibliotecas ***/
#include<stdio.h>
#include<stdlib.h>

/*** Definicao da estrutura ***/
struct estruturaNo {
    int dado;
    struct estruturaNo *prox;
};
typedef struct estruturaNo tipoNo;

/*** Prototipacao das funcoes ***/
void insereInicio(tipoNo**, int);
void insereFim(tipoNo**, int);
int inserePosicao(tipoNo**, int, int);

//TODO:
int removeInicio(tipoNo**);
int removeFim(tipoNo**);
int removePosicao(tipoNo**, int);
int contaElementos(tipoNo*);

//*** Funcao principal (apenas para teste da biblioteca) ***
int main() {
    return 1;
}

//*** IMPLEMETACAO DAS FUNCOES ***

//Funcao que insere no inicio da lista circular
void insereInicio(tipoNo** lst, int valor) {
    tipoNo *novoNo;
    //Aloca novo no
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = (*lst);

    //Percorre lista para que ultimo aponte para o primeiro
    if (*lst == NULL) {
        novoNo->prox = novoNo;
    } else {
        tipoNo *aux;
        aux = (*lst);
        while (aux->prox != (*lst))
            aux = aux->prox;
        aux->prox = novoNo;
    }
    (*lst) = novoNo;
}

//Funcao que insere no fim da lista circular
void insereFim(tipoNo **lst, int valor) {
    tipoNo *aux, *novoNo;

    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = NULL;

    if ((*lst) == NULL) {
        novoNo->prox = novoNo;
        (*lst) = novoNo;
    } else {
        aux =  (*lst);
        while (aux->prox != (*lst))
            aux = aux->prox;
        aux->prox = novoNo;
        novoNo->prox = (*lst);
    }
}

//Funcao que insere em uma posicao especifica da list circular
int inserePosicao(tipoNo **lst, int valor, int pos) {
    tipoNo *aux, *auxAnt, *novoNo;
    int cont;

    if (pos == 0) {
        insereInicio(lst, valor);
    } else {
        if ((*lst) != NULL) {
            aux = (*lst)->prox;
            auxAnt = (*lst);
            cont = 1;
            while ( (cont < pos) && (aux != (*lst)) ) {
                cont++;
                auxAnt = aux;
                aux = aux->prox;
            }
            if (cont == pos) {
                novoNo = (tipoNo*) malloc(sizeof(tipoNo));
                novoNo->dado = valor;
                novoNo->prox = aux;
                auxAnt->prox = novoNo;
            }
        }
    }
}

//Funcao que remove valor do inicio da lista circular
int removeInicio(tipoNo **lst) {
    novoNo *aux, *noRemover;
    int valor;

    if ((*lst) != NULL) {
        noRemover = (*lst);
        valor = noRemover->dado;

        aux = (*lst);
        if (aux == aux->prox) {
            free(aux);
            (*lst) = NULL;
            return valor;
        } else {
            while ( aux->prox != (*lst) ) {
                 aux = aux->prox;
            }
            (*lst) = (*lst)->prox;
            aux->prox = (*lst);
            free(noRemover);
            return valor;
        }
    }
}
