/***
 ** UFMT - Ciencia da Computacao
 ** Disciplina ED1 - Prof Ivairton
 **
 ** Implementacao da estrutura LISTA com alocacao
 ** dinamica e encadeada
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
int insereAposValor(tipoNo**, int, int);

int removeInicio(tipoNo**);
int removeFim(tipoNo**);
int removePosicao(tipoNo**, int);
int removeValor(tipoNo**, int);

int buscaValor(tipoNo*, int);
int buscaPosicao(tipoNo*, int);
int contaElementos(tipoNo*);

tipoNo *divideLista(tipoNo**, int);
tipoNo *uneLista(tipoNo*, tipoNo*);

tipoNo *ordenaLista(tipoNo*);

//*** Funcao principal (apenas para teste da biblioteca) ***
int main() {
    return 1;
}

//*** IMPLEMETACAO DAS FUNCOES ***

//Funcao que intese no inicio da lista
void insereInicio(tipoNo** lst, int valor) {
    tipoNo *novoNo;
    //Aloca novo no
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = (*lst);
    (*lst) = novoNo;
}

//Funcao que insere no fim da lista
void insereFim(tipoNo** lst, int valor) {
    tipoNo *aux, *novoNo;
    //Aloca novo no
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    novoNo->dado = valor;
    novoNo->prox = NULL;

    //Verifica se a lista esta fazia
    if ( (*lst) == NULL ) {
        (*lst) = novoNo;
    } else {
        //Caso nao esteja vazia, percorre a estrutura ateh o ultimo no
        aux = (*lst);
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        //Estando no ultimo no, faz o encadeamento
        aux->prox = novoNo;
    }
}

//Funcao que insere em uma posicao especifica
//Retorna verdade (1) se a insercao ocorrer, ou falso (0) caso contrario
int inserePosicao(tipoNo** lst, int valor, int pos) {
    if ( pos > contaElementos(*lst) ) { //Impossivel adicionar elemento
        return 0; //sinal de erro
    } else {
        if (pos == 0) {
            insereInicio(lst, valor);
        } else if ( pos == contaElementos(*lst) ) {
            insereFim(lst, valor);
        } else {
            int cont;
            tipoNo *aux, *novoNo;
            aux = (*lst);
            cont = 0;
            while (cont < (pos-1) ) {
                aux = aux->prox;
                cont++;
            }
            novoNo = (tipoNo*) malloc(sizeof(tipoNo));
            novoNo->dado = valor;
            novoNo->prox = aux->prox;
            aux->prox = novoNo;
        }
        return 1;
    }
}

//Funcao que insere um novo noh apos um valor de referencia
//Retorna verdade (1) caso a insercao ocorra, ou falso (0) caso contrario
int insereAposValor(tipoNo** lst, int valor, int referencia) {
    //Caso o valor de referencia exista na lista
    if ( buscaValor((*lst), referencia) ) {
        tipoNo *aux, *novoNo;
        aux = (*lst);
        while(aux->dado != referencia) {
            aux = aux->prox;
        }
        novoNo = (tipoNo*) malloc(sizeof(tipoNo));
        novoNo->dado = valor;
        novoNo->prox = aux->prox;
        aux->prox = novoNo;

        return 1;
    } else { //Caso o valor de referencia nao esteja presente
        return 0;
    }
}

//Funcao que remove o primeiro elemento da LISTA
//A funcao retorna -1 no caso de lista vazia
int removeInicio(tipoNo** lst) {
    tipoNo* aux;
    int valor;
    //Caso lista diferente de vazia
    if ((*lst) != NULL) {
        valor = (*lst)->dado; //Armazena valor a ser removido
        aux = (*lst); //Guarda referencia do noh a ser desalocado
        (*lst) = (*lst)->prox; //Atualiza ponteiro principal da lista
        free(aux); //Libera memoria
    } else { //Caso lista vazia
        valor  = -1; //Codigo de erro
    }
    return valor;
}

//Funcao que remove do fim da LISTA
//Retorna o valor removido ou -1 no caso de erro
int removeFim(tipoNo** lst) {
    tipoNo *aux, *auxAnt;
    int valor;
    if ( (*lst) != NULL ) {
        aux = (*lst);
        while ( aux->prox != NULL ) {
            auxAnt = aux;
            aux = aux->prox;
        }
        valor = aux->dado;
        auxAnt->prox = NULL;
        free(aux);
    } else {
        valor  = -1;
    }
    return valor;
}

//Funcao que remove um valor de uma posicao especifica da LISTA
//Retorna verdadeiro o valor caso ocorra a remocao, ou falha (-1) caso contrario
int removePosicao(tipoNo** lst, int pos) {
    if ( ( (*lst) != NULL ) && (pos < contaElementos(*lst)) ) {
        int cont, valor;
        tipoNo *aux, *auxAnt;
        cont =0;
        aux = (*lst);
        while(cont < pos ) {
            auxAnt = aux;
            aux = aux->prox;
            cont++;
        }
        valor = aux->dado;
        auxAnt->prox = aux->prox;
        free(aux);
        return valor;
    } else { //Houve uma falha por lista vazia ou posicao invalida
        return -1;
    }
}

//Funcao que remove noh pelo valor
//Retorna verdadeiro (1) no caso da remocao, ou falso (0) caso contrario
int removeValor(tipoNo** lst, int valor) {
    if ( (*lst) != NULL ) {
        if ( buscaValor((*lst),valor) ) {
            tipoNo *aux, *auxAnt;
            aux = (*lst);
            while (aux->dado != valor) {
                auxAnt = aux;
                aux = aux->prox;
            }
            auxAnt->prox = aux->prox;
            free(aux);
            return 1;
        } else { //retorna falso caso o valor nao exista na estrutura
            return 0;
        }
    } else {
        return 0;
    }
}

//Funcao que busca por um valor na lista, retorna 0 para nao e 1 para sim
int buscaValor(tipoNo* lst, int valor) {
    while (lst != NULL) {
        if (lst->dado == valor)
            return 1;
    }
    return 0;
}
//int buscaPosicao(tipoNo*, int);
//Funcao auxiliar que contabiliza quantos elementos há na estrutura
int contaElementos(tipoNo* lst) {
    int cont;
    cont = 0 ;
    while (lst != NULL) {
        lst = lst->prox;
        cont++;
    }
    return cont;
}

//Funcao que divide uma lista em duas, mantendo o pronteiro lst para a
//primeira metade e retornando o ponteiro para a segunda metade.
//Caso ocorra alguma falha, a funcao retorna nulo.
tipoNo *divideLista(tipoNo** lst, int pos){
    if (pos < contaElementos((*lst)) ) {
        tipoNo *aux, *auxAnt;
        int cont;
        cont = 0;
        aux = (*lst);

        //verifica se a posicao informada eh a zero
        if (pos == 0) {
            (*lst) = NULL;
            return aux;
        } else {
            while (cont < pos) {
                auxAnt = aux;
                aux = aux->prox;
                cont++;
            }
            auxAnt->prox = NULL;
            return aux;
        }
    } else { //No caso de uma posicao invalida
        return NULL;
    }
}

//Executa a uniao de duas listas e retorna o ponteiro para o inicio da nova lista
tipoNo *uneLista(tipoNo *lst1, tipoNo *lst2) {
    if ( (lst1 == NULL) && (lst2 == NULL) ) {
        return NULL;
    } else {
        if (lst1 == NULL) {
            return lst2;
        } else if (lst2 == NULL) {
            return lst1;
        } else {
            tipoNo *aux;
            aux = lst1;
            while (aux->prox != NULL)
                aux = aux->prox;
            aux->prox = lst2;
            return lst1;
        }
    }
}

//Constroi um vetor com os valores da estrutura, aplica o metodo de ordenacao e atualiza a estrutura da lista
tipoNo *ordenaLista(tipoNo *lst) {
    int cont, i, *vet;
    tipoNo *aux;
    cont = contaElementos(lst);
    vet = (int*) malloc(sizeof(int * cont));
    aux = lst;
    //Copia os valores da estrutura para o vetor
    for (i=0; i<cont; i++) {
        vet[i] = aux->dado;
        aux = aux->prox;
    }
    //Aplica ordenacao
    quickSort(vet,cont);
    //Copia os valores do vetor para a estrutura lista
    aux = lst;
    for (i=0; i<cont; i++) {
        aux->dado = vet[i];
        aux = aux->prox;
    }
    return lst;
}
