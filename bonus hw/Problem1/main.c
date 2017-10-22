#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"

/* find minimum-cost path */
/* Input: pointer to tree
          pointer to array that should store all node values from
                  root to leaf along the identified min-cost path, 
   Output: min-cost path length 
*/
int FindMinPath(struct AVLTree *tree, int *path)
{
	struct AVLnode * cur = tree->root;
	int i = 1; /* counts the number of nodes along a path */

	/* write this function */
	
	return i;
}

int main()
{
	const char *filename = "input.txt";
	FILE *file;
	int num, len, i;
	clock_t timer;
	int pathArray[50];

	struct AVLTree *tree = newAVLTree(); /*return an empty tree */
	
	file = fopen(filename, "r");
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}

	timer = clock();

	/* Find the minimum-cost path in the AVL tree*/
	pathArray[0] = tree->root->val;
	len = FindminPath(tree, pathArray);

	/* Print out all numbers on the minimum-cost path */
	printf("The minimum-cost path is: ");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	fclose(file);
	timer = clock() - timer;
	printf("\nExecution time is %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	deleteAVLTree(tree); 
}



