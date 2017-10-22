#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
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

void freeMap (struct hashMap * ht)
{  /*write this*/
    int i;
    for(i = 0; i < ht->tableSize; i++){
        if(ht->table[i] == NULL)
            continue;
        hashLink * current = ht->table[i];
        hashLink * next = NULL;
        do{
            next = current->next;
            free(current->key);
            free(current);
            current = next;
        }while(next != NULL)
    }
    free(ht->table);
    ht->table = NULL;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    int hash = stringHash1(k);
    int hashIndex = (int) (labs(hash) % ht->tablesize);
    hashLink * current = ht->table[hash];
    if(current == NULL){
        ht->table[hashIndex] = (struct hashLink *) malloc(sizeof(hashLink));
        ht->table[hashIndex]->key = malloc(sizeof(char) * (strlrn(k) + 1));
        strcpy(ht->table[hashIndex]->key, k);
        ht->table[hashIndex]->value = v;
        ht->table[hashIndex]->next = NULL;
        h->count++;
        float loadFactor = ht->count/ht->tablesize;
        if(loadFactor > 10)
            resizeMap(ht);
    }
    else if(strcmp(current->key, k) == 0){
        current->value = v;
        return;
    }
    else{
        while(current->next != NULL){
            if(strcmp(current->next->key, k) == 0){
                current->next->value = v;
                return;
            }
            current = current->next;
        }
    }
    hashLink * new = (struct hashLink *) malloc(sizeof(hashLink));
    new->key = malloc(sizeof(char) * (strlen(k) + 1));
    strcpy(new->key, k);
    new->value = v;
    new->next = NULL;
    current->next = new;
    ht->count++;
    float loadFactor = ht->count/ht->tablesize;
    if(loadFactor > 10)
        resizeMap(ht);
    return;
    
}

void resizeMap(struct hashMap * ht){
    int oldsize = ht->tablesize;
    struct hashMap * oldht = ht;
    struct hashLink *cur, *last;
    int i;
    initMap(ht, 2*oldsize);
    for(i = 0; i < oldsize; i++){
        cur = oldht->table[i];
        while(cur != 0){
            insertMap(ht, cur->k, cur->value);
            last = cur;
            cur = cur->next;
            free(last)
        }
    }
    free(oldht);
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
    int hash = stringHash1(k);
    int hashIndex = (int) (labs(hash) % ht->tablesize);
    struct hashLink * cur = ht->table[hashIndex];
    while(cur ! = NULL){
        if(strcmp(cur->key, k) == 0){
            return &(cur->value);
        }
        cur = cur->next;
    }
    return NULL;
    
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
    int hash = stringHash1(k);
    int hashIndex  = (int) (labs(hash) % ht->tablesize);
    
    struct hashLink * cur = ht->table[hashIndex];
    while(cur){
        if(strcmp(cur->key, k) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
    
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
    int hash = stringHash1(k);
    int hashIndex = (int) (labs(hash) % ht->tablesize);
    struct hashLink *cur, *last;
    cur = ht->table[hashIndex];
    last = ht->table[hashIndex];
    while(cur){
        if(strcmp(cur->key, k) == 0){
            if(cur == ht->table[hashIndex])
                ht->table[hashIndex] = cur->next;
            else
                last->next = cur->next;
            free(cur);
            cur = 0;
            ht->count--;
        }
        else{
            last = cur;
            cur = cur->next;
        }
    }
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    return ht->tablesize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    int a = 0;
    for(i = 0; i < ht->tablesize; i++){
        if(ht->table[i] == NULL)
            a++;
    }
    return a;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
    return (float) (ht->count / ht->tablesize);
}
