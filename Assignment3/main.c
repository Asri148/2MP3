#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    // <Handle the inputs here>
    const char *filename = argv[1];

    CSRMatrix A = {0};  // Initialize all members to zero
    ReadMMtoCSR(filename, &A);

    // Initializing vector b (in Ax=b)
    double *b = (double *)malloc(A.num_rows * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation error for vector b\n");
        // Handle the error (return or exit)
    }

    // Set all elements of b to 1
    for (int i = 0; i < A.num_rows; ++i) {
        b[i] = 1.0;
    }

    // <The rest of your code goes here>

    // Print the results
    printf("The matrix name: %s\n", filename);
    printf("The dimension of the matrix: %d by %d\n", A.num_rows, A.num_cols);
    printf("Number of non-zeros: %d\n", A.num_non_zeros);

    // Free allocated memory
    free(A.csr_data);
    free(A.col_ind);
    free(A.row_ptr);
    free(b);

    return 0;
}
