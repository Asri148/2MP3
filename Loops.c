#include <stdio.h>
          
    int main() 
    {
        int x = 5;
        printf("Original value: %d\n", x);
              
        printf("After x++: %d\n", x++);  // Postfix increment
        printf("Print x after x++ is applied: %d\n", x);
        printf("Print x again: %d\n", x);
        printf("After ++x: %d\n", ++x);  // Prefix increment
              
        printf("After x--: %d\n", x--);  // Postfix decrement
        printf("Print x after x-- is applied: %d\n", x);
        printf("Print x again: %d\n", x);
        printf("After --x: %d\n", --x);  // Prefix decrement  
        }
    