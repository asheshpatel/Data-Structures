/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q5.c
 *
 * Overview:
 * This program takes a word from user and makes it 
 * "sticky caps," alternating upper and lower case letters.
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>


/***********************************************************
 * toUpperCase: converts lower case to upper case.
 *
 * parameters: char.
 * returns: char.
 ***********************************************************/
 
char toUpperCase(char ch)
{
    return ch-'a'+'A';
}


/***********************************************************
 * toLowerCase: converts upper case to lower case.
 *
 * parameters: char.
 * returns: char.
 ***********************************************************/

char toLowerCase(char ch)
{
    return ch-'A'+'a';
}


/***********************************************************
 * sticky: converts a word to stick caps (alternating
 * upper and lower case letters).
 *
 * parameters: pointer to array and size of struct.
 * returns: none.
 ***********************************************************/
 
void sticky(char* word)
{
    int c = 0;                                                  // count position of letters
    while (word[c] != '/0')                                     // search every letter
    {
        if (c % 2 == 0 && word[c] > 90)                         // if even letters are lower case, convert to upper case
            word[c] = toUpperCase(word[c]);
        if (c % 2 != 0 && word[c] < 97)                         // if odd letters are upper case, convert to lower case
            word[c] = toLowerCase(word[c]);
    }
}


/***********************************************************
 * main: reads in word from keyboard, then prints 
 * sticky caps versions of word.
 *
 * parameters: word.
 * returns: none.
 ***********************************************************/
 
int main()
{
    char word[50];                                              // char array to hold word
    printf("Please enter a word:\n"); fflush(stdout);
    scanf("%s", word);                                          // get word from user

    sticky(word);                                               // pass word by reference

    printf("%s", word);                                         // print sticky caps word
    
    return 0;
}
