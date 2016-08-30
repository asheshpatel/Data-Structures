/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 8, 2016
 * Filename:        dynamicArray.c
 *
 * Overview:
 * This is the dynamic array implementation file
 ************************************************************/

#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
    TYPE *data;		/* pointer to the data array */
    int size;		/* Number of elements in the array */
    int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
 ************************************************************************ */

/***********************************************************
 * initDynArr: initialize the array
 *
 * parameters: pointer to struct and capacity of array.
 * returns: none.
 ***********************************************************/

void initDynArr(DynArr *v, int capacity)
{
    assert(capacity > 0);    // assert capacity is not zero and the pointer to struct is not null
    assert(v!= 0);
    
    v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);    // allocate memory for array 
    
    assert(v->data != 0);    // assert pointer to array is not null
    
    v->size = 0;    // initialize size to zero since empty and capacity to set capacity
    v->capacity = capacity;
}


/***********************************************************
 * newDynArr: allocate and initialize new array
 *
 * parameters: capacity of array.
 * returns: pointer to DynArr struct.
 ***********************************************************/

DynArr* newDynArr(int cap)
{
    assert(cap > 0);    // assert capacity is not zero
    
    DynArr *r = (DynArr *)malloc(sizeof( DynArr));    // allocate memory for struct
    
    assert(r != 0);    // assert pointer to struct is not null
    
    initDynArr(r,cap);    // initialize array
    
    return r;    // return pointer to struct
}


/***********************************************************
 * freeDynArr: deallocates array
 *
 * parameters: pointer to struct.
 * returns: none.
 ***********************************************************/

void freeDynArr(DynArr *v)
{
    if(v->data != 0)
    {
        free(v->data);    // free array and make pointer null
        v->data = NULL; 
    }
    
    v->size = 0;    // set size and capacity to zero
    v->capacity = 0;
}


/***********************************************************
 * deleteDynArr: deallocate array and struct
 *
 * parameters: pointer to struct.
 * returns: none.
 ***********************************************************/

void deleteDynArr(DynArr *v)
{
    freeDynArr(v);    // deallocate array
    free(v);    // free pointer to struct
}


/***********************************************************
 * _dynArrSetCapacity: resizes array to given capacity
 *
 * parameters: pointer to struct and capacity of array.
 * returns: none.
 ***********************************************************/

void _dynArrSetCapacity(DynArr *v, int newCap)
{
    assert(newCap > 0);    // assert capacity is not zero and pointer to struct is not null
    assert(v!=0);
    
    struct DynArr newArray;    // create a new array given the new capacity and initialize
    initDynArr(&newArray, newCap);
    
    for (int index = 0; index < v->size; index++)    // copy the old array to the new array
    {
        newArray.data[index] = v->data[index];
        newArray.size++;
    }
    
    freeDynArr(v);    // release the old array
    *v = newArray;    // point to the new array
}


/***********************************************************
 * sizeDynArr: get the size of the array
 *
 * parameters: pointer to struct.
 * returns: size of array.
 ***********************************************************/

int sizeDynArr(DynArr *v)
{
    return v->size;
}


/***********************************************************
 * addDynArr: adds an element to end of array
 *
 * parameters: pointer to struct and element value.
 * returns: none.
 ***********************************************************/

void addDynArr(DynArr *v, TYPE val)
{
    if(v->size >= v->capacity)    // check to see if a resize is necessary
        _dynArrSetCapacity(v, 2 * v->capacity);
        
    v->data[v->size] = val;    // add element to end
    v->size++;    // increase size of array
}


/***********************************************************
 * getDynArr: get element from specified position of array
 *
 * parameters: pointer to struct.
 * returns: element value.
 ***********************************************************/

TYPE getDynArr(DynArr *v, int pos)
{
    assert(v!=0);    // assert pointer to struct is not null and position is not less than zero or greater than size of array
    assert(pos >= 0);
    assert(pos < v->size);
    
    return v->data[pos];    // return element value at specified position
}


/***********************************************************
 * putDynArr: put an item into array at specified position,
 *		overwrititng element that was there
 *
 * parameters: pointer to struct, specified position, and
 *		element value.
 * returns: none.
 ***********************************************************/

