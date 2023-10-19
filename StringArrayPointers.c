#include <stdio.h>

int main (){
    // Ragged array of strings
    char *names[] = {"Anne-Marie", "Anna", "Mahmoud", "Kian", "Raouf", "Nikki"};

    // Accessing and printing the elements and their lengths
    for (int i = 0; i < 6; i ++){
    int length = 0;
    while (names [i][length] !='\0'){
        length++;
        }
    printf ("Name %d: %s ( Length : %d) - After ’\\0’: '%c'\n", i+1, names [i], length, names[i][length]) ;
    }
}