#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
    char *filename = malloc(sizeof(char)*250);
    char *description = malloc(sizeof(char)*250);
    int priority;
    char cmd = ' ';
    DynArr *mainList = createDynArr(10);

    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    
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
        /* get input command (from the keyboard) */
        cmd = getchar();
        /* clear the trailing newline character */
        while (getchar() != '\n');
        
        switch (cmd)
        {
            case 'l':
                printf("Please enter the filenmae: ");
                fgets(filename, 100, stdin);
                if(filename[strlen(filename) - 1] == '\n')
                    filename[strlen(filename) - 1] = 0;
                FILE *reader = fopen(filename, "r");
                loadList(mainList, reader);
                printf("The list has been loaded from file successfully.\n");
                fclose(reader);
                break;
                
            case 's':
                printf("Please enter the filename: ");
                fgets(filename, 100, stdin);
                if(filename[strlen(filename) - 1] == '\n')
                    filename[strlen(filename) - 1] = 0;
                FILE *writer = fopen(filename, "w+");
                saveList(mainList, writer);
                printf("The list has been saved io the file successfully. \n");
                fclose(writer);
                break;
                
            case 'a':
                printf("Please enter the task description: ");
                fgets(description, 100, stdin);
                if (description[strlen(description) - 1] == '\n')
                    description[strlen(description) - 1] = 0;
                printf("Please enter the task priority (0-999): ");
                scanf("%d", &priority);
                while (getchar() != '\n');
                TaskP dummy = createTask(priority, description);
                addHeap(mainList, dummy, compare);
                printf("The task '%s' has been added to the list.\n", description);
                break;
                
            case 'g':
                if (!isEmptyDynArr(mainList))
                    printf("The first task is: %s\n", ((struct Task *)getMinHeap(mainList))->description);
                else
                    printf("The list is empty...\n");
                break;
                
            case 'r':
                if (isEmptyDynArr(mainList))
                    printf("The list is empty...\n");
                else
                {
                    description = ((struct Task *)getMinHeap(mainList))->description;
                    removeMinHeap(mainList, compare);
                    printf("The first task '%s' has been removed from the list.\n", description);
                }
                break;
                
            case 'p':
                if(isEmptyDynArr(mainList))
                    printf("The list is empty...\n");
                else
                    printList(mainList);
                break;
                
            case 'e':
                printf("Exiting Application...\n");
                break;
        }
        
        /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
    while(cmd != 'e');
    /* delete the list */
    deleteDynArr(mainList);
    
    return 0;
}
