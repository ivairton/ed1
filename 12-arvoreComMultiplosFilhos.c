/**
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Prof. Ivairton
 *
 * Implementacao da estrutura Arvore Multiplos Filhos
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Definicao de Constantes
#define T 1 //T irah impactar na ordem da arvore, de modo a obedecer a relação Ordem=T*2+1 e Filhos=T*2+2
#define K (T*2+1)

//Definicao de tipos
struct est_arvM {
    int valores[K];
    struct est_arvM *filhos[K+1];
    int qtd;
};
typedef struct est_arvM tipoArvM;

//Prototipos das funcoes
tipoArvM *alocaNovoNoh();
int nohCheio(tipoArvM*);
void insereValorNoh(tipoArvM*, int);
void insereArvM (tipoArvM**, int);
void impressaoPreOrdemArvM(tipoArvM*);
void impressaoOrdemArvM(tipoArvM*);
void impressaoPosOrdemArvM(tipoArvM*);
int buscaValor(tipoArvM*, int);
int numValores(tipoArvM*);
int numNohs(tipoArvM*);
int alturaArvM(tipoArvM*);
int numNohsPorNivel(tipoArvM*, int, int);
int ehFolha(tipoArvM*);
int maior(tipoArvM*);
int menor(tipoArvM*);
void removeArvM(tipoArvM**, int);
//TODO:
//Retornar todos os valores de um certo nível


/** Funcao principal **/
int main(int argc, char *argv[]) {
    tipoArvM *arv;
    arv = NULL;

    insereArvM(&arv, 30);
    insereArvM(&arv, 20);
    insereArvM(&arv, 10);

    insereArvM(&arv, 5);
    insereArvM(&arv, 7);

    insereArvM(&arv, 23);
    insereArvM(&arv, 26);
    insereArvM(&arv, 29);

    insereArvM(&arv,27);
    insereArvM(&arv,28);


    printf("Num total de valores = %d\n", numValores(arv));
    printf("Num total de noh na arvore = %d\n", numNohs(arv));
    printf("Altura da arvore  = %d\n", alturaArvM(arv));
    printf("Numero de nos por nivel: %d\n", numNohsPorNivel(arv, 0, 3));

    impressaoPreOrdemArvM(arv); printf("\n");
    impressaoOrdemArvM(arv); printf("\n");
    impressaoPosOrdemArvM(arv); printf("\n");

    removeArvM(&arv, 20);

    impressaoPreOrdemArvM(arv); printf("\n");
    impressaoOrdemArvM(arv); printf("\n");
    return 1;
}

//Aloca um novo noh na memoria e retorna o endereco
tipoArvM *alocaNovoNoh() {
    int i;
    tipoArvM *novoNoh;
    novoNoh = (tipoArvM*) malloc(sizeof(tipoArvM));
    novoNoh->qtd = 0;
    for (i=0; i<K; i++) {
        novoNoh->valores[i] = 0;
        novoNoh->filhos[i] = NULL;
    }
    novoNoh->filhos[i] = NULL; //Atualiza o último filho
    return novoNoh;
}

// Verifica se um noh esta cheio.
// Retorna verdadeiro se cheio, ou falso, caso contrario
int nohCheio(tipoArvM* arv) {
    if (arv != NULL) {
        if (arv->qtd < K)
            return 0; //Ha espaco
    }
    return 1; //NAO ha espaco, nao pode ser inserido.
}

//Executa insercao ordenada em um noh com esapaco disponivel
void insereValorNoh(tipoArvM* no, int vl) {
    if (no != NULL) {
        if (no->qtd < K) {
            int i;
            i = no->qtd-1;
            while ( (i >= 0) && (no->valores[i] > vl) ) {
                no->valores[i+1] = no->valores[i];
                i--;
            }
            no->valores[i+1] = vl;
            no->qtd++;
        }
    }
}

//Insere um novo valor na arvore
void insereArvM (tipoArvM** arv, int vl) {
    //Se arvore vazia, aloca um no o noh e coloca o valor
    if ( (*arv) == NULL) {
        (*arv) = alocaNovoNoh();
        insereValorNoh( (*arv), vl);
    } else {
        //Verifica se ha espaco
        if ((*arv)->qtd < K) {
            insereValorNoh( (*arv), vl);
        } else {
            //Identifica o filho onde deve ocorrer a chamada recursiva
            int i;
            i = 0;
            while ( (i < K) && (vl > (*arv)->valores[i]) )
                i++;
            insereArvM(&((*arv)->filhos[i]), vl);
        }
    }
}

