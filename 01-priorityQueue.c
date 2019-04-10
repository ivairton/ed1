/**
 * Universidade Federal de Mato Grosso - UFMT
 * Campus Universitário do Araguaia
 * Instituto de Ciências Exatas e da Terra - ICET
 * Curso de Bacharelado em Ciência da Computação
 *
 * Course: 'Estrutura de Dados I'
 * Professor: PhD Ivairton Monteiro Santos
 *
 * Last version: April, 10 - 2019
 * Repository: https://github.com/ivairton/ed1
 * Project under GPL 3.0v Licence
 *
 * Description: Development of priority queue data structure using static memory strategie.
 *
 */

// Libraries
#include<stdio.h>
#include<stdlib.h>

// Constant definition
#define N 100

// Data structure definition
struct dataStruct {
    int value;
    int prio;
};
typedef struct dataStruct dataType;

// Queue structure definition
struct queueStruct {
    dataType queue[N];
    int quantity;
};
typedef struct queueStruct queueType;

// Functions prototype
void initQueue(queueType*);
void addQueue(queueType*, dataType);
dataType removeQueue(queueType*);
dataType firstQueue(queueType);
int quantityQueue(queueType);
void printQueue(queueType);


// MAIN FUNCTION
// To test queue data structure
int main(int argc, char *argv[]) {
    queueType queue;
    initQueue(&queue);

    dataType dt;

    dt.value = 10;
    dt.prio = 5;
    addQueue(&queue, dt);

    dt.value = 20;
    dt.prio = 8;
    addQueue(&queue, dt);

    dt.value = 30;
    dt.prio = 2;
    addQueue(&queue, dt);

    dt.value = 40;
    dt.prio = 2;
    addQueue(&queue, dt);

    dt = removeQueue(&queue);
    printf("Value removed from queue = %d(%d)\n", dt.value, dt.prio );
    printf("First value from queue = %d\n", firstQueue(queue).value );
    printf("Queue has %d datas\n", quantityQueue(queue) );
    printQueue(queue);

    return 1;
}


// Function that init queue structure
void initQueue(queueType* q){
    q->quantity = 0;
}

// Function that add a new value in queue using priority information
void addQueue(queueType *q, dataType dt) {
    int i;
    //Check if queue is not full
    if ( (q->quantity) < N ) {
        //Check if queue is emptry, in this case add new value on zero position
        if ( q->quantity == 0 ) {
            q->queue[q->quantity++] = dt;
        } else {
            //Add new value in a adequate position, using priority information
            i = q->quantity;
            while ( (i > 0) && (q->queue[i-1].prio > dt.prio) ) {
                //move value in queue to add new one
                q->queue[i] = q->queue[i-1];
                i--;
            }
            q->queue[i] = dt;
            q->quantity++;
        }
    }
}

// Remove the first value and return than
dataType removeQueue(queueType* q) {
    int i;
    dataType dt;

    //Check if queue is not emptry
    if ( q->quantity > 0 ) {
        dt = q->queue[0]; //record the firts value
        //move the orther values
        for (i=0; i < (q->quantity-1); i++) {
            q->queue[i] = q->queue[i+1];
        }
        q->quantity--; //counter decrement
        return dt; //return the old first value, recorded at the function first time
    } else {
        /*LOGICAL IMPRECISION: The queue is empty but returns -1 value. The ideal
        return is NULL, but is necessary that function work with pointers. This
        method is TO DO.*/
        dt.value = -1;
        dt.prio = -1;
        return dt;
    }
}

// Function that return the first value from queue
dataType firstQueue(queueType q) {
    return q.queue[0];
}

// Function that return the quantity of datas from queue
int quantityQueue(queueType q) {
    return q.quantity;
}

// Function that print the queue structure. It is useful to debug structure development.
void printQueue(queueType q) {
    int i;
    printf("Queue: ");
    for (i=0; i < quantityQueue(q); i++ ){
        printf("[%d|%d]", q.queue[i].value, q.queue[i].prio);
    }
    printf(" (Quantity of datas = %d)\n", quantityQueue(q) );
}
