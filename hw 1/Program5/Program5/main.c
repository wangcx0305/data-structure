/* CS261- HW1 - Program5.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct student{
    char initials[2];
    int score;
};

struct student* allocate(int n){
    /*Allocate memory for ten students*/
    struct student* students = malloc(sizeof(struct student*) * n);
    
    /*return the pointer*/
    return students;
}

void generate(struct student* students, int n){
    /*Generate random initials and scores for ten students.
     The two initial letters must be capital and must be between A and Z.
     The scores must be between 0 and 100*/
    for(int i = 0; i < n; i++){
        students[i].initials[0] = rand()%26 + 'A';
        students[i].initials[1] = rand()%26 + 'A';
        students[i].score = rand()%101;
    }
    
}

void output(struct student* students, int n){
    /*Output information about the ten students in the format:
     1. Initials  Score
     2. Initials  Score
     ...
     n. Initials Score*/
    for(int i = 0; i < n; i++){
        printf("%d. %c%c %d\n", i+1, students[i].initials[0], students[i].initials[1], students[i].score);
    }
}

void sort(struct student* students, int n){
    /*Sort the n students based on their initials*/
    char elem1, elem2;
    int i, j, score;
    
    for(i = 1; i < n; i++){
        elem1 = students[i].initials[0];
        elem2 = students[i].initials[1];
        score = students[i].score;
        
        for(j = i - 1; j >= 0 && (elem1 < students[j].initials[0] || (elem1 == students[j].initials[0] && elem2 < students[j].initials[1])); j--){
            students[j+1] = students[j];
            
        }
        students[j+1].initials[0] = elem1;
        students[j+1].initials[1] = elem2;
        students[j+1].score = score;
    }
    
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 30;
    
    assert(n != 0);
    
    /*Allocate memory for n students using malloc.*/
    struct student* stud = NULL;
    
    stud = allocate(n);
    
    /*Generate random IDs and scores for the n students, using rand().*/
    generate(stud, n);
    
    /*Print the contents of the array of n students.*/
    printf("The contents of initial array are:\n");
    output(stud, n);
    
    /*Pass this array along with n to the sort() function*/
    sort(stud, n);
    
    /*Print the contents of the array of n students.*/
    printf("The contents of array after sorting are:\n");
    output(stud, n);
    
    return 0;
}
