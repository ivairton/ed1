/**
 * UFMT - Ciencia da Computacao
 * ED1 - PRof Ivairton
 *
 * Implementacao de HEAP e Heap Sort
 */

#include<stdio.h>
#include<stdlib.h>

//Definicao de constante
#define N 10

//Definicao da estrutura do HEAP
struct estruturaHeap {
    int vetHeap[N];
    int qtd;
};
typedef struct estruturaHeap tipoHeap;


//Prototipacao das funcoes
int pai(int);
int filhoEsq(int);
int filhoDir(int);
void insereHeap(tipoHeap*, int);
int removeRaizHeap(tipoHeap*);
int removeValorHeap(tipoHeap*, int);
void sobeHeap(tipoHeap*, int);
void desceHeap(tipoHeap*, int);
void heapSort(int*, int, int);




// Funcao principal para testes
int main(int argc, char *argv[]) {
    tipoHeap heap;
    heap.qtd = 0; //Inicializa contador do heap

    insereHeap(&heap, 10);
    insereHeap(&heap, 7);
    insereHeap(&heap, 15);
    insereHeap(&heap, 20);
    insereHeap(&heap, 30);
    insereHeap(&heap, 22);
    insereHeap(&heap, 50);

    removeValorHeap(&heap,15);


    int i;
    for (i=0; i<heap.qtd; i++)
        printf("[%d]", heap.vetHeap[i]);
    printf("\n");

    //Experimento do Heap Sort
    int vet[N] = {5,2,7,6,10}; //Cria um vetor para teste
    heapSort(vet, N, 5);
    printf("Aplicação do Heap Sort: ");
    for (i=0; i<5; i++)
        printf("[%d]", vet[i]);
    printf("\n");

    return 1;
}



//Funcao que retorna o indice do pai
int pai(int idx) {
    return (int) (idx-1)/2;
}



//Retorna o indice do filho esquerdo
int filhoEsq(int idx) {
    return 2 * idx + 1;
}



//Retorna o indice do filho direito
int filhoDir(int idx) {
    return 2 * idx + 2;
}



//Insercao na estrutura HEAP
void insereHeap(tipoHeap *heap, int valor) {
    //Verifica se o heap tem espaco
    if (heap->qtd < N) {
        heap->vetHeap[heap->qtd++] = valor;
        sobeHeap(heap, heap->qtd-1);
    }
}



//Remove o valor na raiz do heap.
//Retorna o valor removido
int removeRaizHeap(tipoHeap *heap) {
    int valor;
    if (heap->qtd > 0) {
        valor = heap->vetHeap[0]; //Guarda o valor para o retorno
        heap->vetHeap[0] = heap->vetHeap[ --heap->qtd ]; //Move o último valor do heap para a raiz
        desceHeap(heap, 0); //Funcao para manutencao do heap, a partir da raiz
    } else {
        valor = -1; //Sinaliza falha na remocao
    }
    return valor;
}



//Busca e remove um valor especifico do heap
int removeValorHeap(tipoHeap *heap, int valor) {
    int idx;
    if (heap->qtd > 0) {
        //Busca valor no vetor do heap
        idx = 0;
        while ( (idx < heap->qtd) && (heap->vetHeap[idx] != valor) ) {
            idx++;
        }
        //Verifica se o valor foi encontrado
        if (idx < heap->qtd) {
            heap->vetHeap[idx] = heap->vetHeap[ --heap->qtd ]; //Move o último valor do heap para o indice do valor encontrado
            //Verifica a possibilidade do valor removido estar em uma folha em outro ramo
            if ( (idx != 0) && (heap->vetHeap[pai(idx)] < heap->vetHeap[idx]) )
                sobeHeap(heap, idx);
            else
                desceHeap(heap, idx); //Funcao para manutencao do heap, a partir do indice do valor encontrado
        } else {
            //Caso o valor não tenha sido encontrado, retorna sinal de erro
            idx = -1;
        }
    } else {
        idx = -1; //Sinaliza falha na remocao
    }

    return idx;
}


//Corrige estrutura do heap elevando o valor ao nivel adquado
void sobeHeap(tipoHeap* heap, int idx) {
    int aux;
    if (heap->vetHeap[idx] > heap->vetHeap[ pai(idx) ]) {
        aux = heap->vetHeap[idx];
        heap->vetHeap[idx] = heap->vetHeap[pai(idx)];
        heap->vetHeap[pai(idx)] = aux;
        //Chamada recursiva
        if (pai(idx) != 0)
            sobeHeap(heap, pai(idx));
    }
}



//Corrige estrutura do heap descendo o valor ao nivel adquado
void desceHeap(tipoHeap *heap, int idx) {
    int aux, idxFilho;

    //Vefirica se o indice possui ao menos um filho
    if ( (filhoEsq(idx) < heap->qtd ) || (filhoDir(idx) < heap->qtd) ) {
        //Verifica o caso do indice possuir os dois filhos
        if (filhoDir(idx) < heap->qtd) {
            //identifica qual filho tem maior valor, para que ele suba (se for o caso)
            if ( heap->vetHeap[filhoEsq(idx)] > heap->vetHeap[filhoDir(idx)] ) {
                idxFilho = filhoEsq(idx); //Maior valor é o esquerdo
            } else {
                idxFilho = filhoDir(idx); //Maior valor é o direito
            }
        } else { //para o caso de possuir apenas o filho esquerdo
            idxFilho = filhoEsq(idx);
        }

        //Verifica se ha necessidade de troca
        if (heap->vetHeap[idx] < heap->vetHeap[idxFilho]) {
            //Executa a troca de valores
            aux = heap->vetHeap[idx];
            heap->vetHeap[idx] = heap->vetHeap[idxFilho];
            heap->vetHeap[idxFilho] = aux;
            desceHeap(heap, idxFilho);
        }
    }
}



// HEAP sort
//Recebe como parametros o vetor com valores, o seu tamanho e a quantidade de valores
void heapSort(int vet[], int tamanho, int qtd) {
    tipoHeap heap;
    heap.qtd = 0;
    int i;

    // Constroi o heap para promover a ordenacao, inserindo os valores da lista
    for (i=0; i<qtd; i++) {
        insereHeap(&heap, vet[i]);
    }

    // Iterativamente, remove a raiz do heap promovendo a ordenacao
    while (heap.qtd > 0) {
        heap.vetHeap[heap.qtd-1] = removeRaizHeap(&heap);
    }

    // Copia o vetor do heap (ordenado) para o vetor
    for (i=0; i<qtd; i++) {
        vet[i] = heap.vetHeap[i];
    }
}
