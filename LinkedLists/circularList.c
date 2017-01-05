/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 11, 2016
 * Filename:        circularList.c
 *
 * Overview:
 * This is the circular linked list implementation file
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

struct Link
{
    TYPE value;    // link value
    struct Link * next;    // pointer to next link
    struct Link * prev;    // pointer to previous link
};

struct CircularList
{
    int size;    // size of circular list
    struct Link* sentinel;    // pointer to list sentinel
};


/* ************************************************************************
	Helper Functions
 ************************************************************************ */

/***********************************************************
 * init: allocates the list's sentinel and sets the size 
 * to 0. The sentinel's next and prev should point to 
 * the sentinel itself.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

static void init(struct CircularList* list)
{
    assert(list != 0);
    list->size = 0;
    list->sentinel = (struct Link *)malloc(sizeof(struct Link));
    assert(list->sentinel != 0);
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
}


/***********************************************************
 * createLink: creates a link.
 *
 * parameters: value of link.
 * returns: link.
 ***********************************************************/

static struct Link* createLink(TYPE value)
{
    struct Link* newLink = (struct Link *)malloc(sizeof(struct Link));
    assert(newLink != 0);
    newLink->value = value;
    newLink->next = NULL;
    newLink->prev = NULL;
    return(newLink);
}


/***********************************************************
 * addLinkAfter: adds a new link after the given link.
 *
 * parameters: pointer to circular list struct, given link, 
 * value of new link.
 * returns: none.
 ***********************************************************/

static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
    assert(list != 0);
    assert(link != 0);
    struct Link* newLink = createLink(value);
    newLink->next = link->next;
    newLink->prev = link;
    link->next->prev = newLink;
    link->next = newLink;
    list->size++;
}


/***********************************************************
 * removeLink: removes a given link.
 *
 * parameters: pointer to circular list struct, given link.
 * returns: none.
 ***********************************************************/

static void removeLink(struct CircularList* list, struct Link* link)
{
    assert(list != 0);
    assert(link != 0);
    assert(list->size != 0);
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(link);
    list->size--;
}


/* ************************************************************************
	Circular Linked List Functions
 ************************************************************************ */

/***********************************************************
 * circularListCreate: allocates and initializes a list.
 *
 * parameters: none.
 * returns: pointer to circular list struct.
 ***********************************************************/

struct CircularList* circularListCreate()
{
    struct CircularList* list = malloc(sizeof(struct CircularList));
    init(list);
    return list;
}


/***********************************************************
 * circularListDestroy: deallocates every link in the list
 * and frees the list pointer.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

void circularListDestroy(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    while(list->size > 0)
        circularListRemoveFront(list);
    free(list->sentinel);
    free(list);
}


/***********************************************************
 * circularListPrint: prints the values of the links in the
 * deque from front to back.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

void circularListPrint(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    struct Link* current = list->sentinel->next;
    assert(current != 0);
    while(current != list->sentinel)
    {
        printf("%f\n", current->value);
        current = current->next;
    }
}


/***********************************************************
 * circularListReverse: reverses the deque.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

void circularListReverse(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    struct Link* current = list->sentinel->next;
    struct Link* temp;
    list->sentinel->prev = current;
    do
    {
        temp = current->next;
        if(temp->next == list->sentinel)
        {
            list->sentinel->next = temp;
        }
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while(current != list->sentinel);
}


/* ************************************************************************
	Deque Interface Functions
 ************************************************************************ */

/***********************************************************
 * circularListAddFront: adds a new link with the given
 * value to the front of the deque.
 *
 * parameters: pointer to circular list struct, given value.
 * returns: none.
 ***********************************************************/

void circularListAddFront(struct CircularList* list, TYPE value)
{
    assert(list != 0);
    addLinkAfter(list, list->sentinel, value);
}


/***********************************************************
 * circularListAddBack: adds a new link with the given value
 * to the back of the deque.
 *
 * parameters: pointer to circular list struct, given value.
 * returns: none.
 ***********************************************************/

void circularListAddBack(struct CircularList* list, TYPE value)
{
    assert(list != 0);
    addLinkAfter(list, list->sentinel->prev, value);
}


/***********************************************************
 * circularListFront: returns the value of the link at the
 * front of the deque.
 *
 * parameters: pointer to circular list struct.
 * returns: front link value.
 ***********************************************************/

TYPE circularListFront(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    return(list->sentinel->next->value);
}


/***********************************************************
 * circularListBack: returns the value of the link at the
 * back of the deque.
 *
 * parameters: pointer to circular list struct.
 * returns: back link value.
 ***********************************************************/

TYPE circularListBack(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    return(list->sentinel->prev->value);
}


/***********************************************************
 * circularListRemoveFront: removes the link at the front
 * of the deque.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

void circularListRemoveFront(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    removeLink(list, list->sentinel->next);
}


/***********************************************************
 * circularListRemoveBack: removes the link at the back
 * of the deque.
 *
 * parameters: pointer to circular list struct.
 * returns: none.
 ***********************************************************/

void circularListRemoveBack(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    removeLink(list, list->sentinel->prev);
}


/***********************************************************
 * circularListIsEmpty: returns 1 if the deque is empty 
 * and 0 otherwise.
 *
 * parameters: pointer to circular list struct.
 * returns: int.
 ***********************************************************/

int circularListIsEmpty(struct CircularList* list)
{
    assert(list != 0);
    return(list->size == 0);
}
