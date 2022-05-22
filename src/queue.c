#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Bool isEmptyQueue(void){
    if(first == NULL && last == NULL)
        return true;

    return false;
}

/*--------------------------------------------*/

int queueLenght(void){
    return nbElement;
}

/*--------------------------------------------*/

int queueFirst(void){
    if(isEmptyQueue())
        exit(1);
    
    return first->value;
}

/*--------------------------------------------*/

int queueLast(void){
    if(isEmptyQueue())
        exit(1);
    
    return last->value;
}

/*--------------------------------------------*/

void printQueue(void){
    if(isEmptyQueue()){
        printf("Rien a afficher, la file est vide.\n");
        return;
    }

    QueueElement *temp = first;

    while(temp != NULL){
        printf("[%d] ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

/*--------------------------------------------*/

void pushQueue(int x){
    QueueElement *element;

    element = malloc(sizeof(*element));

    if(element == NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique\n");
        exit(EXIT_FAILURE);
    }

    element->value = x;
    element->next = NULL;

    if(isEmptyQueue()){
        first = element;
        last = element;
    } else {
        last->next = element;
        last = element;
    }

    nbElement++;
}

/*--------------------------------------------*/

void popQueue(void){
    if(isEmptyQueue()){
        printf("Rien a retirer, la file est deja vide.\n");
        return;
    }

    QueueElement *temp = first;

    if(first == last){
        first = NULL;
        last = NULL;
    } else
        first = first->next;

    free(temp);
    nbElement--;
}

/*--------------------------------------------*/

void clearQueue(void){
    if(isEmptyQueue()){
        printf("Rien a nettoyer, la file est deja vide.\n");
        return;
    }

    while(!isEmptyQueue())
        popQueue();
}