#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "functions.h"

void ReadMMtoCSR(const char *filename, CSRMatrix *matrix){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }
    // Read matrix properties
    fscanf(file, "%*s %*s %*s %*s %d %d %d", &(matrix->num_rows), &(matrix->num_cols), &(matrix->num_non_zeros));

    // Allocate memory
    matrix->csr_data = (double *)malloc(matrix->num_non_zeros * sizeof(double));
    matrix->col_ind = (int *)malloc(matrix->num_non_zeros * sizeof(int));
    matrix->row_ptr = (int *)malloc((matrix->num_rows + 1) * sizeof(int));

    // Read matrix entries
    for (int i = 0; i < matrix->num_non_zeros; i++) {
        fscanf(file, "%d %d %lf", &(matrix->row_ptr[i]), &(matrix->col_ind[i]), &(matrix->csr_data[i]));
        // Matrix market format is 1-based index, convert to 0-based index
        matrix->row_ptr[i]--;
        matrix->col_ind[i]--;
    }
    matrix->row_ptr[matrix->num_non_zeros] = matrix->num_non_zeros;

    fclose(file);
}

void spmv_csr(const CSRMatrix *A, const double *x, double *y){
    for (int i = 0; i < A->num_rows; i++) {
        y[i] = 0.0;
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) {
            y[i] += A->csr_data[j] * x[A->col_ind[j]];
        }
    }
}

//Function to solve the linear system Ax = b
//void solver(const CSRMatrix *A, const double *b, double *x) {
    // Implement your solver algorithm here
    // ...
//}

// Function to compute the residual r = Ax - b
void compute_residual(const CSRMatrix *A, const double *x, const double *b, double *r) {
    spmv_csr(A, x, r);  // r = Ax
    for (int i = 0; i < A->num_rows; ++i) {
        r[i] -= b[i];   // r = Ax - b
    }
}

// Function to compute the norm of a vector
double compute_norm(const double *vector, int size) {
    double norm = 0.0;
    for (int i = 0; i < size; ++i) {
        norm += vector[i] * vector[i];
    }
    return sqrt(norm);
}