#ifndef __QUEUE__H__
#define __QUEUE__H__

/* Définition du type Booléen */
typedef enum{
    false,
    true
}Bool;

/* Définition d'une file */
typedef struct QueueElement{
    int value;
    struct QueueElement *next;
}QueueElement, *Queue;

/* Paramètres de la file */
static QueueElement *first = NULL;
static QueueElement *last = NULL;
static int nbElement = 0;

/* Prototypes */
Bool isEmptyQueue(void);
int queueLenght(void);
int queueFirst(void);
int queueLast(void);
void printQueue(void);
void pushQueue(int x);
void popQueue(void);
void clearQueue(void);

#endif