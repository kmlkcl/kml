#include <cstdlib>
#include <cstring>
#include "smlkr_linked_list.h"
#include "smlkr_node.h"


inline SMLKR_Node_Linked* Disconnect(SMLKR_LinkedList* LinkedList, size_t index);


SMLKR_LinkedList* SMLKR_LinkedList_Init() {
    SMLKR_LinkedList* LinkedList = (SMLKR_LinkedList *)malloc(sizeof(SMLKR_LinkedList));

    LinkedList->Head = NULL;
    LinkedList->Size = 0;
    return LinkedList;
}

void SMLKR_LinkedList_AddNode_Head(SMLKR_LinkedList* LinkedList, void* data) {
    SMLKR_Node_Linked* LinkedNode = SMLKR_Node_Init_Linked(data);

    if (LinkedList->Size == 0) {
        LinkedList->Head = LinkedNode;
        LinkedList->Size += 1;
        return;
    }

    LinkedNode->Next = LinkedList->Head;
    LinkedList->Head = LinkedNode;
    LinkedList->Size += 1;
}

void SMLKR_LinkedList_AddNode_After(SMLKR_LinkedList* LinkedList, void* data, const size_t index) {

    SMLKR_Node_Linked* FoundNode = SMLKR_LinkedList_Get(LinkedList, index);
    SMLKR_Node_Linked* NextNode = FoundNode->Next;
    SMLKR_Node_Linked* NewNode = SMLKR_Node_Init_Linked(data);

    if (NextNode != NULL) {
        NewNode->Next = NextNode;
    }
    FoundNode->Next = NewNode;

    LinkedList->Size += 1;
}

void SMLKR_LinkedList_AddNode_Tail(SMLKR_LinkedList* LinkedList, void* data) {
    SMLKR_Node_Linked* LinkedNode = SMLKR_Node_Init_Linked(data);

    if (LinkedList->Size == 0) {
        LinkedList->Head = LinkedNode;
        LinkedList->Size += 1;
        return;
    }

    SMLKR_Node_Linked* LastNode = SMLKR_LinkedList_Get(LinkedList, LinkedList->Size - 1);
    LastNode->Next = LinkedNode;
    LinkedList->Size += 1;
}

SMLKR_Node_Linked* SMLKR_LinkedList_Get(const SMLKR_LinkedList* LinkedList, const size_t index) {

    int current = 0;
    SMLKR_Node_Linked* CurrentNode = LinkedList->Head;

    while (current < index) {
        CurrentNode = CurrentNode->Next;
        current++;
    }

    return CurrentNode;
}

void SMLKR_LinkedList_Destroy(SMLKR_LinkedList* LinkedList) {
    SMLKR_Node_Linked* CurrentNode = LinkedList->Head;

    while (CurrentNode != NULL) {
        SMLKR_Node_Linked* nextNode = CurrentNode->Next;
        free(CurrentNode->Node);
        free(CurrentNode);

        CurrentNode = nextNode;
    }

    free(LinkedList);
}

void* SMLKR_LinkedList_PullAt(SMLKR_LinkedList* LinkedList, const size_t index) {
    SMLKR_Node_Linked* Current = Disconnect(LinkedList, index);
    void* data = Current->Node;
    free(Current);

    return data;
}

void SMLKR_LinkedList_DestroyAt(SMLKR_LinkedList* LinkedList, const size_t index) {
    SMLKR_Node_Linked* linked_node = Disconnect(LinkedList, index);
    free(linked_node->Node);
    free(linked_node);
}

SMLKR_Node_Linked* Disconnect(SMLKR_LinkedList* LinkedList, const size_t index) {

    SMLKR_Node_Linked* Previous = index == 0 ? NULL : SMLKR_LinkedList_Get(LinkedList, index - 1);
    SMLKR_Node_Linked* Current = index == 0 ? LinkedList->Head : Previous->Next;

    if (Previous == NULL) {
        LinkedList->Head = Current->Next;
    }
    else {
        Previous->Next = Current->Next;
    }
    LinkedList->Size -= 1;
    return Current;
}


bool SMLKR_LinkedList_IsEqual(const SMLKR_LinkedList&x, const SMLKR_LinkedList&y, const size_t dataSize) {
    if (x.Size != y.Size) {
        return false;
    }
    const SMLKR_Node_Linked* xCurrent = x.Head;
    const SMLKR_Node_Linked* yCurrent = y.Head;

    while (xCurrent != NULL) {
        if (memcmp(xCurrent->Node, yCurrent->Node, dataSize) != 0) {
            return false;
        }
        xCurrent = xCurrent->Next;
        yCurrent = yCurrent->Next;
    }
    return true;
}