void putDynArr(DynArr *v, int pos, TYPE val)
{
    assert(v!=0);    // assert pointer to struct is not null and position is not less than zero or greater than size of array
    assert(pos < v->size);
    assert(pos >= 0);
    
    v->data[pos] = val;    // add element value at specified position
}


/***********************************************************
 * swapDynArr: swap two specified elements in array
 *
 * parameters: pointer to struct and two specified positions.
 * returns: none.
 ***********************************************************/

void swapDynArr(DynArr *v, int i, int  j)
{
    assert (v!=0);    // assert pointer to struct is not null and both positions are not less than zero or greater than size of array
    assert(i >=0 && i < v->size);
    assert(j >=0 && j < v->size);
    
    int temp = v->data[i];    // swap elements using a temp to help
    v->data[i] = v->data[j];
    v->data[j] = temp;
}


/***********************************************************
 * removeatDynArr: removes element at specified position 
 * 		and shifts other elements back to fill gap
 *
 * parameters: pointer to struct and specified position.
 * returns: none.
 ***********************************************************/

void removeAtDynArr(DynArr *v, int idx)
{
    assert(v!=0);    // assert pointer to struct is not null and position is not less than zero or greater than size of array
    assert(v->size > idx);
    assert(idx >= 0);
    
    for (int j = idx; j < v->capacity; j++)    // shift all elements that are greater than specified position back one
        v->data[j] = v->data[j+1];
        
    v->size = v->size - 1;    // decrease size of array
}


/* ************************************************************************
	Stack Interface Functions
 ************************************************************************ */

/***********************************************************
 * isEmptyDynArr: returns boolean as int (1 if empty, 0 if not) 
 * 		to show if array contains any element
 *
 * parameters: pointer to struct.
 * returns: boolean as int.
 ***********************************************************/

int isEmptyDynArr(DynArr *v)
{
    return (sizeDynArr(v) == 0);
}


/***********************************************************
 * pushDynArr: pushes an element on top of the stack
 *
 * parameters: pointer to struct and element value.
 * returns: none.
 ***********************************************************/

void pushDynArr(DynArr *v, TYPE val)
{
    assert(v != 0);    // assert pointer to struct is not null
    
    if(v->size >= v->capacity)    // if size is larger than capacity, resize array
        _dynArrSetCapacity(v, 2 * v->capacity);
    
    v->data[v->size] = val;    // push element on top of stack and increase size
    v->size = v->size + 1;
}


/***********************************************************
 * topDynArr: returns element value at top of stack
 *
 * parameters: pointer to struct.
 * returns: element value.
 ***********************************************************/

TYPE topDynArr(DynArr *v)
{
    assert(v != 0);    // assert pointer to struct is not null and array is not empty
    assert(v->size > 0);
    
    return v->data[v->size-1];    // return value of top element
}


/***********************************************************
 * popDynArr: removes element on top of stack
 *
 * parameters: pointer to struct.
 * returns: none.
 ***********************************************************/

void popDynArr(DynArr *v)
{
    assert(v != 0);    // assert pointer to struct is not null and array is not empty
    assert(v->size > 0);
    
    removeAtDynArr(v, v->size-1);    // remove element at top of stack
}


/* ************************************************************************
	Bag Interface Functions
 ************************************************************************ */

/***********************************************************
 * containsDynArr: returns boolean as int (1 if empty, 0 if not) 
 * 		to show if array contains specified value
 *
 * parameters: pointer to struct and value to look for.
 * returns: boolean as int.
 ***********************************************************/

int containsDynArr(DynArr *v, TYPE val)
{
    int i;
    
    for (i = 0; i < v->size; i++)    // search all elements
    {
        if(v->data[i] == val)
            return 1;    // return true if found and end search
    }
    
    return 0;    // return false if not found in array
}


/***********************************************************
 * removeDynArr: removes first occurrence of specified value 
 * 		if it is found in array
 *
 * parameters: pointer to struct and value to look for.
 * returns: none.
 ***********************************************************/

void removeDynArr(DynArr *v, TYPE val)
{
    int i = 0;
    int a;
    while(!EQ(v->data[i], val))    // search array until element is found
        i++;
    
    for(a = i; a < v->size-1; a++)    // move elements greater than position of found element back one
    {
        v->data[a] = v->data[a+1];
        v->size = v->size-1;    // decrease size of array
    }
}
