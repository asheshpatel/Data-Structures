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
 * parameters: pointer to x
 * returns: nothing
 ***********************************************************/
 
void fooA(int* iptr)
{
    /*Print the value pointed to by iptr*/
    printf("%i\n", *iptr);
    
    /*Print the address pointed to by iptr*/
    printf("%p\n", &(*iptr));
    
    /*Print the address of iptr itself*/
    printf("%p\n", iptr);
}


/***********************************************************
 * main function: declares an integer x, prints the address
 * and value of x.
 *
 * parameters: nothing
 * returns: nothing
 ***********************************************************/
 
int main()
{
    /*declare an integer x*/
    int x = 3;
    
    /*print the address of x*/
    printf("%p\n", &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*print the value of x*/
    printf("%i\n", x);
    
    return 0;
}
