/*  CS261- Assignment 1 - Q.1*/
/*  Name: Kelsey Helms
 *  Date: June 27, 2016
 *  Solution description: Struct of students
 *  that generates unique ID and scores, then
 *  calculates minimum, maximum and average
 *  scores.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student
{
    int id;
    int score;
};

struct student* allocate()
{
    /*Allocate memory for ten students*/
    struct student *ptr = malloc(10 * sizeof(struct student));
    
    /*return the pointer*/
    return ptr;
}

void generate(struct student* students)
{
    /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    int used[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int id;
    _Bool flag;
    for (int c = 0; c < 10; c++)
    {
        do
        {
            flag = 0;
            id = rand() % 10 + 1;
            for (int i = 0; i < 9; i++)
            {
                if (id == used[i])
                    flag = 1;
            }
        } while (flag == 1);
        
        used[c] = id;
        students[c].id = id;
        students[c].score = rand() % 101;
    }
}

void output(struct student* students)
{
    /*Output information about the ten students in the format:
     ID1 Score1
     ID2 score2
     ID3 score3
     ...
     ID10 score10*/
    for (int c = 0; c < 10; c++)
    {
        printf("ID %i Score %i\n", students[c].id, students[c].score);
    }
}

void summary(struct student* students)
{
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 100;
    int max = 0;
    double av = 0;
    
    for (int c = 0; c < 10; c++)
    {
        if (students[c].score < min)
            min = students[c].score;
        if (students[c].score > max)
            max = students[c].score;
        av = av + students[c].score;
    }
    
    av = av / 10;
    
    printf("Minimum: %i\nMaximum: %i\nAverage: %f", min, max, av);
}

void deallocate(struct student* stud)
{
    /*Deallocate memory from stud*/
    free(stud);
}

int main()
{
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);
    
    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);
    
    return 0;
}
