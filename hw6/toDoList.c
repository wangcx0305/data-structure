#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */
    assert(heap->size > 0);
    int i;
    Task * task;
    for(i = 0; i < heap->size; i++){
        task = heap->data[i];
        fprintf(filePtr, "%d\t%s\n", task->priority, task->descirption);
    }
    
    fclose(filePtr);
    
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */
    Task * task;
    char desc[TASK_DESC_SIZE];
    int priority;
    
    while(fscanf(filePtr, "%d\t", &priority) != EOF){
        fgets(desc, sizeof(desc), filePtr);
        task = createtask(priority, desc);
        addHeap(heap, task);
    }
    
    fclose(filePtr);
    
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	/* FIX ME  */
    assert(heap->size > 0);
    DynArr * temp;
    copyDynArr(heap, temp);
    sort(temp);
    for(i = temp->size - 1; i > 0; i--){
        Task * task = getDynArr(temp, i);
        fprintf("%d  %s\n", task->priority, task->description);
    }
    deleteDynArr(temp);
    
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
