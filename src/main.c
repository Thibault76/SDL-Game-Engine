#include <stdio.h>
#include "engine/dataStructure/linked_list.h"

int main(int argv, char **args){
    
    CeosLinkedList *list;

    list = CeosLinkedListCreate();

    CeosLinkedListInsertLast(list, 8);
    CeosLinkedListInsertLast(list, 7);
    CeosLinkedListInsertLast(list, 6);

    CeosLinkedListDisplayForwardInt(list);

    CeosLinkedListDeleteLast(list);
    CeosLinkedListDisplayForwardInt(list);
    CeosLinkedListDeleteLast(list);
    CeosLinkedListDisplayForwardInt(list);
    CeosLinkedListDeleteLast(list);

    CeosLinkedListDisplayForwardInt(list);


    list = CeosLinkedListFree(list);

    return EXIT_SUCCESS;
}