/**
 * UFMT - Ciencia da Computacao
 * ED1 - Prof Ivairton
 *
 * Implementacao da estrutura arvore binaria
 *
 */

#include <stdio.h>
#include <stdlib.h>


//Definicao de tipos
struct estruturaArv {
    int valor;
    struct estruturaArv *esq;
    struct estruturaArv *dir;
};
typedef struct estruturaArv tipoArv;


//Definicao de prototipos
void insereArvBin(tipoArv**, int);
void impPreOrdem(tipoArv*);
void impOrdem(tipoArv*);
void impPosOrdem(tipoArv*);
int buscaValor(tipoArv*, int);
int contaNumNos(tipoArv*);
int contaFolhas(tipoArv*);
int alturaArv(tipoArv*);
int calculaAltura(tipoArv* arv);
int contaNohNivel(tipoArv*, int, int);
int verificaFolha(tipoArv*, int);
int configuracaoDeFilhos(tipoArv*, int);
void removeArvBin(tipoArv**, int);
int encontraMaior(tipoArv*);
int encontraMenor(tipoArv*);
//Variacoes de funcoes, usando a estrategia de buscar um noh e encontrar sua referencia
tipoArv *buscaValorPt(tipoArv*, int);
int verificaFolha2(tipoArv*, int);
int configuracaoDeFilhos2(tipoArv*, int);
//TODO: remocao 2



/*** Funcao principal ***/
int main(int argc, char *argv[]) {
    tipoArv *arvBin;
    arvBin = NULL;

    insereArvBin(&arvBin, 70);
    insereArvBin(&arvBin, 40);
    insereArvBin(&arvBin, 110);
    insereArvBin(&arvBin, 20);
    insereArvBin(&arvBin, 60);
    insereArvBin(&arvBin, 80);
    insereArvBin(&arvBin, 200);
    insereArvBin(&arvBin, 10);
    insereArvBin(&arvBin, 56);
    insereArvBin(&arvBin, 90);
    insereArvBin(&arvBin, 300);
    insereArvBin(&arvBin, 7);
    insereArvBin(&arvBin, 51);
    insereArvBin(&arvBin, 57);
    insereArvBin(&arvBin, 1);

    impPreOrdem(arvBin); printf("\n");
    impOrdem(arvBin); printf("\n");
    impPosOrdem(arvBin); printf("\n");

    removeArvBin(&arvBin, 70);
    impPreOrdem(arvBin); printf("\n");

    return 1;
}


//Insere em arvore binaria
//Parametros: ponteiro para arvore e valor
void insereArvBin(tipoArv **arv, int valor) {
    //Verifica se arvore vazia
    if ( *arv == NULL ) {
        //Aloca novo noh na arvore e inicializa componentes
        (*arv) = (tipoArv*) malloc(sizeof(tipoArv));
        (*arv)->valor = valor;
        (*arv)->esq = NULL;
        (*arv)->dir = NULL;
    } else { // Verifica em qual ramo descer e faz chamada recursiva
        if (valor < (*arv)->valor) {
            insereArvBin(&(*arv)->esq, valor);
        } else { //Para o caso de valor = usa-se a direita
            insereArvBin(&(*arv)->dir, valor);
        }
    }
}


// Impressao em pre-ordem
void impPreOrdem(tipoArv* arv) {
    if (arv != NULL) {
        printf("[%d]", arv->valor);
        impPreOrdem(arv->esq);
        impPreOrdem(arv->dir);
    }
}


// Impressao em ordem
void impOrdem(tipoArv *arv) {
    if (arv != NULL) {
        impOrdem(arv->esq);
        printf("[%d]", arv->valor);
        impOrdem(arv->dir);
    }
}


// Impressao em pos ordem
void impPosOrdem(tipoArv* arv) {
    if (arv != NULL) {
        impPosOrdem(arv->esq);
        impPosOrdem(arv->dir);
        printf("[%d]", arv->valor);
    }
}


// Busca valor
// Retorna 1 caso o valor exista e 0 caso contrario
int buscaValor(tipoArv* arv, int valor) {
    if (arv == NULL) {
        return 0;
    } else {
        if (arv->valor == valor) {
            return 1;
        } else {
            if (valor < arv->valor)
                return buscaValor(arv->esq, valor);
            else
                return buscaValor(arv->dir, valor);
        }
    }
}


// Busca pelo valor na arvore e retorna o pt para o noh correspondente
tipoArv *buscaValorPt(tipoArv* arv, int valor) {
    if ( arv == NULL ) {
        return NULL;
    } else {
        if ( arv->valor == valor )
            return arv;
        else {
            if (valor < arv->valor)
                return buscaValorPt(arv->esq, valor);
            else
                return buscaValorPt(arv->dir, valor);
        }

    }
}


// Contabiliza o numero total de nos presentes na arvore
// Retorna a contabilidade
int contaNumNos(tipoArv* arv) {
    if (arv == NULL)
        return 0;
    else
        //Retorna a contabilidade do noh atual, mais seus filhos
        return ( 1 + contaNumNos(arv->esq) + contaNumNos(arv->dir) );
}


// Contabiliza o numero total de folhas na arvore
int contaFolhas(tipoArv* arv) {
    if (arv == NULL) {
        return 0;
    } else {
        if ( (arv->esq == NULL) && (arv->dir == NULL) )
            return 1;
        else
            return ( contaFolhas(arv->esq) + contaFolhas(arv->dir) );
    }
}


