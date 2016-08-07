/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q2.c
 *
 * Overview:
 * This program prints three values, uses a function to 
 * changes two by pointer and one by returning, prints
 * the returned value, then prints the original variables
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>


/***********************************************************
 * foo: doubles value pointed to by first pointer, halves 
 * value pointed to by second pointer, and sets variable
 * equal to sum of values pointed to by both pointers.
 *
 * parameters: two pointers and one variable.
 * returns: one variable.
 ***********************************************************/
 
int foo(int* a, int* b, int c)
{
    *a = *a * 2;                                                // sets a to double original value

    *b = *b / 2;                                                // sets b to half original value

    c = *a + *b;                                                // assigns c to sum of a + b

    return c;
}


/***********************************************************
 * main: prints values of three variables, prints value
 * returned by foo, then prints values of three
 * variables again.
 *
 * parameters: none.
 * returns: none.
 ***********************************************************/
 
int main()
{
    int x = 5;                                                  // declare and initialize three variables and a value to 
    int y = 6;                                                  // capture returned value
    int z = 7;
    int returned;

    printf("%i\n%i\n%i\n", x, y, z);                            // print values of variables
    
    returned = foo(&x, &y, z);                                  // pass addresses of a and b and value of c to foo

    printf("%i\n", returned);                                   // print value returned by foo

    printf("%i\n%i\n%i\n", x, y, z);                            // print values of variables
    
    return 0;
}
