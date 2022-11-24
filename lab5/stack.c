#include <stdlib.h>
#include "stack.h"

void push(stack_t *stack, int value) {
    if(stack->len==0){
        node_t *nod=initNode(value);
        stack->tail=nod;
        stack->head=nod;
        stack->len++;
    }else{
        node_t *nod=initNode(value);
        nod->next=stack->head;
        stack->head->prev=nod;
        stack->head=nod;
        stack->len++;
    }
    
    /*
     * TODO
     *      Se adauga un nou nod cu valoarea data
     *      ca parametru la inceputul listei
     */
}

int pop(stack_t *stack, int *status) {
    if(stack->len==0){
        (*status)=1;
        return 33;
    }else{
        (*status)=0;
        int val=stack->head->data;
        node_t *aux=stack->head;
        stack->head=aux->next;
        stack->len--;
        free(aux);
        return val;
    }
    /*
     * TODO
     *      Se elimina nodul din varful stivei si i se returneaza valoarea
     *          - Daca stiva este goala, se seteaza parametrul 'status' la valoarea STATUS_ERR (1)
     *          - Altfel, se seteaza parametrul 'status' la valoarea STATUS_OK (0)
     */
    return 0;
}

int top(stack_t *stack, int *status) {
    if(stack->len==0){
        (*status)=1;
        return 33;
    }else{
        (*status)=0;
        return stack->head->data;
    }
    /*
     * TODO
     *      Se returneaza valoarea nodul din varful stivei
     *          - Daca stiva este goala, se seteaza parametrul 'status' la valoarea STATUS_ERR (1)
     *          - Altfel, se seteaza parametrul 'status' la valoarea STATUS_OK (0)
     */
    return 0;
}
