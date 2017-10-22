#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] == NULL)
			continue;

		hashLink* currentLink = ht->table[i];
		hashLink* nextLink = NULL;

		do
		{
			nextLink = currentLink->next;
			free(currentLink->key);
			free(currentLink);
			currentLink = nextLink;
		} while (nextLink != NULL);
	}
	free(ht->table);
	ht->table = NULL;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	hashMap* tmpMap = createMap(newTableSize);

	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] == NULL)
			continue;

		hashLink* currentLink = ht->table[i];

		do
		{
			insertMap(tmpMap, currentLink->key, currentLink->value);
			currentLink = currentLink->next;
		} while (currentLink != NULL);
	}

	_freeMap(ht);
	ht->count = tmpMap->count;
	ht->table = tmpMap->table;
	ht->tableSize = tmpMap->tableSize;

	/* We don't want to free the table here, as it is the new table being used by our hash table */
	tmpMap->table = NULL;
	free(tmpMap);
	
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	int hash;

#if HASHING_FUNCTION == 1
	hash = stringHash1(k) % ht->tableSize;
#elif HASHING_FUNCTION == 2
	hash = stringHash2(k) % ht->tableSize;
#else
#error HASHING_FUNCTION is not valid.
#endif

	hashLink* currentLink = ht->table[hash];

	/* we know we don't really need to check anything if the bucket we fall in hasn't been allocated */
	if (currentLink == NULL)
	{
		ht->table[hash] = malloc(sizeof(hashLink));
		ht->table[hash]->key = malloc(sizeof(char) * (strlen(k) + 1)); strcpy(ht->table[hash]->key, k);
		ht->table[hash]->value = v;
		ht->table[hash]->next = NULL;

		/* increments the count of objects, calculates the load factor, and compares */
		if (((float)(++(ht->count)) / (float)(ht->tableSize)) > LOAD_FACTOR_THRESHOLD)
			_setTableSize(ht, (ht->tableSize * 2));

		return;
	}
	
	else if (strcmp(currentLink->key, k) == 0)
	{
		currentLink->value = v;
		return;
	}
	else
	{
		while (currentLink->next != NULL)
		{
			if (strcmp(currentLink->next->key, k) == 0)
			{
				currentLink->value = v;
				return;
			}

			currentLink = currentLink->next;
		}

		/* If we have gotten to this point, currentLink->next is null and should become something */

		hashLink* newLink = malloc(sizeof(hashLink));
		newLink->key = malloc(sizeof(char) * (strlen(k) + 1)); strcpy(newLink->key, k);
		newLink->value = v;
		newLink->next = NULL;

		currentLink->next = newLink;

		/* increments the count of objects, calculates the load factor, and compares */
		if (((float)(++(ht->count)) / (float)(ht->tableSize)) > LOAD_FACTOR_THRESHOLD)
			_setTableSize(ht, (ht->tableSize * 2));

		return;

	}
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	int hash;

#if HASHING_FUNCTION == 1
	hash = stringHash1(k) % ht->tableSize;
#elif (HASHING_FUNCTION == 2)
	hash = stringHash2(k) % ht->tableSize;
#else
#error HASHING_FUNCTION is not valid.
#endif

	hashLink* currentLink = ht->table[hash];

	while (currentLink != NULL)
	{
		if (strcmp(currentLink->key, k) == 0)
			return &(currentLink->value);
		currentLink = currentLink->next;
	}

	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	int hash;

#if HASHING_FUNCTION == 1
	hash = stringHash1(k) % ht->tableSize;
#elif (HASHING_FUNCTION == 2)
	hash = stringHash2(k) % ht->tableSize;
#else
#error HASHING_FUNCTION is not valid.
#endif

	hashLink* currentLink = ht->table[hash];

	while (currentLink != NULL)
	{
		if (strcmp(currentLink->key, k) == 0)
			return 1;
		currentLink = currentLink->next;
	}

	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	int hash;

#if HASHING_FUNCTION == 1
	hash = stringHash1(k) % ht->tableSize;
#elif (HASHING_FUNCTION == 2)
	hash = stringHash2(k) % ht->tableSize;
#else
#error HASHING_FUNCTION is not valid.
#endif

	hashLink* currentLink = ht->table[hash];

	if (currentLink == NULL)
		return;

	hashLink* nextLink = ht->table[hash]->next;

	if (strcmp(currentLink->key, k) == 0)
	{
		free(currentLink->key);
		ht->table[hash] = nextLink;
		free(currentLink);
		return;
	}

	while (nextLink != NULL)
	{
		if (strcmp(nextLink->key, k) == 0)
		{
			free(nextLink->key);
			currentLink->next = nextLink->next;
			free(nextLink);
			return;
		}
		currentLink = currentLink->next;
		nextLink = nextLink->next;
	}

	
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	int empty = 0;

	for (int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] == NULL)
			empty++;
	}

	return empty;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	return ((float)(ht->count) / (float)(ht->tableSize));
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


