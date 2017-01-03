/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 25, 2016
 * Filename:        toDo.c
 *
 * Overview:
 * This program implements different heap functions.
 *
 * Input and outputs are defined by function.
 ************************************************************/

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 *Compares a task with each task already in the heap.
 *@param heap
 *@param the new task to compare to the heap
 *@Returns: 0 if not present, 1 if present
 */

int duplicateCheck(DynamicArray *heap, struct Task *task)
{
    assert (heap != 0);
    assert (task != 0);
    compareFunction compare = taskCompare;
    
    return dyOrderedContains(heap, task, compare);
}

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        struct Task *newTask = taskNew(temp.priority, temp.name);
        if (duplicateCheck(heap, newTask) == 0)
            if (duplicateCheck(heap, newTask) == 0)
            {
                dyHeapAdd(heap, newTask, taskCompare);
            }
    }
    
}


/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    Task* newTask;
    Task* firstTask;
    compareFunction compare = taskCompare;
    FILE *filePointer;
    char name[TASK_NAME_SIZE], filename[50], *nlptr;
    int priority;
    
    switch (command)
   	{
        case 'a': /* add new task */
            printf("Please enter the task description: ");
            /* get task description from user input (from keyboard) */
            if (fgets(name, sizeof(name), stdin) != NULL)
            {
                /* remove trailing newline character */
                nlptr = strchr(name, '\n');
                if (nlptr)
                    *nlptr = '\0';
            }
            /* get task priority from user input (from keyboard) */
            do {
                printf("Please enter the task priority (0-999): ");
                scanf("%d", &priority);
            } while(!(priority >= 0 && priority <= 999));
            
            /* clear the trailing newline character */
            while (getchar() != '\n');
            
            /* create task and add the task to the heap */
            newTask = taskNew(priority, name);
            dyHeapAdd(list, newTask, compare);
            printf("The task '%s' has been added to your to-do list.\n\n", name);
            break;
            
        case 'g': /* get the first task */
            if (dySize(list) > 0)
            {
                firstTask = dyHeapGetMin(list);
                printf("Your first task is: %s\n\n", firstTask->name);
            }
            else
                printf("Your to-do list is empty!\n\n");
            
            break;
            
        case 'r': /* remove the first task */
            if (dySize(list) > 0)
            {
                firstTask = dyHeapGetMin(list);
                dyHeapRemoveMin(list, compare);
                printf("Your first task '%s' has been removed from the list.\n\n", firstTask->name);
            }
            else
                printf("Your to-do list is empty!\n\n");
            
            break;
            
        case 'p': /* print the list */
            if (dySize(list) > 0)
            {
                listPrint(list);
            }
            else
                printf("Your to-do list is empty!\n\n");
            
            break;
            
            
        case 's': /* save the list to file */
            if (dySize(list) > 0)
            {
                /* get filename from user input (from keyboard) */
                printf("Please enter the filename: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL)
                {
                    /* remove trailing newline character */
                    nlptr = strchr(filename, '\n');
                    if (nlptr)
                        *nlptr = '\0';
                }
                /* open the file */
                filePointer = fopen(filename, "w");
                if (filePointer == NULL) {
                    fprintf(stderr, "Cannot open %s\n", filename);
                    break;
                }
                /* save the list to the file */
                listSave(list, filePointer);
                /* close the file */
                fclose(filePointer);
                printf("The list has been saved into the file successfully.\n\n");
            }
            else
                printf("Your to-do list is empty!\n\n");
            
            break;
            
        case 'l': /* load the list from the file */
            printf("Please enter the filename: ");
            /* get filename from user input (from keyboard) */
            if (fgets(filename, sizeof(filename), stdin) != NULL)
            {
                /* remove trailing newline character */
                nlptr = strchr(filename, '\n');
                if (nlptr) 
                    *nlptr = '\0';
            }
            /* open the file */
            filePointer = fopen(filename, "r");	
            if (filePointer == NULL) {
                fprintf(stderr, "Cannot open %s\n", filename);
                break;
            }
            /* load the list from the file */
            listLoad(list, filePointer);
            /* close the file */
            fclose(filePointer);
            printf("The list has been loaded from file successfully.\n\n");			
            break;
            
        case 'e': /* exit the program */
            printf("Bye!\n\n");
            break;
            
        default: 
            printf("What is your command anyway?\n\n" );
            break;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
               );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