// Imprime a arvore usando o metodo de pre Ordem
void impressaoPreOrdemArvM(tipoArvM* arv) {
    int i;
    if (arv != NULL) {
        //Prioriza impressao dos valores
        for (i=0; i<arv->qtd; i++)
            printf("[%d]",arv->valores[i]);
        //Executa chamada recursiva
        for (i=0; i<arv->qtd+1; i++)
            impressaoPreOrdemArvM(arv->filhos[i]);
    }
}

// IMpressao em Ordem
void impressaoOrdemArvM(tipoArvM* arv) {
    int i;
    if (arv != NULL) {
        for (i=0; i < arv->qtd; i++) {
            impressaoOrdemArvM(arv->filhos[i]);
            printf("[%d]",arv->valores[i]);
        }
        impressaoOrdemArvM(arv->filhos[i]);
    }
}

// Impressao em pos Ordem
void impressaoPosOrdemArvM(tipoArvM* arv) {
    int i;
    if (arv != NULL) {
        //Prioriza impressao dos filhos
        for (i=0; i<arv->qtd+1; i++)
            impressaoPosOrdemArvM(arv->filhos[i]);
        //Imprime valores
        for (i=0; i < arv->qtd; i++)
            printf("[%d]",arv->valores[i]);
    }
}

// Busca por valor na arvore, retornando verdadeiro caso encontre e zero caso contrario
int buscaValor(tipoArvM* arv, int vl) {
    if (arv == NULL) {
        return 0;
    } else {
        int i;
        i = 0;
        while ( (i < arv->qtd) && (arv->valores[i] < vl) )
            i++;
        if ( (i < arv->qtd) && arv->valores[i] == vl)
            return 1;
        else
            return buscaValor(arv->filhos[i], vl);
    }
}

// Contabiliza o numero total de valores armazenados na Arvore
int numValores(tipoArvM* arv) {
    if (arv == NULL)
        return 0;
    else {
        int i, cont;
        cont = 0 ;
        for (i=0; i <= arv->qtd; i++)
            cont = cont + numValores(arv->filhos[i]);
        return (cont + arv->qtd);
    }
}

// Contabiliza o numero de nohs na Arvore
int numNohs(tipoArvM* arv) {
    if (arv == NULL)
        return 0;
    else {
        int i, cont;
        cont = 0 ;
        for (i=0; i <= arv->qtd; i++)
            cont = cont + numNohs(arv->filhos[i]);
        return (cont + 1);
    }
}

// Calcula a altura da arvore
int alturaArvM(tipoArvM* arv) {
    if (arv == NULL)
        return 0;
    else {
        int i, altMaior, altFilho;
        altMaior = 0 ;
        for (i=0; i <= arv->qtd; i++) {
            altFilho = alturaArvM(arv->filhos[i]);
            if ( altFilho > altMaior )
                altMaior = altFilho;
        }
        return (altMaior + 1);
    }
}

// Contabiliza o numero de noh para um certo nivel
// Parametros sao a arvore, o nivel corrente e o nivel objetivo
int numNohsPorNivel(tipoArvM* arv, int nivelAtual, int nivelAlvo) {
    if (arv == NULL)
        return 0;
    else {
        if (nivelAtual == nivelAlvo)
            return 1;
        else {
            if (nivelAtual > nivelAlvo)
                return 0;
            else {
                int i, cont;
                cont = 0;
                for (i=0; i <= arv->qtd; i++)
                    cont = cont + numNohsPorNivel(arv->filhos[i], nivelAtual+1, nivelAlvo);
                return cont;
            }
        }
    }
}


// Verifica se o noh eh folha
// Retorna verdadeiro se for folha, e falso caso contrario
int ehFolha(tipoArvM* arv) {
    int i;
    for (i=0; i <= arv->qtd; i++)
        if ( arv->filhos[i] != NULL)
            return 0;
    return 1;
}


// Encontra o maior valor em um ramo da arv
int maior(tipoArvM* arv) {
    if (arv != NULL) {
        if ( arv->filhos[arv->qtd] == NULL)
            return arv->valores[(arv->qtd)-1];
        else
            return maior( arv->filhos[arv->qtd] );
    }
}
// Encontra o menor valor em um ramo da arv
int menor(tipoArvM* arv) {
    if (arv != NULL) {
        if (arv->filhos[0] == NULL)
            return arv->valores[0];
        else
            return menor( arv->filhos[0] );
    }
}



