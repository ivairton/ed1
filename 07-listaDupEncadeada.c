/***
 ** UFMT - Ciencia da Computacao
 ** Disciplina ED1 - Prof Ivairton
 **
 ** Implementacao da estrutura LISTA com alocacao
 ** dinamica dupla e encadeada
 **
 */

/*** Inclusao das bibliotecas ***/
#include<stdio.h>
#include<stdlib.h>

/*** Definicao da estrutura ***/
struct estruturaNo {
    int dado;
    struct estruturaNo *ant;
    struct estruturaNo *prox;
};
typedef struct estruturaNo tipoNo;

/*** Prototipacao das funcoes ***/
void insereInicio(tipoNo**, int);
void insereFim(tipoNo**, int);
void inserePosicao(tipoNo**, int, int);
int removeUltimo(tipoNo**);
int removePrimeiro(tipoNo**);
int removePosicao(tipoNo**,int);

/*** Implementacao das funcoes ***/
//Funcao que insere no inicio da lista duplamente encadeada
void insereInicio(tipoNo** lst, int valor) {
    tipoNo *novoNo;

    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->ant = NULL;
    novoNo->prox = (*lst);
    if ( (*lst) != NULL )
        (*lst)->ant  = novoNo;
    (*lst) = novoNo;
}

//Funcao que insere no fim da lista duplamente encadeada
void insereFim(tipoNo** lst, int valor) {
    tipoNo *aux, *novoNo;

    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = NULL;
    novoNo->ant = NULL;

    if ( (*lst) == NULL ) {
        (*lst) = novoNo;
    } else {
        aux = (*lst);
        while ( aux->prox != NULL )
            aux = aux->prox;
        novoNo->ant = aux;
        aux->prox = novoNo;
    }
}

//Funcao que insere um novo valor em uma posicao especifica da lista duplamente encadeada
void inserePosicao(tipoNo** lst, int valor, int pos) {
    tipoNo *aux, *novoNo;
    int cont;
    if ( pos == 0 ) {
        insereInicio(lst, valor);
    } else {
        cont = 0;
        aux = (*lst);
        while ( (aux != NULL) && (cont < pos) ) {
            aux = aux->prox;
            cont++;
        }
        if ( (aux == NULL) && (cont == pos) ) {
            insereFim(lst,valor);
        } else if ( (aux != NULL) && (cont == pos) ) {
            novoNo = (tipoNo*) malloc(sizeof(tipoNo));
            novoNo->dado = valor;
            novoNo->prox = aux;
            novoNo->ant = aux->ant;
            aux->ant->prox = novoNo;
            aux->ant = novoNo;
        }
    }
}

//Remove o ultimo no da lista duplamente ligada
int removeUltimo(tipoNo** lst) {
    if ((*lst) != NULL) { //Verifica se a lista contem valores
        int valor;
        tipoNo *aux;
        aux = (*lst);
        while (aux->prox != NULL)
            aux = aux->prox;
        valor = aux->dado;
        if (aux->ant == NULL)
            (*lst) = NULL;
        else
            aux->ant->prox = NULL;
        free (aux);
        return valor;
    } else {
        return -1;
    }
}

//Remove o primeiro elemento da lista
int removePrimeiro(tipoNo** lst) {
    if ((*lst) != NULL) {
        tipoNo *aux;
        int valor;
        aux = (*lst);
        valor = aux->dado;
        (*lst) = (*lst)->prox;
        if ( (*lst) != NULL )
            (*lst)->ant = NULL;
        free (aux);
        return valor;
    } else {
        return -1;
    }
}

//Remove um no de uma posicao especifica
int removePosicao(tipoNo** lst, int pos) {
    if ((*lst) != NULL) {
        if (pos == 0) {
            return removePrimeiro(lst);
        } else {
            tipoNo *aux;
            int valor, cont;
            cont = 0;
            aux = (*lst);
            while ( (cont < pos) && (aux != NULL) ) {
                cont++;
                aux = aux->prox;
            }
            if (aux != NULL) {
                aux->ant->prox = aux->prox;
                if (aux->prox != NULL)
                    aux->prox->ant = aux->ant;
                valor = aux->dado;
                free(aux);
                return valor;
            } else {
                return -1;
            }
        }
    } else {
        return -1;
    }
}




int main() {
    return 1;
}
