/**
 * UFMT - Ciência da Computacao
 * ED1 - Prof. Ivairton
 *
 * Implementacao de fila com prioridade, com alocacao estática.
 *
 */

//Incluao de bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Definicao de constantes
#define N 100


//Definicao de registro/tipo de dado
//Definiçao da estrutura dos dados
struct estruturaDado {
    int dado;
    int prio;
};
typedef struct estruturaDado tipoDado;

//Definicao da estrutura da fila
struct estruturaFila {
    tipoDado fila[N];
    int qtd;
};
typedef struct estruturaFila tipoFila;

//Prototipo de funcoes
void inicializaFila(tipoFila*);
void insereFila(tipoFila*, tipoDado);
tipoDado removeFila(tipoFila*);
tipoDado primeiroFila(tipoFila);
int qtdFila(tipoFila);
void imprimeFila(tipoFila);

//Funcao principal
//Funcao principal com passagem de parametros para sua execucao
int main(int argc, char *argv[]) {
    tipoFila fila;
    inicializaFila (&fila);

    tipoDado dt;

    dt.dado = 10;
    dt.prio = 5;
    insereFila(&fila, dt);

    dt.dado = 20;
    dt.prio = 8;
    insereFila(&fila, dt);

    dt.dado = 30;
    dt.prio = 2;
    insereFila(&fila, dt);

    dt.dado = 40;
    dt.prio = 2;
    insereFila(&fila, dt);

    dt = removeFila(&fila);
    printf("Retirando valor da fila = %d(%d)\n", dt.dado, dt.prio );
    printf("Primeiro valor da fila é = %d\n", primeiroFila(fila).dado );
    printf("Atualmente fila tem %d valores\n", qtdFila(fila) );
    imprimeFila(fila);

    return 1;
}


//Funcao que inicializa a estrutura
void inicializaFila(tipoFila* fila){
    fila->qtd = 0;
}

//Funcao que insere COM PRIORIDADE um novo valor da Fila
void insereFila(tipoFila *fl, tipoDado dado) {
    int i;
    //Verifica se ha espaco na Fila
    if (fl->qtd < N) {
        //Verifica se fila estah vazia, para este caso insere na pos zero
        if (fl->qtd == 0) {
            fl->fila[fl->qtd++] = dado;
        } else {
            //Insere em posicao comparando as prioridades
            i = fl->qtd;
            while ( (i > 0) && (fl->fila[i-1].prio > dado.prio) ) {
                //reposiciona o dado ja presente na Fila
                fl->fila[i] = fl->fila[i-1];
                i--;
            }
            fl->fila[i] = dado;
            fl->qtd++;
        }


    }
}

//Remove e retorna valor da fila
tipoDado removeFila(tipoFila* fl) {
    int i;
    tipoDado vl;

    //Verifica se fila tem valor
    if (fl->qtd > 0) {
        vl = fl->fila[0]; //Guarda o 1o valor
        //reposiciona os valores
        for (i=0; i < (fl->qtd-1); i++) {
            fl->fila[i] = fl->fila[i+1];
        }
        fl->qtd--; //Decrementa contador
        return vl; //Retorna o valor guardado no inicio da funcao
    } else {
        //Impressicao logica, pois a fila está vazia mas devolve o valor -1
        vl.dado = -1;
        vl.prio = -1;
        return vl;
    }
}

// Funcao que retorna o 1o elemento da fila
tipoDado primeiroFila(tipoFila fl) {
    return fl.fila[0];
}

// Retorna a quantidade de valores da fila
int qtdFila(tipoFila fl) {
    return fl.qtd;
}

//Funcao que imprime a fila, por questoes de debug
void imprimeFila(tipoFila fl) {
    int i;
    printf("Fila: ");
    for (i=0; i < qtdFila(fl); i++ ){
        printf("[%d|%d]", fl.fila[i].dado, fl.fila[i].prio);
    }
    printf(" (Qtd de elementos=%d)\n", qtdFila(fl) );
}
