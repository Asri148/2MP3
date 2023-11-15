#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int* soldiers = NULL;
    int N; // Total number of soldiers
    int x;
    int sumDecimatedAges = 0;

    // Read the total number of soldiers
    scanf("%d", &N);

    // Allocate memory for the army
    soldiers = (int*)malloc(sizeof(int) * N);

    // Check if memory allocation was successful
    if (soldiers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read the ages of soldiers
    for (x = 0; x < N; x++) {
        scanf("%d", &soldiers[x]);
    }

    // Calculate the number of soldiers to decimate (last 10%)
    int decimationSize = N / 10;

    // Reallocate memory to decimate the army
    soldiers = (int*)realloc(soldiers, sizeof(int) * (N - decimationSize));

    // Check if memory reallocation was successful
    if (soldiers == NULL) {
        printf("Memory reallocation failed.\n");
        free(soldiers); // Free the original memory before exiting
        return 1;
    }

    // Calculate the sum of decimated soldiers' ages
    for (x = N - decimationSize; x < N; x++) {
        sumDecimatedAges += soldiers[x];
    }

    // Print the list of soldiers
    printf("List of soldiers:\n");
    for (x = 0; x < N - decimationSize; x++) {
        printf("%d ", soldiers[x]);
    }
    printf("\n");

    // Print the sum of decimated soldiers' ages
    printf("Total age of decimated soldiers: %d\n", sumDecimatedAges);

    // Free the allocated memory
    free(soldiers);

    return 0;
}
