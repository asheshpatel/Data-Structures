/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q3.c
 *
 * Overview:
 * This program creates an array of random ints then
 * sorts the array in ascending order.
 ************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>


/***********************************************************
 * sort: sorts the array in ascending order
 *
 * parameters: pointer to array and size of array.
 * returns: none.
 ***********************************************************/

void sort(int* number, int n)
{
    int temp;    // temp int to store values during swap
    _Bool swap;    // bool to indicate swap
    
    do    // continue comparing if swap occurred
    {
        swap = 0;
        for (int c = 0; c < n - 1; c++)    // compare all elements
        {
            if (number[c] > number[c + 1])    //swap if out of order
            {
                temp = number[c];
                number[c] = number[c + 1];
                number[c + 1] = temp;
                swap = 1;
            }
        }
    } while (swap == 1);
}


/***********************************************************
 * main: creates array of random numbers, prints array,
 * then prints array after sorting.
 *
 * parameters: none.
 * returns: none.
 ***********************************************************/
 
int main()
{
    int n = 20;    // size of array

    int *array = malloc(n);    // allocate memory for array

    for (int c = 0; c < 20; c++)    // fill array with random numbers
        array[c] = rand() % 50;

    for (int c = 0; c < 20; c++)    // print array
        printf("%i ", array[c]);

    sort(array, n);    // pass array by reference, and pass size of array
    
    printf("\n\n");    // print array
    for (int c = 0; c < 20; c++)
        printf("%i ", array[c]);
    
    return 0;
}
