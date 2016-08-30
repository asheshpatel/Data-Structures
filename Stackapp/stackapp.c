/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 8, 2016
 * Filename:        stackapp.c
 *
 * Overview:
 * Takes a string with different types of parentheses
 * and checks whether the parentheses are balanced
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/***********************************************************
 * nextChar: returns next character of string
 *
 * parameters: pointer to string.
 * returns: next char.
 ***********************************************************/

char nextChar(char* s)
{
    static int i = -1;    // start at -1 to set up increase and search at 0
    char c;
    
    ++i;
    c = *(s+i);    // get next char
    
    if ( c == '\0' )    // if next char is null, string is ended
        return '0';
    else
        return c;    // return next char
}


/***********************************************************
 * isBalanced: checks whether parentheses are balanced using
 * 		boolean as int (1 is balanced, 0 is not)
 *
 * parameters: pointer to string.
 * returns: boolean as int.
 ***********************************************************/

int isBalanced(char* s)
{
    if (s == NULL)
        return 1;    // null string is balanced
    
    struct DynArr *stack = newDynArr(10);    // stack holds opening parentheses
    char check;    // current char that we are checking
    int balance = 1;    // checks balance
    
    while((check = nextChar(s)) != '0')    // while string is not empty
    {
        switch(check)
        {
            case '{' :    // opening parentheses case: purposefully fall through
            case '[' :
            case '(' :
                pushDynArr(stack, check);
                break;
                
            case '}' :    // closing parentheses: each needs own case to match opening
                if(topDynArr(stack) == '{')
                {
                    popDynArr(stack);    // if matched, pop top for next match
                    break;
                }
                balance = 0;    // if not matching, not balanced
                
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
        balance = 0;    // if leftovers in stack that haven't been matched, not balanced
    }
    
    deleteDynArr(stack);    // always delete dynamically created stack!
    return balance;    // return result
}


/***********************************************************
 * main: takes string and prints result of parentheses 
 * 		balance
 *
 * parameters: none.
 * returns: none.
 ***********************************************************/
 
int main(int argc, char* argv[]){
    
    printf("Assignment 2\n");
    
    char* s= argv[1];    // get string of parentheses
    int res;
    
    res = isBalanced(s);    // see if parentheses are balanced
    
    if (res)    // print result
        printf("The string %s is balanced\n",s);
    else
        printf("The string %s is not balanced\n",s);
    
    return 0;
}
