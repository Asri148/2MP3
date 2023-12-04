#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    // Handle any error in input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    //Read the file
    const char *filename = argv[1];

    CSRMatrix A = {0}; // Initialize all members to zero
    ReadMMtoCSR(filename, &A);

    //Print the Row Pointer
    printf("Row Pointer: ");
    for (int i = 0; i < A.num_rows + 1; i++)
        printf("%d ", A.row_ptr[i]);
    printf("\n");

    // Print the column index
    printf("Column Index (adjusted to begin from zero): ");
    for (int i = 0; i < A.num_non_zeros; i++)
        printf("%d ", A.col_ind[i]);
    printf("\n");

    // Print the values
    printf("Values: ");
    for (int i = 0; i < A.num_non_zeros; i++)
        printf("%0.4f ", A.csr_data[i]);
    printf("\n");

    // Initializing vector b (in Ax=b)
    double *b = (double *)malloc(A.num_rows * sizeof(double));
    if (b == NULL)
    {
        fprintf(stderr, "Memory allocation error for vector b\n");
        // Handle the error (return or exit)
    }
    // Set all elements of b to 1
    for (int i = 0; i < A.num_rows; ++i)
    {
        b[i] = 2.0;
    }
    

    // Initiating vector x (solution)
    double *x = (double *)malloc(A.num_cols * sizeof(double));
    if (x == NULL)
    {
        fprintf(stderr, "Memory allocation error for vector x\n");
        // Handle the error (return or exit)
        free(b);
        return 1;
    }
    
    // Initiating all the variables necessary to print CPU time
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // Solving Ax=b
    double r_norm = solver(&A, b, x);
    
    // Ending timer and computing the time taken to solve Ax=b
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the results
    printf("The matrix name: %s\n", filename);
    printf("The dimension of the matrix: %d by %d\n", A.num_rows, A.num_cols);
    printf("Number of non-zeros: %d\n", A.num_non_zeros);
    printf("CPU time taken to solve Ax=b: %f seconds\n", cpu_time_used);
    printf("The Residual Normal: %f\n", r_norm);

    // Free allocated memory
    free(A.csr_data);
    free(A.col_ind);
    free(A.row_ptr);
    free(b);
    free(x);
    return 0;
}
