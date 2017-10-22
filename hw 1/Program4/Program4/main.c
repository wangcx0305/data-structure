/* CS261- HW1 - Program4.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <math.h>

void sort(int* number, int n){
    /*Sort the given array number , of length n*/
    int i, j, elem;
    
    for(i = 1; i < n; i++){
        elem = number[i];
        for(j = i - 1; j >= 0 && elem < number[j]; j--){
            number[j+1] = number[j];
        }
        
        number[j+1] = elem;
        
    }
}

int main(){

    
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    
    /*Allocate memory for an array of n integers using malloc.*/
    int* array = malloc(sizeof(int) * n);
    
    /*Fill this array with random numbers, using rand().*/
    for(int i = 0; i < n; i++){
        array[i] = rand() % 100; /*I use number between 0 and 99*/
    }
    
    /*Print the contents of the array.*/
    printf("the contents of the array is:\n");
    for(int i = 0; i < n; i++){
        printf("%d\n",array[i]);
    }
    
    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    
    /*Print the contents of the array.*/
    printf("the contents of the array after sorting is:\n");
    for(int i = 0; i < n; i++){
        printf("%d\n",array[i]);
    }
    
    return 0;
}