// Remove valor da Arv Multipolos filhos
// Parametros: Arv e valor
void removeArvM(tipoArvM** arv, int vl) {
    /*
      Ha 4 possibilidades a serem tratadas:
      1) Remover um valor da lista ordenada em noh
        folha;
      2) Remover o ultimo valor de um noh folha
        (desalocando memoria e atualizando pt);
      3) Remover um valor em um noh NAO folha, que
        possui ao menos um de seus filhos. Neste caso
        encontra um valor apropriado para tomar seu
        lugar;
      4) Remover um valor em um noh NAO folha, que NAO
        possui filhos. Neste caso deve-se remover o valor
        reposicionar os vizinhos e encontrar um "filho"
        apropriado onde o novo valor (a subir) serah
        utilizado
    */
    int i, aux, idxF, idxP;

    if ( (*arv) != NULL) {
        //Executa busca pelo valor
        i = 0;
        while ( (i < (*arv)->qtd) && ( (*arv)->valores[i] < vl) )
            i++;

        if ( i < (*arv)->qtd ) {
            //Verifica se encontramos o filho a descer
            if (vl < (*arv)->valores[i])
                removeArvM(&(*arv)->filhos[i], vl);
            else { //Caso o valor tenha sido encontrado
                //Verifica se noh eh folha
                if ( ehFolha( *arv )  ) {
                    //Verifica se possui apenas 1 valor
                    if ( (*arv)->qtd == 1) {
                        free( *arv );
                        (*arv) = NULL;
                    } else { //Se possui mais de 1 valor
                        //Remove o valor da lista ordenada
                        while ( i < ((*arv)->qtd-1) ) {
                            (*arv)->valores[i] = (*arv)->valores[i+1];
                            i++;
                        }
                        (*arv)->qtd--;
                    }
                } else { //Caso o noh NAO seja folha
                    //Verifica se possui filho esq, usando o filho esq
                    if ( (*arv)->filhos[i] != NULL ) {
                        aux = maior( (*arv)->filhos[i] );
                        (*arv)->valores[i] = aux;
                        removeArvM( &(*arv)->filhos[i], aux);
                    } else if ( (*arv)->filhos[i+1] != NULL ) { //Verifica se ha filho dir, usando-o
                        aux = menor( (*arv)->filhos[i+1] );
                        (*arv)->valores[i] = aux;
                        removeArvM( &(*arv)->filhos[i+1], aux);
                    } else { //Quando nao possui filhos
                        //identifica qual eh a posicao do primeiro filho disponivel
                        idxF = 0;
                        while ( (idxF <= (*arv)->qtd) && ((*arv)->filhos[idxF] == NULL) )
                            idxF++;
                        //Identifica o pai do filho encontrado
                        if (idxF < (*arv)->qtd)
                            idxP = idxF; //Pai do filho esquerdo encontrado
                        else
                            idxP = idxF - 1; //Ultimo valor 'pai' com seu filho direito encontrado

                        //Verifica se o filho disponivel estah aa direita ou esquerda do valor
                        if (i < idxP) { //Se filho estah aa direita
                            //reposiciona valores no noh, trazendo para o inicio (sobreescrevendo valor)
                            if (idxP == idxF) { //Se o filho eh esquerdo do pai
                                while (i < idxP-1) {
                                    (*arv)->valores[i] = (*arv)->valores[i+1];
                                    (*arv)->filhos[i] = (*arv)->filhos[i+1];
                                    i++;
                                }
                            } else { //Se eh o ultimo filho do noh
                                while (i < idxP) {
                                    (*arv)->valores[i] = (*arv)->valores[i+1];
                                    i++;
                                }
                            }

                            aux = menor( (*arv)->filhos[idxF] );
                            (*arv)->valores[i] = aux;
                            removeArvM( &(*arv)->filhos[idxF], aux);
                        } else { //Se filho estah aa esquerda
                            //reposiciona valores no noh, empurra para tras (sobreescrevendo valor)
                            while (i > idxP) {
                                (*arv)->valores[i] = (*arv)->valores[i-1];
                                (*arv)->filhos[i] = (*arv)->filhos[i-1];
                                i--;
                            }

                            aux = maior( (*arv)->filhos[idxF] );
                            (*arv)->valores[i] = aux;
                            removeArvM( &(*arv)->filhos[idxF], aux);
                        }

                    }
                }
            }
        } else {
            // Desce no ultimo filho do noh (i = qtd)
            removeArvM(&(*arv)->filhos[i], vl);
        }

    } else {
        //Caso o valor nao seja encontrado
    }
}
