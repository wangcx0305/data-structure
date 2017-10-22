/* CS261- HW1 - Program2.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    *a = *a + 1;
    
    /* Decrement  b */
    *b = *b + 1;
    
    /* Assign a-b to c */
    c = *a - *b;
    
    /* Return c */
    return c;
}

int main(){
    /* To generate same x, y and z each time running the code */
    srand(0403);
     
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand()%11, y = rand()%11, z = rand()%11;
    
    /* Print the values of x, y and z */
    printf("the values of x, y and z are: %d %d %d\n", x, y, z);
    
    /* Call foo() appropriately, passing x,y,z as parameters */
    int fooreturn = foo(&x, &y, z);
    
    /* Print the values of x, y and z */
    printf("after calling foo, the values of x, y and z are: %d %d %d\n", x, y, z);
    
    /* Print the value returned by foo */
    printf("the value returned by foo() is: %d\n", fooreturn);
    
    /* Is the return value different than the value of z?  Why? */
    /* The return value id different than the value of z. C is pass-by-value, we only modifying a copy of z not z itself. If we want to modify a variable in a function, the pointer should be passed.*/
    
    return 0;
}


