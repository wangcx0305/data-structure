/* CS261- HW1 - Program1.c */
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
    /*Print the value of iptr*/
    printf("the value of iptr: %d\n", *iptr);
    
    /*Print the address pointed to by iptr*/
    printf("the address pointed to by iptr: %p\n", iptr);
    
    /*Print the address of iptr itself*/
    printf("the address of iptr itself: %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
    int x = 2;
    
    /*print the address of x*/
    printf("the address of x: %p\n", &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*print the value of x*/
    printf("the value of x: %d\n", x);
    
    return 0;
}
