#include <stdlib.h>
#include "smlkr_node.h"


SMLKR_Node_Linked* SMLKR_Node_Init_Linked(void* data) {
    SMLKR_Node_Linked* LinkedNode = (SMLKR_Node_Linked*) malloc(sizeof(SMLKR_Node_Linked));


    LinkedNode->Node = data;
    LinkedNode->Next = NULL;
    return LinkedNode;
}

SMLKR_Node_Linked_Double* SMLKR_Node_Init_Linked_Double(void* data) {
    SMLKR_Node_Linked_Double* LinkedDoubleNode = (SMLKR_Node_Linked_Double*)malloc(sizeof(SMLKR_Node_Linked_Double));

    LinkedDoubleNode->Node = data;
    LinkedDoubleNode->Prev = NULL;
    LinkedDoubleNode->Next = NULL;
    return LinkedDoubleNode;
}