/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 8, 2016
 * Filename:        stackapp.c
 *
 * Overview:
 * Takes a string with different types of parentheses
 * and checks whether the parentheses are balanced
 * Inputs and outputs determined by function
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
 Using stack to check for unbalanced parentheses.
 ***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
 */
char nextChar(char* s)
{
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    if ( c == '\0' )
        return '0';
    else
        return c;
}

/* Checks whether the parentheses are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
 */
int isBalanced(char* s)
{
    if (s == NULL)
        return 1;       //null string is balanced
    
    struct DynArr *stack = newDynArr(10);       //stack holds opening parentheses
    char check;             //current char that we are checking
    int balance = 1;        //checks balance
    
    while((check = nextChar(s)) != '0')     //while string is not empty
    {
        switch(check)
        {
            case '{' :          //opening parentheses case: purposefully fall through
            case '[' :
            case '(' :
                pushDynArr(stack, check);
                break;
                
            case '}' :              //closing parentheses: each needs own case to match opening
                if(topDynArr(stack) == '{')
                {
                    popDynArr(stack);       //if matched, pop top for next match
                    break;
                }
                balance = 0;        //if not matching, not balanced
                
            case ']' :
                if(topDynArr(stack) == '[')
                {
                    popDynArr(stack);
                    break;
                }
                balance = 0;
                
            case ')' :
                if(topDynArr(stack) == '(')
                {
                    popDynArr(stack);
                    break;
                }
                balance = 0;
        }
    }
    
    if(sizeDynArr(stack) != 0)
    {
        balance = 0;        //if leftovers in stack that haven't been matched, not balanced
    }
    
    deleteDynArr(stack);        //always delete dynamically created stack!
    return balance;         //return result
    
}

int main(int argc, char* argv[]){
    
    printf("Assignment 2\n");
    
    char* s= argv[1];
    int res;
    
    res = isBalanced(s);
    
    if (res)
        printf("The string %s is balanced\n",s);
    else
        printf("The string %s is not balanced\n",s);
    
    return 0;
}
