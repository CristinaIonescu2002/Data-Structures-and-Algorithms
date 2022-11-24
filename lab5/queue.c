#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void enqueue(queue_t *queue, int value) {
    if (queue->len==0){
        node_t *nod=initNode(value);
        queue->head=nod;
        queue->tail=nod;
        queue->len++;
    }
    else{
        node_t *nod=initNode(value);
        nod->next=queue->head;
        queue->head->prev=nod;
        queue->head=nod;
        queue->len++;
    }
    /*
     * TODO
     *      Adauga un nou element in coada
     *      - Daca nu exista elemente in coada se seteaza atat 'head', cat si 'tail' ca fiind noul nod
     *      - Altfel, se introduce noul element la inceput de lista
     */
}

int dequeue(queue_t *queue, int *status) {
    if(queue->len==0){
        (*status)=1;
        return 33;
    }else if(queue->len==1){
        int val=queue->head->data;
        free(queue->head);
        queue->head=NULL;
        queue->tail=NULL;
        queue->len--;
        (*status)=0;
        return val;
    }else{
        int val=queue->tail->data;
        node_t *aux=queue->tail;
        queue->tail=aux->prev;
        queue->tail->next=NULL;
        queue->len--;
        free(aux);
        (*status)=0;
        return val;
    }
    /*
     * TODO
     *      Elimina elementul de la sfarsitul cozii
     *      - Daca nu exista elemente in coada:
     *          - Se seteaza statusul pe valoarea STATUS_ERR (1)
     *          - Se returneaza orice valoare
     *      - Altfel:
     *          - Se copiaza valoarea nodului
     *          - Se seteaza statsul pe valoarea STATUS_OK (0)
     *          - Se returneaza valoarea nodului
     */
    return 0;
}

int peek(queue_t *queue, int *status) {
    if(queue->len==0){
        (*status)=1;
        return 33;
    }else{
        (*status)=0;
        return queue->tail->data;
    }
    /*
     * TODO
     *      Afiseaza valoarea elementului de la sfarsitul cozii
     *      - Daca nu exista elemente in coada:
     *          - Se seteaza status pe valoarea STATUS_ERR (1)
     *          - Se returneaza orice
     *      - Altfel:
     *          - Se seteaza statusul pe valoarea STATUS_OK (0)
     *          - Se returneaza campul 'data' al ultimului nod din coada
     */
    return 0;
}
