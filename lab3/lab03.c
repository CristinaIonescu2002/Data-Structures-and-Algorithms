#include <stdio.h>
#include <stdlib.h>

#include "lab03.h"

void print_list_int(sl_list_t *list)
{
    node_t *aux = list->head;

    printf("%-20s", "Lista construita:");

    while (aux->next != NULL) {
        printf("%d->", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

node_t *init_node(const int *value) // initializeaza un nod din lista
{ 
    node_t *aux = malloc (sizeof(*aux));
    aux->data = value;
    aux->next = NULL;
    return aux;
}

void free_node(node_t *node) //elibereaza memoria ocupata de un nod din lista
{
    free(node->data);
    free(node);
}

sl_list_t *init_list() // initializeaza o lista vida
{
    sl_list_t *list = malloc (sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

void destroy_list(sl_list_t *list) // elibereaza memoria ocupata de lista. Daca lista nu este vida, se vor elimina nodurile existente
{
    if(list->head == NULL){ //lista vida
        free(list);
        return;
    }
    node_t *aux, *auxx;
    aux = list->head;
    while(aux != NULL){
            auxx = aux->next;
            free_node(aux);
            aux = auxx;
    }
    free(list);
}

int insert_node(sl_list_t *list, int value, uint position)
{
// insereaza un nod cu o valoare primita ca parametru la o pozitie data. Daca pozitia la care se doreste inserarea 
// nu este valida, nu se insereaza niciun nou element ın lista si se returneaza codul de eroare -1.
    node_t *ante, *aici;
    *aici = init_node(value);
    if(position < 0 || position > list->len - 1){
        return -1;
    }
    if(position == 0 && list.len == 0{ //lista vida
        list->head = aici;
        list->tail = aici;
        aici->next = NULL;
        list->len ++;
        return 0;
    }
    if(position == 0){
        aici->next = list->head;
        list->head = aici;
        list->len ++;
        return 0;
    }
    if(position == list->len - 1){
        aici->next = NULL;
        list->tail = aici;
        list->len ++;
        return 0;
    }
    else{
        ante = list->head;
        int i;
        for(i = 0; i < position - 1; i++){
            ante = ante->next;
        }
        aici->next = ante->next;
        ante->next = aici;
        list->len ++;
        return 0;
    }
    return 0;
}

int remove_node_by_key(sl_list_t *list, int value) // cauta primul nod din lista ce contine valoarea data ca
// parametru si ıl elimina. Daca acel element nu exista, se va ıntoarce codul de eroare -1.
{
    node_t *ante;
    node_t *aici;
    aici = list->head;
    while(aici != NULL){ // parcurgere
        if(*aici->data == value) break;
        ante = aici;
        aici = aici->next;
    }
    if(aici == list->tail && *list->tail->data != value) return -1;
    if(aici == list->tail && *list->tail->data == value){
        free_node(aici);
        list->tail = ante;
        list->tail->next = NULL;
        list->len --;
        return 0;
    }
    if(ante == NULL){
        node_t *aux = list->head;
        list->head = list->head->next;
        free_node(aux);
        list->len --;
        return 0;
    }
    ante->next = aici->next;
    free_node(aici);
    list->len --;
    return 0;
}

int remove_node_at_position(sl_list_t *list, uint position)
{
    if(position < 0 || position > list->len - 1)
        return -1;
    if(position == 0){
        node_t *aux = list->head;
        list->head = list->head->next;
        free_node(aux);
        list->len --;
        return 0;
    }
    
    node_t *aici = list->head;
    node_t *ante = NULL;
    for(int i = 0; i < position; i++){
        ante = aici;
        aici = aici->next;
    }
    if(aici == list->tail){
        list->tail = ante;
        list->tail->next = NULL;
        free_node(aici);
        list->len --;
        return 0;
    }
    list->len --;
    ante->next = aici->next;
    free_node(aici);
    return 0;
}

int cyclic_search(sl_list_t *list, int k)
{
    if(k > 0 && k >= list->len)
        k = k % list->len;
    while(k < 0)
        k = k + list->len;

    node_t *aux = list->head;
    for(int i = 0; i < k; i++) aux = aux->next;
    return *aux->data;
}