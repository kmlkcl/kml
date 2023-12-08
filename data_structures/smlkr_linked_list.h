#ifndef SMLKR_ENGINE_SMLKR_LINKED_LIST_H
#define SMLKR_ENGINE_SMLKR_LINKED_LIST_H

#include <stddef.h> //This is not redundant.
#include "smlkr_node.h"

typedef struct SMLKR_LinkedList {
    SMLKR_Node_Linked* Head;
    size_t Size;
} SMLKR_LinkedList;

/**
 * Initializes a single linked list
 */
SMLKR_LinkedList* SMLKR_LinkedList_Init();

/**
 * Adds a node to specified single linked lists tail
 * @param LinkedList
 * @param data
 */
void SMLKR_LinkedList_AddNode_Tail(SMLKR_LinkedList* LinkedList, void* data);

/**
 * Adds a node to specified single linked lists head
 * @param LinkedList
 * @param data
 */
void SMLKR_LinkedList_AddNode_Head(SMLKR_LinkedList* LinkedList, void* data);

/**
 * Add a new node index the specified index
 * @param LinkedList
 * @param data
 * @param index
 */
void SMLKR_LinkedList_AddNode_After(SMLKR_LinkedList* LinkedList, void* data, size_t index);

//TODO: Implement SMLKR_LinkedList_AddNode_Before
/**
 * Gets the element at current index from the single linked list
 * @param LinkedList
 * @param index
 * @return
 */
SMLKR_Node_Linked* SMLKR_LinkedList_Get(const SMLKR_LinkedList* LinkedList, size_t index);

/**
 * Pulls an elements data from the linked list. But it does not destroy the data.
 * @param LinkedList
 * @param index
 * @return
 */
void* SMLKR_LinkedList_PullAt(SMLKR_LinkedList* LinkedList, size_t index);

void SMLKR_LinkedList_DestroyAt(SMLKR_LinkedList* LinkedList, size_t index);

/**
 * Destroys the linked list
 */
void SMLKR_LinkedList_Destroy(SMLKR_LinkedList* LinkedList);


void SMLKR_LinkedList_Test();

bool SMLKR_LinkedList_IsEqual(const SMLKR_LinkedList&x, const SMLKR_LinkedList&y, size_t dataSize);

inline void SMLKR_LinkedList_Log(const SMLKR_LinkedList* LinkedList);

#endif //SMLKR_ENGINE_SMLKR_LINKED_LIST_H