// Funcao principal para o calculo da altura da arvore.
// necessaria apenas para evitar a contabilidade da raiz
int alturaArv(tipoArv* arv) {
    int altEsq, altDir;
    if (arv == NULL) {
        return 0;
    } else {
        altEsq = calculaAltura(arv->esq);
        altDir = calculaAltura(arv->dir);
        if (altEsq > altDir)
            return (altEsq);
        else
            return (altDir);
    }
}


// Calcula a altura da arvore binaria
int calculaAltura(tipoArv* arv) {
    int altEsq, altDir;
    if (arv == NULL) {
        return 0;
    } else {
        altEsq = calculaAltura(arv->esq);
        altDir = calculaAltura(arv->dir);
        if (altEsq > altDir)
            return (altEsq + 1);
        else
            return (altDir + 1);
    }
}


// Contabiliza o numero de noh por nivel da arvore
// Recebe como parametro a arvore, o nivel desejado, e o nivel corrente
// Retorna a quantidade de nos no nivel desejado
int contaNohNivel(tipoArv* arv, int nivelAlvo, int nivelAtual) {
        if (arv == NULL) {
            return 0;
        } else {
            if (nivelAlvo == nivelAtual)
                return 1;
            else
                return ( contaNohNivel(arv->esq, nivelAlvo, nivelAtual+1) + contaNohNivel(arv->dir, nivelAlvo, nivelAtual+1) );
        }
}


// Verifica se um valor informado como parametro eh folha
// Funcao retorna 0 caso nao seja, 1 caso seja e -1 caso valor nao encontrado
int verificaFolha(tipoArv* arv, int valor) {
    if (arv == NULL) {
        return -1;
    } else {
        if (valor == arv->valor) {  //Se valor encontrado
            if ( (arv->esq == NULL) && (arv->dir == NULL) )
                return 1;
            else
                return 0;
        } else {
            if (valor < arv->valor)
                return verificaFolha(arv->esq, valor);
            else
                return verificaFolha(arv->dir, valor);
        }
    }
}


//Rerifica se um noh eh folha, a partir da busca que retorna pt
int verificaFolha2(tipoArv* arv, int valor) {
    tipoArv *auxArv;
    auxArv = buscaValorPt(arv, valor);
    if ( auxArv != NULL ) {
        if ( (auxArv->esq == NULL) && (auxArv->dir == NULL) )
            return 1;
        else
            return 0;
    }
    return -1;
}

// Verifica a configuracao dos filhos do no
// Recebe como parametro o valor do noh a ser verificado
// Retorna -1 se o valor nao existe;
//      0 se nao possui filhos,
//      1 caso tenha os dois,
//      2 caso tenha apenas o esq,
//      3 caso tenha apenas o direito
int configuracaoDeFilhos(tipoArv* arv, int valor) {
    if (arv == NULL) {
        return -1;
    } else {
        if (arv->valor == valor) {
            if ( (arv->esq == NULL) && (arv->dir == NULL) ) //sem filhos
                return 0;
            else if ( (arv->esq != NULL) && (arv->dir != NULL) ) //Os dois filhos
                return 1;
            else if ( (arv->esq != NULL) && (arv->dir == NULL) ) //apenas o esquerdo
                return 2;
            else //Apenas o direito
                return 3;
        } else {
            if (valor < arv->valor)
                return configuracaoDeFilhos(arv->esq, valor);
            else
                return configuracaoDeFilhos(arv->dir, valor);
        }
    }
}


int configuracaoDeFilhos2(tipoArv* arv, int valor) {
    // Verifica a configuracao dos filhos do no
    // Recebe como parametro o valor do noh a ser verificado
    // Retorna -1 se o valor nao existe;
    //      0 se nao possui filhos,
    //      1 caso tenha os dois,
    //      2 caso tenha apenas o esq,
    //      3 caso tenha apenas o direito
    tipoArv *aux;
    aux = buscaValorPt(arv,valor);

    if (aux != NULL) {
        if ( (aux->esq == NULL) && (aux->dir == NULL) )
            return 0;
        else if ( (aux->esq != NULL) && (aux->dir != NULL) )
            return 1;
        else if ( (aux->esq != NULL) && (aux->dir == NULL) )
            return 2;
        else
            return 3;
    }
    return -1;
}


//Remove um valor da arvore binaria
void removeArvBin(tipoArv **arv, int valor) {
    int auxValor;
    if ((*arv) != NULL) {
        //Busca pelo valor
        if ( (*arv)->valor != valor) {
            if (valor < (*arv)->valor)
                removeArvBin(&(*arv)->esq, valor);
            else
                removeArvBin(&(*arv)->dir, valor);
        } else { //Quando o valor for encontrado
            //Caso o noh seja folha, desaloca e atualiza pt
            if ( ((*arv)->esq == NULL) && ((*arv)->dir == NULL) ) {
                free( (*arv) );
                (*arv) = NULL;
            } //Caso exista apenas o filho esquerdo
              else if ( ((*arv)->esq != NULL) && ((*arv)->dir == NULL) ) {
                auxValor = encontraMaior( (*arv)->esq ) ;
                (*arv)->valor = auxValor;
                removeArvBin( &(*arv)->esq, auxValor);
            } //Caso tenha os dois filhos, ou apenas o direito
               else {
                auxValor = encontraMenor( (*arv)->dir );
                (*arv)->valor = auxValor;
                removeArvBin( &(*arv)->dir, auxValor);
            }
        }
    }
}


//Encontra o maior valor presente na arvore
int encontraMaior(tipoArv* arv) {
    if ( arv->dir == NULL )
        return arv->valor;
    else
        return encontraMaior(arv->dir);
}


// Encontra o menor valor presente na arvore
int encontraMenor(tipoArv* arv) {
    if ( arv->esq == NULL )
        return arv->valor;
    else
        return encontraMenor(arv->esq);
}
