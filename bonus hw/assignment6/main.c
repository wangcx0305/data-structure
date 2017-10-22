#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

int main (int argc, const char * argv[]) {
	const char* filename;
	struct hashMap *hashTable;	
	int tableSize = 10;
	clock_t timer;
	FILE *fileptr;	
    /*
     this part is using command line arguments, you can use them if you wish
     but it is not required. DO NOT remove this code though, we will use it for
     testing your program.
     
     if you wish not to use command line arguments manually type in your
     filename and path in the else case.
     */
    if(argc == 2)
        filename = argv[1];
    else
        filename = "input1.txt"; /*specify your input text file here*/
    
    printf("opening file: %s\n", filename);
	fileptr = fopen(filename, "r");

	if (fileptr == NULL)
	{
		printf("No file %s exists!", filename);
		return 1;
	}
    
	timer = clock();
	
	hashTable = createMap(tableSize);	   

	while (1)
	{
		char* word = getWord(fileptr);
		if (word == NULL)
			break;

		int * occurances = atMap(hashTable, word);

		if (occurances == NULL)
			insertMap(hashTable, word, 1);
		else
		{
			insertMap(hashTable, word, *occurances + 1);
		}
		
		free(word);
	}

	/* Print the words (case sensitive)*/
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(hashTable); i++){
		temp = hashTable->table[i];
		while(temp != 0){
			printf("%s: ", temp->key);
			printf("%d", temp->value);
			printf("\n");
			temp=temp->next;
		}
	}

	printMap(hashTable);
	timer = clock() - timer;
	printf("\nconcordance ran in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	printf("Table emptyBuckets = %d\n", emptyBuckets(hashTable));
    printf("Table count = %d\n", size(hashTable));
	printf("Table capacity = %d\n", capacity(hashTable));
	printf("Table load = %f\n", tableLoad(hashTable));
	
	printf("Deleting keys\n");
	
	removeKey(hashTable, "and");
	removeKey(hashTable, "me");
	removeKey(hashTable, "the");
	printMap(hashTable);
		
	deleteMap(hashTable);
	printf("\nDeleted the table\n");   
	fclose(fileptr);
	return 0;
}

void printValue(ValueType v) {
	printf("Value:%d", v);
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}
