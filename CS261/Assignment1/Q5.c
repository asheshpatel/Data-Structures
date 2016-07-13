/* CS261- Assignment 1 - Q.5*/
/* Name: Kelsey Helms
 * Date: June 27, 2016
 * Solution description: Takes a word and makes it
 * alternating upper and lower case.
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch)
{
    return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch)
{
    return ch-'A'+'a';
}

void sticky(char* word)
{
    /*Convert to sticky caps*/
    for (int c = 0; c < 50; c = c + 2)
    {
        if (word[c] > 90)
            word[c] = toUpperCase(word[c]);
    }
    for (int c = 1; c < 50; c = c + 2)
    {
        if (word[c] < 97)
            word[c] = toLowerCase(word[c]);
    }
}

int main()
{
    /*Read word from the keyboard using scanf*/
    char word[50];
    printf("Please enter a word:\n"); fflush(stdout);
    scanf("%s", word);
    
    /*Call sticky*/
    sticky(word);
    
    /*Print the new word*/
    printf("%s", word);
    
    return 0;
}
