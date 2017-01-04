/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 11, 2016
 * Filename:        circularList.h
 *
 * Overview:
 * This is the circular linked list header file
 ************************************************************/

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#ifndef TYPE
#define TYPE double
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

struct CircularList;

struct CircularList* circularListCreate();
void circularListDestroy(struct CircularList* list);
void circularListPrint(struct CircularList* list);
void circularListReverse(struct CircularList* list);

/* Deque interface */
void circularListAddFront(struct CircularList* list, TYPE value);
void circularListAddBack(struct CircularList* list, TYPE value);
TYPE circularListFront(struct CircularList* list);
TYPE circularListBack(struct CircularList* list);
void circularListRemoveFront(struct CircularList* list);
void circularListRemoveBack(struct CircularList* list);
int circularListIsEmpty(struct CircularList* list);

#endif
