/* CS261- HW1 - Program6.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
    return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
    return ch-'A'+'a';
}

void lowerCase(char* word){
    /* Convert to lower case letters */
     
    unsigned i;
    long len = sizeof(word)/sizeof(char);
    
    for(i = 0; i < len; i++){
        
        if(word[i] >= 'A' && word[i] <= 'Z') word[i] = toLowerCase(word[i]);
        
    }
    
    
}

void upperCase(char* word){
    /* Convert to upper case letters */
    unsigned i;
    long len = sizeof(word)/sizeof(char);
    
    for(i = 0; i < len; i++){
        
        if(word[i] >= 'a' && word[i] <= 'z') word[i] = toUpperCase(word[i]);
        
    }
    
}



int main(){
    
   /* Input a word and flag */
    char* word= malloc(sizeof(char*)*100);
    int flag;
    
    
    printf("input word:\n");
    scanf("%s", word);
    
    printf("input flag:\n");
    scanf("%d", &flag);
    
    /* Print the input word and flag */
    printf("the word is: %s\n", word);
    printf("the flag is: %d\n", flag);
    
   if(flag == 0) lowerCase(word);
    
   if(flag == 1) upperCase(word);
    
    /* Print the new word */
    
    printf("The transfer word is: %s\n", word);
    
    return 0;
}
