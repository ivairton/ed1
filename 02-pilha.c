/**
 * UFMT - Ciência da Computacao
 * ED1 - Prof. Ivairton
 *
 * Implementacao de PILHA com alocacao estática
 *
 */

//Incluao de bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Definicao de constantes
#define N 100

//Definicao de registro/tipo de dado
struct estruturaPilha {
    int pilha[N];
    int qtd;
};
typedef struct estruturaPilha tipoPilha;

//Prototipo de funcoes
void inicializaPilha(tipoPilha*);
void empilha(tipoPilha*, int);
int desempilha(tipoPilha*);
int topo(tipoPilha);
int vazia(tipoPilha);
void imprimePilha(tipoPilha);

//Funcao principal
//Funcao principal com passagem de parametros para sua execucao
int main(int argc, char *argv[]) {
    tipoPilha pilha;
    pilha.qtd = 0; //Inicializa contador da fila

    empilha(&pilha, 10);
    empilha(&pilha, 20);
    empilha(&pilha, 30);
    printf("Desempilhando = %d\n", desempilha(&pilha) );
    printf("Valor do topo é = %d\n", topo(pilha) );

    imprimePilha(pilha);

    return 1;
}


//Funcao que inicializa a estrutura
void inicializaPilha(tipoPilha* pilha) {
    pilha->qtd = 0;
}

//Funcao que empilha um novo valor da Pilha
void empilha(tipoPilha *pl, int vl) {
    //Verifica se ha espaco na Pilha
    if (pl->qtd < N) {
        pl->pilha[pl->qtd++] = vl; //Armazena o novo valor a primeira posicao livre (após valores), ou seja, no fim do vetor
    }
}

//Funcao que desempilha e retorna valor da Pilha
int desempilha(tipoPilha* pl) {
    //Verifica se Pilha nao está vazia
    if ( !vazia(*pl) ) {
        return pl->pilha[--(pl->qtd)];
    }
    return -1;
    //Versao 1
    if (vazia(*pl)){
        return -1; //Caso a pilha esteja vazia
    } else {
        return pl->pilha[--(pl->qtd)]; //Caso tenha valor
    }

    //VERSAO 2
    //int vl;
    //vl = pl->pilha[pl->qtd - 1];
    //pl->qtd--;
    //return vl;
}

// Funcao que retorna o elemento do topo da pilha
int topo(tipoPilha pl) {
    return pl.pilha[pl.qtd-1];
}

// Funcao que verifica se uma pilha esta vazia (retornando verdadeiro caso esteja)
int vazia(tipoPilha pl) {
    if (pl.qtd > 0) {
        return 0;
    } else {
        return 1;
    }
}

//Funcao que imprime a pilha, por questoes de debug
void imprimePilha(tipoPilha pl) {
    int i;
    printf("Pilha: |BASE| ");
    for (i=0; i < pl.qtd; i++ ){
        printf("[%d]", pl.pilha[i]);
    }
    printf(" <<=TOPO\n(Qtd de elementos=%d)\n", pl.qtd );
}
