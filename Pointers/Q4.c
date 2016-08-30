/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q4.c
 *
 * Overview:
 * This program creates an array with student IDs and 
 * scores, then sorts array in ascending score order 
 ************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student
{
    int id;
    int score;
};


/***********************************************************
 * sort: sorts the array by ascending score order
 *
 * parameters: pointer to array and size of struct.
 * returns: none.
 ***********************************************************/
 
void sort(struct student* students, int n)
{
    int tempScore;    // int tempScore to store score while swapping
    int tempID;    // int tempID to store ID while swapping
    _Bool swap;    // check if swap has occurred
    
    do    // keep comparing if swap has occurred
    {
        swap = 0;
        for (int c = 0; c < n - 1; c++)    // compare every student
        {
            if (students[c].score > students[c + 1].score)    // swap if scores not in ascending order
            {
                tempScore = students[c].score;    // swap score
                students[c].score = students[c + 1].score;
                students[c + 1].score = tempScore;
                
                tempID = students[c].id;    // swap ID
                students[c].id = students[c + 1].id;
                students[c + 1].id = tempID;
                swap = 1;
            }
        }
    } while (swap == 1);
}


/***********************************************************
 * main: creates array of struct student with randomly 
 * generated IDs and scores, prints the array, then 
 * prints the array after sorting.
 *
 * parameters: none.
 * returns: none.
 ***********************************************************/
 
int main()
{
    int n = 5;    // size of array
    
    struct student *students = malloc(n * sizeof(struct student));    // allocate memory for students

    int used[5] = {0, 0, 0};    // array of used numbers
    int id;
    _Bool flag;
    for (int c = 0; c < n; c++)    // assign every student
    {
        do    // continue generating until number is unique
        {
            flag = 0;
            id = rand() % 10 + 1;    // generate ID between 1-10
            for (int i = 0; i < 5; i++)
            {
                if (id == used[i])
                    flag = 1;
            }
        } while (flag == 1);
        
        used[c] = id;    // mark ID number as used
        students[c].id = id;    // set ID
        students[c].score = rand() % 101;    // generate score between 0-100 and set score
    }

    for (int c = 0; c < n; c++)    // print array of students
        printf("ID %i Score %i\n", students[c].id, students[c].score);

    sort(students, n);    // pass by reference and size of struct

    printf("\n");    // print array of students
    for (int c = 0; c < n; c++)
        printf("ID %i Score %i\n", students[c].id, students[c].score);
    
    free(students);    // deallocate memory of array
}    
