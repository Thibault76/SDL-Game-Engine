#include <stdio.h>
#include "engine/dataStructure/linkedList.h"

int main(int argv, char **args){
    
    CeosLinkedList *list;

    list = CeosLinkedListCreate(true, 2, 5);
    CeosLinkedListDisplayPoolSize(list);

    CeosLinkedListInsertLast(list, 8);
    CeosLinkedListDisplayPoolSize(list);
    CeosLinkedListInsertLast(list, 7);
    CeosLinkedListDisplayPoolSize(list);
    CeosLinkedListInsertLast(list, 6);
    CeosLinkedListDisplayPoolSize(list);

    CeosLinkedListDisplayForwardInt(list);

    _sleep(10000);

    CeosLinkedListDeleteLast(list);
    CeosLinkedListDisplayForwardInt(list);
    CeosLinkedListDisplayPoolSize(list);
    CeosLinkedListDeleteLast(list);
    CeosLinkedListDisplayForwardInt(list);
    CeosLinkedListDisplayPoolSize(list);
    CeosLinkedListDeleteLast(list);

    CeosLinkedListDisplayForwardInt(list);
    CeosLinkedListDisplayPoolSize(list);


    list = CeosLinkedListFree(list);

    _sleep(60000);

    return EXIT_SUCCESS;
}