/* CS261- Assignment 1 - Q.3*/
/* Name: Kelsey Helms
 * Date: June 27, 2016
 * Solution description: creates an array of random ints
 * then sorts the array in ascending order.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n)
{
    /*Sort the given array number, of length n*/
    int temp;
    _Bool swap;
    
    do
    {
        swap = 0;
        for (int c = 0; c < n - 1; c++)
        {
            if (number[c] > number[c + 1])
            {
                temp = number[c];
                number[c] = number[c + 1];
                number[c + 1] = temp;
                swap = 1;
            }
        }
    } while (swap == 1);
}

int main()
{
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int *array = malloc(n);
    
    /*Fill this array with random numbers, using rand().*/
    for (int c = 0; c < 20; c++)
        array[c] = rand() % 50;
    
    /*Print the contents of the array.*/
    for (int c = 0; c < 20; c++)
        printf("%i ", array[c]);
    
    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    
    /*Print the contents of the array.*/
    printf("\n\n");
    for (int c = 0; c < 20; c++)
        printf("%i ", array[c]);
    
    return 0;
}
