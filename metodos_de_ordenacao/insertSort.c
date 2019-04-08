/**
 * UFMT - Ciencia da Computacao
 * ED1 - Ivairton
 *
 * Implementacao da estrutura lista e metodo de ordenação Insert Sort
 *
 */

//Inclusao de bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Constante
#define N 100

//Definicao de tipo
struct estruturaLista {
    int lista[N];
    int qtd;
};
typedef struct estruturaLista tipoLista;

//Prototipos
void insereFimLista (tipoLista*, int);
int removePosicaoLista (tipoLista*, int);
void imprimeLista (tipoLista);
//Metodo de ordenação
void insertSort(tipoLista*);


//Funcao principal
int main(int argc, char *argv[]){
    tipoLista lista;
    lista.qtd = 0;

    //Geracao de numeros pseudoaleatorios
    time_t tm; //Usado na geração da semente
    srand( (unsigned) time(&tm) );

    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    insereFimLista(&lista, rand()%20);
    
    imprimeLista(lista);

    insertSort(&lista);

    return 1;
}

//Funcao para insercao de valor no fim da lisat
void insereFimLista (tipoLista* lst, int vl) {
    if ( lst->qtd < N ) {
        lst->lista[lst->qtd++] = vl;
    }
}

//Funcao que remove um valor em posicao especifica da lista
int removePosicaoLista (tipoLista* lst, int pos) {
    int i, vl;

    if ( (lst->qtd > 0) && (pos < lst->qtd) && (pos >= 0) ) {
        vl = lst->lista[pos];
        i = pos;
        while ( i < lst->qtd-2 ) {
            lst->lista[i] = lst->lista[i+1];
            i++;
        }
        lst->qtd--;
        return vl;
    } else {
        return -1;
    }

}

//Funcao que imprime a estrutura
void imprimeLista (tipoLista lst) {
    int i;
    printf("Lista: ");
    for (i=0; i<lst.qtd; i++) {
        printf("[%d]", lst.lista[i]);
    }
    printf("(Qtd = %d)\n", lst.qtd);
}

//Ordenacao Insert Sort
void insertSort(tipoLista* lst) {
    int vl, i, pos;

    //Verifica se a lista possui ao menos 2 elementos (ou mais)
    if (lst->qtd > 1) {
        i = 1;
        while (i < lst->qtd) {
            vl = lst->lista[i];
            pos = i;
            while ( (pos > 0) && (lst->lista[pos-1] > vl) ) {
                lst->lista[pos] = lst->lista[pos-1];
                pos--;
            }
            lst->lista[pos] = vl;
            i++;
        }
    }
}
