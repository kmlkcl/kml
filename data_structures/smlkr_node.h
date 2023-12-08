#ifndef SMLKR_ENGINE_SMLKR_NODE_H
#define SMLKR_ENGINE_SMLKR_NODE_H

typedef struct SMLKR_Node_Linked {
    void *Node;
    SMLKR_Node_Linked *Next;
}SMLKR_Node_Linked;

typedef struct SMLKR_Node_Linked_Double {
    void *Node;
    SMLKR_Node_Linked_Double *Prev;
    SMLKR_Node_Linked_Double *Next;
}SMLKR_Node_Linked_Double;

SMLKR_Node_Linked *SMLKR_Node_Init_Linked(void *data);

SMLKR_Node_Linked_Double *SMLKR_Node_Init_Linked_Double(void *data);

#endif //SMLKR_ENGINE_SMLKR_NODE_H
