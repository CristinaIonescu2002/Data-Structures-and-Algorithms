//
// Created by florin on 3/22/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "lab04.h"

node_t * init_node(int *value) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = malloc(sizeof(int));
    *new_node->data = *value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

list_t *init_list() {
    list_t *new_list = malloc(sizeof(list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;
    return new_list;
}

void free_node(node_t *nod)
{
    free(nod->data);
    free(nod);
}

void destroy_list(list_t *list) {
    node_t *aux;
    /* Se sterg toate nodurile din lista, incepand de la coada */
    while (list->len > 0) {
        aux = list->tail;                   // Se retine un pointer catre ultimul nod din lista
        list->tail = list->tail->prev;      // Se muta pointerul cozii cu un nod mai in spate
        free_node(aux);                // Se elibereaza memoria ocupata de nodul eliminat
        --list->len;                        // Se decrementeaza lungimea listei
    }
    /* Se elibereaza memoria ocupata de structura listei */
    free(list);
}

void print_list(list_t *list) {
    node_t *aux = list->head;

    printf("%-25s", "Lista construita (->):");

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux != list->tail) {
        printf("%d -> ", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

void print_list_reversed(list_t *list) {
    node_t *aux = list->tail;
    printf("%-25s", "Lista construita (->):");
    if(aux == NULL){
        printf("NULL\n");
        return;
    }
    while(aux != list->head){
        printf("%d -> ", *aux->data);
        aux = aux->prev;
    }
    printf("%d\n", *aux->data);
    /* TODO 1.a.
     * Se va porni de la ultimul nod din lista si se va parcurge lista
     * pana cand se va ajunge la primul nod
     */
}

int insert_node(list_t *list, int value, int position) {
    if(position<0 || position>list->len)
        return -1;
    if(list->head==NULL){
        node_t *node=init_node(&value);
        list->head=node;
        list->tail=node;
        list->len=1;
    }
    else if(position==0){
        node_t *node=init_node(&value);
        node->next=list->head;
        list->head->prev=node;
        list->head=node;
        list->len++;
    }
    else if(position==list->len){
        node_t *node=init_node(&value);
        node->prev=list->tail;
        list->tail->next=node;
        list->tail=node;
        list->len++;
    }
    else{
        if(position<=list->len/2){
            node_t *aux=list->head;
            for(int i=0; i<position-1; i++)
                aux=aux->next;
            node_t *nod=init_node(&value);
            nod->next=aux->next;
            aux->next->prev=nod;
            nod->prev=aux;
            aux->next=nod;
            list->len++;
        }
        else{
            node_t *aux=list->tail;
            for(int i=list->len-1; i>position; i--)
                aux=aux->prev;
            node_t *nod=init_node(&value);
            nod->prev=aux->prev;
            aux->prev->next=nod;
            nod->next=aux;
            aux->prev=nod;
            list->len++;
        }
    }
    /* TODO 1.b.
     * Se vor trata urmatoarele cazuri:
     *  - Pozitia nu este in intervalul [0, len] => return -1
     *  - Inserarea se face intr-o lista vida
     *  - Inserarea se face la inceputul listei
     *  - Inserarea se face la sfarsitul listei
     *  - Inserarea se face intr-o pozitie intermediara:
     *      - Pozitia este mai aproape de inceputul listei => parcurgerea se va face de la inceputul listei
     *      - Pozitia este mai aproape de sfarsitul listei => parcurgerea se va face de la sfarsitul listei
     */
    return 0;
}

int remove_node(list_t *list, int position) {
    if(position<0 || position>=list->len)
        return -1;
    if(position==0){
        node_t *aux;
        aux=list->head;
        list->head=aux->next;
        list->head->prev=NULL;
        list->len--;
        free(aux);
    }
    else if(position==list->len-1){
        node_t *aux;
        aux=list->tail;
        list->tail=aux->prev;
        list->tail->next=NULL;
        list->len--;
        free(aux);
    }
    else{
        if(position<=list->len/2){
            node_t *aux=list->head;
            for(int i=0; i<position-1; i++)
                aux=aux->next;
            node_t *nod=aux->next;
            nod->next->prev=aux;
            aux->next=nod->next;
            free(nod);
            list->len--;
            
        }
        else{
            node_t *aux=list->tail;
            for(int i=list->len-1; i>position; i--)
                aux=aux->prev;
            node_t *nod=aux->prev;
            nod->prev->next=aux;
            aux->prev=nod->prev;
            free(nod);
            list->len--;
            
        }
    }
    /* TODO 1.c.
     * Se vor trata urmatoarele cazuri:
     *  - Pozitia nu este in intervalul [0, len - 1] sau lista este vida (len == 0) => return -1
     *  - Stergerea se face de la inceputul listei
     *  - Stergerea se face de la sfarsitul listei
     *  - Stergerea se face dintr-o pozitie intermediara:
     *      - Pozitia este mai aproape de inceputul listei => parcurgerea se va face de la inceputul listei
     *      - Pozitia este mai aproape de sfarsitul listei => parcurgerea se va face de la sfarsitul listei
     */
    return 0;
} 
int insert_sorted_desc(list_t *list, int value) {
    if(list->head==NULL){
        node_t *nod=init_node(&value);
        list->head=nod;
        list->tail=nod;
        list->len++;
    }
    else if(*list->head->data < value){
        insert_node(list,value,0);
    }
    else if(*list->tail->data > value){
        insert_node(list,value,list->len);
    }
    else{
        node_t *nod=list->tail;
        while(*nod->data < value)
            nod=nod->prev;
        node_t *aux=init_node(&value);
        aux->next=nod->next;
        aux->prev=nod;
        nod->next->prev=aux;
        nod->next=aux;
        list->len++;
    }
    /* TODO 2
     * Se vor trata urmatoarele cazuri:
     *  - Lista este vida
     *  - Inserarea se face la inceputul listei
     *  - Inserarea se face la sfarsitul listei
     */
    return 0;
}
list_t *remove_duplicates(list_t *list) {
    list_t *new_list = init_list();
    for(node_t *aux=list->head; aux !=NULL; aux=aux->next){
        int val=*aux->data;
        for(node_t *aux2=aux->next; aux2 != NULL; aux2=aux2->next){
            int val2=*aux2->data;
            if(val<val2){
                *aux->data=val2;
                *aux2->data=val;
                int ct;
                ct=val2;
                val2=val;
                val=ct;
            }
        }
    }
    node_t *aux=list->head;
    insert_node(new_list,*aux->data,0);
    for(aux=list->head->next; aux != NULL; aux=aux->next){
        if(*aux->data != *aux->prev->data)
            insert_node(new_list,*aux->data,new_list->len);
    }
    /*
     * TODO 3
     * Pornind de la lista primita ca parametru, se construieste
     * o noua lista care va contine doar valori unicat.
     * Lista finala va fi sortata descrescator
     */
    return new_list;
}
