/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 27, 2016
 * Filename:        Q1.c
 *
 * Overview:
 * This program will generate unique ID and scores for a
 * struct of students, then calculate the minimum,
 * maximum, and average scores.
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
 * allocate: allocates memory for 10 students, then
 * returns a pointer to the struct.
 *
 * parameters: none.
 * returns: pointer to struct student.
 ***********************************************************/
 
struct student* allocate()
{
    struct student *ptr = malloc(10 * sizeof(struct student));  // allocate memory for ten students
    
    return ptr;                                                 // return the pointer
}


/***********************************************************
 * generate: generates random and unique ID and scores
 * for the ten students, ID between 1-10, scores 
 * between 0-100.
 *
 * parameters: pointer to struct student.
 * returns: none.
 ***********************************************************/
 
void generate(struct student* students)
{
    int used[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};                  // array of used numbers
    int id;
    _Bool flag;
    for (int c = 0; c < 10; c++)                                // fill all ten students
    {
        do                                                      // continue trying to find unique ID while
        {                                                       // number has already been used
            flag = 0;
            id = rand() % 10 + 1;                               // make sure number is between 1-10
            for (int i = 0; i < 9; i++)
            {
                if (id == used[i])
                    flag = 1;
            }
        } while (flag == 1);
        
        used[c] = id;                                           // put number into used array
        students[c].id = id;                                    // set ID
        students[c].score = rand() % 101;                       // randomly generate score between 0-100 and set score
    }
}


/***********************************************************
 * output: displays struct student.
 *
 * parameters: pointer to struct student.
 * returns: none.
 ***********************************************************/
 
void output(struct student* students)
{
    for (int c = 0; c < 10; c++)                                // output information about the ten students
    {
        printf("ID %i Score %i\n", students[c].id, students[c].score);
    }
}


/***********************************************************
 * summary: computes and prints the minimum, maximum,
 * and average scores of the ten students.
 *
 * parameters: pointer to struct student.
 * returns: none.
 ***********************************************************/
 
void summary(struct student* students)
{
    int min = 100;                                              // set up initial min, max, and average
    int max = 0;
    double av = 0;
    
    for (int c = 0; c < 10; c++)                                // compare each student to min and max, then add to average
    {
        if (students[c].score < min)
            min = students[c].score;
        if (students[c].score > max)
            max = students[c].score;
        av = av + students[c].score;
    }
    
    av = av / 10;                                               // divide sum by number of students for average
                                                                // display min, max, and average
    printf("Minimum: %i\nMaximum: %i\nAverage: %f", min, max, av); 
}


/***********************************************************
 * deallocate: deallocates memory from struct student.
 *
 * parameters: pointer to struct student.
 * returns: none.
 ***********************************************************/
 
void deallocate(struct student* stud)
{
    free(stud);
}


/***********************************************************
 * main: makes calls to all functions.
 *
 * parameters: none.
 * returns: none.
 ***********************************************************/
 
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
