/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 11, 2016
 * Filename:        linkedList. 
 *
 * Overview:
 * This is the linked list implementation file
 ************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Link
{
    TYPE value;    // link value
    struct Link* next;    // pointer to next link
    struct Link* prev;    // pointer to previous link
};

struct LinkedList
{
    int size;    // size of linked list
    struct Link* frontSentinel;    // pointer to front sentinel
    struct Link* backSentinel;    // pointer to back sentinel
};


/* ************************************************************************
	Helper Functions
 ************************************************************************ */

/***********************************************************
 * init: allocates the list's sentinel and sets the size 
 * to 0. The sentinel's next and prev should point to 
 * each other or NULL as appropriate.
 *
 * parameters: pointer to linked list struct.
 * returns: none.
 ***********************************************************/

static void init(struct LinkedList* list)
{
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel);
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;
    list->size = 0;
}


/***********************************************************
 * addLinkBefore: adds a new link with the given value
 * before the given link and increments the list's size.
 *
 * parameters: pointer to linked list struct, given link,
 * given value.
 * returns: none.
 ***********************************************************/

static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    struct Link* newLink = malloc(sizeof(struct Link));
    assert(newLink != 0);
    newLink->value = value;
    newLink->next = link;
    newLink->prev = link->prev;
    link->prev = newLink;
    newLink->prev->next = newLink;
    list->size++;
}


/***********************************************************
 * removeLink: removes the given link frm the list and 
 * decrements the list's size.
 *
 * parameters: pointer to linked list struct, given link.
 * returns: none.
 ***********************************************************/

static void removeLink(struct LinkedList* list, struct Link* link)
{
    assert(!linkedListIsEmpty(list));
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(link);
    list->size--;
}


/* ************************************************************************
	Linked List Functions
 ************************************************************************ */

/***********************************************************
 * linkedListCreate: allocates and initializes a list.
 *
 * parameters: none.
 * returns: pointer to linked list struct.
 ***********************************************************/

struct LinkedList* linkedListCreate()
{
    struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
    init(newDeque);
    return newDeque;
}


/***********************************************************
 * linkedListDestroy: deallocates every link in the list
 * including the sentinels, and frees the list itself.
 *
 * parameters: pointer to linked list struct.
 * returns: none.
 ***********************************************************/

void linkedListDestroy(struct LinkedList* list)
{
    while (!linkedListIsEmpty(list))
    {
        linkedListRemoveFront(list);
    }
    free(list->frontSentinel);
    free(list->backSentinel);
    free(list);
}


/***********************************************************
 * linkedListPrint: prints the values of the links in the 
 * deque from front to back.
 *
 * parameters: pointer to linked list struct.
 * returns: none.
 ***********************************************************/

void linkedListPrint(struct LinkedList* list)
{
    struct Link *current;
    assert(list != 0);
    assert(list->size != 0);
    current = list->frontSentinel->next;
    while(current != list->backSentinel)
    {
        printf("%i", current->value);
        current = current->next;
    }
}


/* ************************************************************************
	Deque Interface Functions
 ************************************************************************ */


/***********************************************************
 * linkedListIsEmpty: returns 1 if the deque is empty and 
 * 0 otherwise.
 *
 * parameters: pointer to linked list struct.
 * returns: int.
 ***********************************************************/

int linkedListIsEmpty(struct LinkedList* list)
{
    return list->size == 0;
}


/***********************************************************
 * linkedListAddFront: adds a new link with the given value
 * to the front of the deque.
 *
 * parameters: pointer to linked list struct, given value.
 * returns: none.
 ***********************************************************/

void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list, list->frontSentinel->next, value);
}


/***********************************************************
 * linkedListAddBack: adds a new link with the given value
 * to the back of the deque.
 *
 * parameters: pointer to linked list struct, given value.
 * returns: none.
 ***********************************************************/

void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list, list->backSentinel, value);
}


/***********************************************************
 * linkedListFront: returns the value of the link at the
 * front of the deque.
 *
 * parameters: pointer to linked list struct.
 * returns: front link value.
 ***********************************************************/

TYPE linkedListFront(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    return list->frontSentinel->next->value;
}


/***********************************************************
 * linkedListBack: returns the value of the link at the
 * back of the deque.
 *
 * parameters: pointer to linked list struct.
 * returns: back link value.
 ***********************************************************/

TYPE linkedListBack(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    return list->backSentinel->prev->value;
}


/***********************************************************
 * linkedListRemoveFront: removes the link at the front
 * of the deque.
 *
 * parameters: pointer to linked list struct.
 * returns: none.
 ***********************************************************/

void linkedListRemoveFront(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    removeLink(list, list->frontSentinel->next);
}


/***********************************************************
 * linkedListRemoveBack: removes the link at the back
 * of the deque.
 *
 * parameters: pointer to linked list struct.
 * returns: none.
 ***********************************************************/

void linkedListRemoveBack(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    removeLink(list, list->backSentinel->prev);
}


/* ************************************************************************
	Bag Interface Functions
 ************************************************************************ */

/***********************************************************
 * linkedListAdd: adds a link with the given value to the bag.
 *
 * parameters: pointer to linked list struct, given value.
 * returns: none.
 ***********************************************************/

void linkedListAdd(struct LinkedList* list, TYPE value)
{
     addLinkBefore(list, list->frontSentinel->next, value);
}


/***********************************************************
 * linkedListContains: returns 1 if a link with the value
 * is in the bag and 0 otherwise.
 *
 * parameters: pointer to linked list struct, given value.
 * returns: int.
 ***********************************************************/

int linkedListContains(struct LinkedList* list, TYPE value)
{
    struct Link *current;
    assert(list != 0);
    assert(list->size != 0);
    current = list->frontSentinel->next;
    while(current != list->backSentinel)
    {
        if(EQ(current->value, value))
            return 1;
        current = current->next;
    }
    return 0;
}


/***********************************************************
 * linkedListRemove: removes the first occurence of a link 
 * with the given value.
 *
 * parameters: pointer to linked list struct, given value.
 * returns: none.
 ***********************************************************/

void linkedListRemove(struct LinkedList* list, TYPE value)
{
    struct Link *current;
    assert(list != 0);
    assert(list->size != 0);
    current = list->frontSentinel->next;
    while(current != list->backSentinel && current->value != value)
        current = current->next;
    if (current != list->backSentinel)
        removeLink(list, current);
}
