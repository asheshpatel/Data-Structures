/* CS261- Assignment 1 - Q.2*/
/* Name: Kelsey Helms
 * Date: June 27, 2016
 * Solution description: passing variables by reference to change
 * the variables in main vs. passing variables by value to not
 * change the variables in main.
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c)
{
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main()
{
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int returned;
    
    /*Print the values of x, y and z*/
    printf("%i\n%i\n%i\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    returned = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
    printf("%i\n", returned);
    
    /*Print the values of x, y and z again*/
    printf("%i\n%i\n%i\n", x, y, z);
    
    /*Is the return value different than the value of z?  Why?
     Answer: z was not passed by reference, therefore the z in main
     did not change. The returned value is that of the new a plus
     the new b inside of foo
     */
    return 0;
}
