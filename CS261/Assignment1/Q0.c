/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q0.c
 *
 * Overview:
 * This program will print the value of x and the 
 * address of x with and without use of a pointer,
 * and print the address of the pointer.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>

/***********************************************************
 * fooA: prints the value of x, the address of x, 
 * and the address of the pointer.
 *
 * parameters: pointer to x.
 * returns: nothing.
 ***********************************************************/
 
void fooA(int* iptr)
{
    printf("%i\n", *iptr);                                   // print the value pointed to by pointer

    printf("%p\n", &(*iptr));                                // print the address pointed to by pointer

    printf("%p\n", iptr);                                    // print the address of the pointer itself
}


/***********************************************************
 * main: declares an integer x, prints the address
 * and value of x.
 *
 * parameters: nothing.
 * returns: nothing.
 ***********************************************************/
 
int main()
{
    int x = 3;                                                // declare and initialize x
    
    printf("%p\n", &x);                                       // print address of x

    fooA(&x);                                                 // call fooA with address of x

    printf("%i\n", x);                                        // print the value of x
    
    return 0;
}
