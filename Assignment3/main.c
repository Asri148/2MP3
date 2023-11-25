#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    // <Handle the inputs here>
    // Handle any error in input
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
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

    // Initiating vector x (solution)
    double *x = (double *)malloc(A.num_cols * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation error for vector x\n");
        // Handle the error (return or exit)
        free(b);
        return 1;
    }
    //Initiating all the variables necessary to print CPU time 
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    //Solving Ax=b
    solver(&A, b, x);

    // Ending timer and computing the time taken to solve Ax=b
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    double residual_norm = compute_residual_norm(&A, x, b);

    // Print the results
    printf("The matrix name: %s\n", filename);
    printf("The dimension of the matrix: %d by %d\n", A.num_rows, A.num_cols);
    printf("Number of non-zeros: %d\n", A.num_non_zeros);
    printf("CPU time taken to solve Ax=b: %f seconds\n", cpu_time_used);
    printf("Residual Norm: %d\n", residual_norm);

    // Free allocated memory
    free(A.csr_data);
    free(A.col_ind);
    free(A.row_ptr);
    free(b);
    free(x);

    return 0;
}
