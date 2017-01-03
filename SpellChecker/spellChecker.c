/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    August 1, 2016
 * Filename:        spellChecker.c
 *
 * Overview:
 * This program loads a dictionary and checks inputted words
 * against those in the dictionary to check their spelling.
 *
 * Input and outputs are defined by function.
 ************************************************************/


#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}


/* When researching efficient hash functions specifically for the use
   of large quantities of data, such as spellcheckers with buckets
   for each word, I found a hash function that has been spreading on
   stackoverflow: http://stackoverflow.com/questions/7666509/hash-function-for-string
 
   I have used this function to ensure that my dictionary has a decent
   load factor and doesn't take an inordinate amount of time to find words
   contained in the dictionary*/

unsigned long hashstring(char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while (c == *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}



/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    char *word = nextWord(file);
    unsigned long hash;
    
    while (word != NULL)
    {
        hash = hashstring(word);
        if(!hashMapContainsKey(map, word))
            hashMapPut(map, word, hash);
        free(word);
        word = nextWord(file);
    }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        if (hashMapContainsKey(map, inputBuffer))
        {
            printf("That word is spelled correctly!\n");
        }
        else
        {
            printf("That word is mispelled!\n");
        }
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}
