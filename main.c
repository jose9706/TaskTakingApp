#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

#define MAX_TASKS 64
#define MAX_TASK_LENGTH 256

enum Status
{
    SUCCESS,
    ERR_CODE
};

struct TaskHolder
{
    int taskCount;
    char taskList[MAX_TASKS][MAX_TASK_LENGTH];
};

enum Status HandleInput(struct TaskHolder *tasks)
{
    printf("Input task:");
    getchar(); // Clean last scanf because C
    char *inputTask = (char *)calloc(MAX_TASK_LENGTH, sizeof(char));
    if (inputTask == NULL)
    {
        printf("Failed allocating memory");
        free(inputTask);
        return ERR_CODE;
    }
    if (fgets(inputTask, MAX_TASK_LENGTH, stdin) == NULL)
    {
        printf("Failed getting input task.");
        free(inputTask);
        return ERR_CODE;
    }

    if (strlen(inputTask) == MAX_TASK_LENGTH - 1)
    {
        FlushRestOfInput(); // Flush the rest because we are past the max task length and if we dont do this C is funny.
    }

    strcpy(tasks->taskList[tasks->taskCount], inputTask);
    tasks->taskCount++;
    free(inputTask);
    return SUCCESS;
}

void FlushRestOfInput()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int main()
{
    struct TaskHolder *taskList = (struct TaskHolder *)calloc(1, sizeof(struct TaskHolder));
    if (taskList == NULL)
    {
        printf("Failed allocating memory\n");
        return 0;
    }
    taskList->taskCount = 0;

    printf("Task taking app in C. Max task count=[%d], Max Length=[%d]\n", MAX_TASKS, MAX_TASK_LENGTH);

    while (1)
    {
        int chosenOption;
        printf("Currently have %d tasks, max is %d, choose option:\n", taskList->taskCount, MAX_TASKS);
        printf("1. Add a new task.\n");
        printf("2. Remove last task.\n");
        printf("3. View all tasks.\n");
        printf("4. Exit.\n");
        scanf("%d", &chosenOption);
        switch (chosenOption)
        {
        case 1:
            if (HandleInput(taskList) == ERR_CODE)
            {
                printf("We've failed terribly handling the input\n");
                free(taskList);
                return 0;
            }
            break;
        case 2:
            if (taskList->taskCount == 0)
            {
                printf("No task to delete, skipping.\n");
            }
            else
            {
                taskList->taskCount--;
            }
            break;
        case 3:
            printf("Tasks:\n");
            for (size_t i = 0; i < taskList->taskCount; i++)
            {
                printf("Task #%zu: %s\n", i + 1, taskList->taskList[i]);
            }

            break;
        case 4:
            printf("Exiting app...\n");
            free(taskList);
            return 1;
            break;
        default:
            printf("We dont support %d. Cya\n", chosenOption);
            free(taskList);
            return 0;
        }
    }
    free(taskList);
    return 1;
}
