/* CS261- Assignment 1 - Q.4*/
/* Name: Kelsey Helms
 * Date: June 27, 2016
 * Solution description: create an array with student ids and scores
 * then sort array in ascending score order.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student
{
    int id;
    int score;
};

void sort(struct student* students, int n)
{
    /*Sort the n students based on their score*/
    int tempScore;
    int tempID;
    _Bool swap;
    
    do
    {
        swap = 0;
        for (int c = 0; c < n - 1; c++)
        {
            if (students[c].score > students[c + 1].score)
            {
                tempScore = students[c].score;
                students[c].score = students[c + 1].score;
                students[c + 1].score = tempScore;
                tempID = students[c].id;
                students[c].id = students[c + 1].id;
                students[c + 1].id = tempID;
                swap = 1;
            }
        }
    } while (swap == 1);
}

int main()
{
    /*Declare an integer n and assign it a value.*/
    int n = 5;
    
    /*Allocate memory for n students using malloc.*/
    struct student *students = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    int used[5] = {0, 0, 0};
    int id;
    _Bool flag;
    for (int c = 0; c < n; c++)
    {
        do
        {
            flag = 0;
            id = rand() % 10 + 1;
            for (int i = 0; i < 5; i++)
            {
                if (id == used[i])
                    flag = 1;
            }
        } while (flag == 1);
        
        used[c] = id;
        students[c].id = id;
        students[c].score = rand() % 101;
    }
    
    /*Print the contents of the array of n students.*/
    for (int c = 0; c < n; c++)
        printf("ID %i Score %i\n", students[c].id, students[c].score);
    
    /*Pass this array along with n to the sort() function*/
    sort(students, n);
    
    /*Print the contents of the array of n students.*/
    printf("\n");
    for (int c = 0; c < n; c++)
        printf("ID %i Score %i\n", students[c].id, students[c].score);
    
    free(students);
}    
