/***
 ** UFMT - Ciencia da Computacao
 ** Disciplina ED1 - Prof Ivairton
 **
 ** Implementacao da estrutura fila com alocacao
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
void insereFila(tipoNo**, int);
int removeFila(tipoNo**);
void imprimeFila(tipoNo*);

//Funcao principal
int main(int argc, char *argv[]) {
    //Ponteiro para a fila
    tipoNo *fila;
    fila = NULL;

    insereFila(&fila, 7);
    insereFila(&fila, 1);
    insereFila(&fila, 9);
    insereFila(&fila, 3);

    imprimeFila(fila);

    printf("Valor removido da fila: %d\n", removeFila(&fila) );

    imprimeFila(fila);
    return 1;
}


//Funcao que insere um novo valor da fila com alocacao dinamica
void insereFila(tipoNo **fila, int valor) {
    tipoNo *aux, *novoNo;

    //Aloca novo no
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = NULL;

    //Verifica se a fila esta fazia
    if ( (*fila) == NULL ) {
        (*fila) = novoNo;
    } else {
        //Caso nao esteja vazia, percorre a estrutura ateh o ultimo no
        aux = (*fila);
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        //Estando no ultimo no, faz o encadeamento
        aux->prox = novoNo;
    }
}


//Remove o primeiro valor da fila
int removeFila(tipoNo **fila) {
    int auxValor;
    tipoNo *aux;
    if ( (*fila) != NULL ) {
        aux = (*fila);
        auxValor = aux->dado;
        (*fila) = (*fila)->prox;
        free(aux);
        return auxValor;
    }
    return -1; //Marcacao utilizada para representar erro (fila vazia)
}


//Funcao para imprimir a fila (apenas para debug)
void imprimeFila(tipoNo *fila) {
    //Como o ponteiro *fila nao interfere no ponteiro
    //fila da funcao main, nao serah usado um Ponteiro
    //auxiliar para percurso da estrutura encadeada
    while (fila != NULL) {
        printf("[%d]->", fila->dado);
        fila->dado = fila_>dado * 2;
        fila = fila->prox;
    }
    printf("NULO\n");
}
