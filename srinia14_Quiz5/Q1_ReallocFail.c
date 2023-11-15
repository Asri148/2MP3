#include <stdio.h>
#include <stdlib.h>

int main() {
    // Fix ptr so that it can be correctly reallocated memory.
    int arr[] = {2, 6, 14};
    int x;
    int* ptr = (int*)malloc(sizeof(int) * 3); // Allocate dynamic memory
    for (x = 0; x < 3; x++)
        ptr[x] = arr[x]; // Copy values from arr to dynamic memory

    int* ptr_new = (int*)realloc(ptr, sizeof(int) * 4);
    if (ptr_new == NULL) {
        // Handle realloc failure
        free(ptr);
        return 1;
    }

    // DO NOT CHANGE ANYTHING BELOW THIS LINE
    ptr_new = (int*)realloc(ptr, sizeof(int) * 4);
    *(ptr_new + 3) = 30;

    for (x = 0; x < 4; x++)
        printf("%d ", *(ptr_new + x));
    printf("\n");

    free(ptr_new);
    return 0;
}