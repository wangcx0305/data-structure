/*	stackapp.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"
#include <assert.h>


/* ***************************************************************
 Using stack to check for unbalanced parentheses.
 ***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
 */
char nextChar(char* s)
{
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    if ( c == '\0' )
        return 0;
    else
        return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
 */
int isBalanced(char* s)
{
    /* FIXME: You will write this function */
    assert(s != NULL);
    char c = nextChar(s);

    
    DynArr * v;
    v = newDynArr(10);
    
    while(c != '\0'){
        
        if(c == '(' || c == '{' || c == '['){
            pushDynArr(v, c);
        }
        
        
       if(c == ')'){
            if(isEmptyDynArr(v) || topDynArr(v) != '('){
                
                return 0;
                break;
            }
            else popDynArr(v);
        }
        
       if(c == '}'){
            if(isEmptyDynArr(v) || topDynArr(v) != '{'){
                
                return 0;
                break;
            }
            else popDynArr(v);
        }
        
        if(c == ']'){
            if(isEmptyDynArr(v) || topDynArr(v) != '['){
                
                return 0;
                break;
            }
            else popDynArr(v);
        }
    
        c = nextChar(s);
        
    }
    
    if(isEmptyDynArr(v))
        return 1;
    else
        return 0;
}


int main(int argc, char* argv[]){
 
	printf("Assignment 2\n");
	
	char* s=argv[1];
	int res;
	
	res = isBalanced(s);
 
	if (res)
 printf("The string %s is balanced\n",s);
	else
 printf("The string %s is not balanced\n",s);
	
    return 0;
    
 }









