#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab05.h"
#include "list.h"
#include "stack.h"
#include "queue.h"


#define NUM_QUEUES 10

int checkBalancedBrackets(char *exp) {
    int lungime=strlen(exp);
    stack_t *stack=initList();
    int status;
    for(int i=0; i<lungime; i++){
        
        if(exp[i]=='(' || exp[i]=='{' || exp[i]=='['){
            push(stack,exp[i]);
        }
        else if(top(stack,&status)=='(' && exp[i]==')'){
            pop(stack,&status);
        }else if(top(stack,&status)=='{' && exp[i]=='}'){
            pop(stack,&status);
        }else if(top(stack,&status)=='[' && exp[i]==']'){
            pop(stack,&status);
        }else
            return 0;
        // print_list(stack);
    }
    if(stack->len!=0)
        return 0;
    return 1;
    /*
     * TODO Exercitiul 3
     */
    return 0;
}

void radixSort(int *v, int n) {
    queue_t **vect=malloc(10*sizeof(queue_t*));     
    for(int i=0; i<10; i++){
       vect[i]=initList();
    }
    int max=0;
    for(int i=0; i<n; i++)
        if(max<v[i])
            max=v[i];
    int ct=0;
    while(max){
        ct++;
        max=max/10;
    }
    int impartit=1;
    for(int k=0; k<ct; k++){
        for(int i=0; i<n; i++){
            if(v[i]<impartit){
                enqueue(vect[0],v[i]);
            }else{
                int cifra=(v[i]/impartit)%10;
                enqueue(vect[cifra],v[i]);
            }
        }
        int status,j=0;
        for(int i=0; i<10; i++){
            status=0;
            while(status==0){
                int nr=dequeue(vect[i],&status);
                if(status==0){
                    v[j]=nr;
                        j++;
                }
            }
        }
        impartit*=10;
    }
    /*
     * TODO Exercitiul 4
     */
}
