#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

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
    struct hashLink *current, *last;
    for(i = 0; i < ht->tableSize; i++){
        current = ht->table[i];
        while(current != 0){
            last = current;
            current = current->next;
            free(last->key);
            free(last);
        }
      }
    
    free(ht->table);
    ht->tableSize = 0;
    ht->count = 0;
    ht->table = 0;

}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    int hash = stringHash1(k);
    int hashIndex = (int) (labs(hash) % ht->tableSize);
    struct hashLink *cur, *newhashLink;
    if(ht-> table[hashIndex]==0){
        newhashLink = (struct hashLink*)malloc(sizeof(struct hashLink));
        /*assert(newhashLink);*/
        newhashLink -> key = k;
        newhashLink -> value = v;
        newhashLink -> next = 0;
        ht->table[hashIndex] = newhashLink;
        ht->count++;
    }else{
        cur = ht->table[hashIndex];
        while(cur!=NULL){
            if(EQ(*(cur->key), *k)){
                cur->value = v;
                break;
            }else{
                cur = cur->next;
            }
        }
        newhashLink = (struct hashLink *)malloc(sizeof(struct hashLink));
        /*assert(newhashLink);*/
        newhashLink -> key = k;
        newhashLink -> value = v;
        newhashLink -> next = ht->table[hashIndex];
        ht->table[hashIndex] = newhashLink;
        ht->count++;
    }
    
}



ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
    int hash = stringHash1(k);
    int hashIndex = (int) (labs(hash) % ht->tableSize);
    struct hashLink * cur = ht->table[hashIndex];
    assert(ht);
    while(cur != 0){
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
    int hashIndex  = (int) (labs(hash) % ht->tableSize);
    
    struct hashLink * cur = ht->table[hashIndex];
    assert(ht);
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
    int hashIndex = (int) (labs(hash) % ht->tableSize);
    struct hashLink *cur, *last;
    assert(ht);
    if(containsKey(ht,k)){
      cur = ht->table[hashIndex];
      last = ht->table[hashIndex];
       while(cur){
          if(EQ(*(cur->key), *k)){
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
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
    assert(ht);
    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    assert(ht);
    return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    int a = 0;
    int i;
    assert(ht);
    for(i = 0; i < ht->tableSize; i++){
        if(ht->table[i] == NULL)
            a++;
    }
    return a;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
    assert(ht);
    return (float) (ht->count / ht->tableSize);
}

void printMap (struct hashMap * ht)
{
    int i;
    struct hashLink *temp;
    for(i = 0;i < capacityMap(ht); i++){
        temp = ht->table[i];
        if(temp != 0) {
            printf("\nBucket Index %d -> ", i);
        }
        while(temp != 0){
            printf("Key:%s|", temp->key);
            printf("val: %d\n", temp->value);
            printf(" -> ");
            temp=temp->next;			
        }		
    }
}

