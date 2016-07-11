/* CS261- Assignment 1 - Q. 0 */
/* Name: Kelsey Helms
 * Date: June 27, 2016
 * Solution description: printing int and int pointer
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr)
{
    /*Print the value pointed to by iptr*/
    printf("%i\n", *iptr);
    
    /*Print the address pointed to by iptr*/
    printf("%p\n", &(*iptr));
    
    /*Print the address of iptr itself*/
    printf("%p\n", iptr);
}

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
