//
// Created by florin on 4/14/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"

char buf[256];
int lung=0;

trieNode_t *trieInitNode() {
    trieNode_t *newNode = malloc(sizeof(trieNode_t));

    // Initializez toti copiii la NULL
    newNode->children = calloc(NUM_CHILDREN, sizeof(trieNode_t *));

    // Setez acest nod ca nefiind sfarsit de cuvant
    newNode->isWordTerminal = 0;

    // Setez parintele la NULL
    newNode->parent = NULL;

    return newNode;
}

void trieFreeNode(trieNode_t *node) {
    free(node->children);
    free(node);
}

void trieDestroy(trieNode_t **root) {
    if (*root == NULL) {
        return;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        trieDestroy(&(*root)->children[i]);
    }
    trieFreeNode(*root);
    *root = NULL;
}

int trieNodeIsLeaf(trieNode_t *node) {
    if (node == NULL) {
        return 1;
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            // Nodul are cel putin un copil
            return 0;
        }
    }
    // Nodul este frunza
    return 1;
}

void printNodeCharacters(trieNode_t *node) {
    if (node == NULL) {
        return;
    }

    printf("Nodul de la adresa %p are legaturi catre: ", node);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            printf("%c ", IDX_TO_CHAR(i));
        }
    }
    printf("\n");
}

void trieInsertWord(trieNode_t **root, char *word) {
    if(*root == NULL){
        *root = trieInitNode();
    }
    trieNode_t *aux = *root;
    while(word[0] != '\0'){
        if(aux->children[CHAR_TO_IDX(word[0])] != NULL){
            aux = aux->children[CHAR_TO_IDX(word[0])];
            word++;
            continue;
        }
        trieNode_t *node = trieInitNode();
        node->parent = aux;
        aux->children[CHAR_TO_IDX(word[0])] = node;
        aux = node;
        word++;
    }
    aux->isWordTerminal = 1;
    return;

    //-varianta recursiva
    // if((*root)==NULL){
    //     *root=trieInitNode();
    //     trieInsertWord(&(*root),word); 
    // }
    // if(word[1]!='\0'){
    //     if(&(*root)->children[CHAR_TO_IDX(word[0])] != NULL){
    //         trieInsertWord(&(*root)->children[CHAR_TO_IDX(word[0])],word+1);
    //     }else{
    //         (*root)->children[CHAR_TO_IDX(word[0])]=trieInitNode();
    //         (*root)->children[CHAR_TO_IDX(word[0])]->parent=*root;
    //         trieInsertWord(&(*root)->children[CHAR_TO_IDX(word[0])],word+1);
    //     }
    // }
    // else{
    //     (*root)->children[CHAR_TO_IDX(word[0])]=trieInitNode();
    //     (*root)->children[CHAR_TO_IDX(word[0])]->isWordTerminal=1;
    // }
}

int trieContainsWord(trieNode_t *root, char *word) {
    if(root == NULL)
        return 0;
    trieNode_t *node = root;
    while(word[0] != '\0'){
        if(node->children[CHAR_TO_IDX(word[0])] == NULL)
            return 0;
        node = node->children[CHAR_TO_IDX(word[0])];
        word++;
    }
    if(node->isWordTerminal == 1)
        return 1;
    return 0;


    //-recursivitate
    // if(root==NULL){
    //     return 0;
    // }else{
    //     if(root->children[CHAR_TO_IDX(word[0])]!=NULL) {
    //         if(word[1]!='\0'){
    //             trieContainsWord(root->children[CHAR_TO_IDX(word[0])],word+1);
    //         }else{
    //             if(root->children[CHAR_TO_IDX(word[0])]->isWordTerminal==1)
    //                 return 1;
    //             else return 0;
    //         }
            
    //     }else{
    //         return 0;
    //     }
    // }
}

void trieDeleteWord(trieNode_t **root, char *word) {
    if(root == NULL)
        return;
    
    trieNode_t *node = *root;

    while(word[0] != '\0'){
        if(node->children[CHAR_TO_IDX(word[0])] == NULL)
            return;
        node = node->children[CHAR_TO_IDX(word[0])];
        word++;
    }
    node->isWordTerminal = 0;
    node = node->parent;
    while(trieNodeIsLeaf(node)){
        trieNode_t *prev = node->parent;
        trieFreeNode(node);
        node = prev;
    }
}

void showAll(trieNode_t *root){
    if(root == NULL)
        return;
    if(root->isWordTerminal == 0)
        printf("%s\n", buf);
    for(int i = 0; i < NUM_CHILDREN; i++){
        buf[lung] = IDX_TO_CHAR(i);
        lung++;
        showAll(root->children[i]);
        lung--;
    }
}

void triePrefixMatching(trieNode_t *root, char *prefix) {
    if(root == NULL)
        return;
    while(*prefix != '\0'){
        if(root->children[CHAR_TO_IDX(*prefix)] == NULL)
            return;
        root = root->children[CHAR_TO_IDX(*prefix)];
        buf[lung] = *prefix;
        lung++;
        prefix = prefix+1;
    }
    showAll(root);
    // TODO
}
