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

    // Skip the header lines
    char line[400];
    while (fgets(line, sizeof(line), file) != NULL && line[0] == '%') {
        // Skip comment lines
    }
    // Read matrix properties
    sscanf(line, "%d %d %d", &(matrix->num_rows), &(matrix->num_cols), &(matrix->num_non_zeros));

    // Allocate memory
    matrix->csr_data = (double *)malloc(matrix->num_non_zeros * sizeof(double));
    matrix->col_ind = (int *)malloc(matrix->num_non_zeros * sizeof(int));
    matrix->row_ptr = (int *)malloc((matrix->num_rows + 1) * sizeof(int));

    // Check if memory allocation is successful
    if (matrix->csr_data == NULL || matrix->col_ind == NULL || matrix->row_ptr == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

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

//Sparse matrix multiplication 
void spmv_csr(const CSRMatrix *A, const double *x, double *y){
    for (int i = 0; i < A->num_rows; i++) {
        y[i] = 0.0;
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) {
            y[i] += A->csr_data[j] * x[A->col_ind[j]];
        }
    }
}

//Function to solve the linear system Ax = b - Conjugate Gradient Method
void solver(const CSRMatrix *A, const double *b, double *x) {
    // Implement your solver algorithm here
    int n = A->num_rows;

    // Allocate memory for temporary vectors
    double *r = (double *)malloc(n * sizeof(double));
    double *p = (double *)malloc(n * sizeof(double));
    double *Ap = (double *)malloc(n * sizeof(double));

    // Initialize vectors
    spmv_csr(A, x, r);  // r = Ax
    for (int i = 0; i < n; ++i) {
        r[i] = b[i] - r[i];  // r = b - Ax
        p[i] = r[i];         // p = r (initially)
    }

    // Conjugate Gradient iteration
    const int max_iter = 1000;  // Set a maximum number of iterations
    const double tolerance = 1e-6;  // Set a tolerance for convergence
    double alpha, beta;
    double r_norm, r_norm_old = 1.0;

    for (int iter = 0; iter < max_iter; ++iter) {
        // Ap = A * p
        spmv_csr(A, p, Ap);

        // alpha = (r' * r) / (p' * Ap)
        double r_dot_r = 0.0;
        double p_dot_Ap = 0.0;
        for (int i = 0; i < n; ++i) {
            r_dot_r += r[i] * r[i];
            p_dot_Ap += p[i] * Ap[i];
        }
        alpha = r_dot_r / p_dot_Ap;

        // x = x + alpha * p
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
        }

        // r = r - alpha * Ap
        for (int i = 0; i < n; ++i) {
            r[i] -= alpha * Ap[i];
        }

        // Check for convergence
        r_norm = compute_norm(r, n);
        if (r_norm < tolerance) {
            break;  // Convergence achieved
        }

        // beta = (r_new' * r_new) / (r_old' * r_old)
        beta = r_norm * r_norm / r_norm_old;

        // p = r + beta * p
        for (int i = 0; i < n; ++i) {
            p[i] = r[i] + beta * p[i];
        }

        // Update the old residual norm
        r_norm_old = r_norm;
    }

    // Free temporary vectors
    free(r);
    free(p);
    free(Ap);
}

// Function to compute the norm of the residual vector r = Ax - b
double compute_residual_norm(const CSRMatrix *A, const double *x, const double *b) {
    int n = A->num_rows;
    
    // Allocate memory for the residual vector
    double *r = (double *)malloc(n * sizeof(double));
    if (r == NULL) {
        fprintf(stderr, "Memory allocation error for residual vector r\n");
        // Handle the error (return or exit)
        return -1.0; // Return a negative value to indicate an error
    }

    // Compute the residual vector r = Ax - b
    spmv_csr(A, x, r);  
    for (int i = 0; i < n; ++i) {
        r[i] -= b[i];
    }

    // Compute the norm of the residual vector
    double norm = 0.0;
    for (int i = 0; i < n; ++i) {
        norm += r[i] * r[i];
    }
    norm = sqrt(norm);

    // Free allocated memory for the residual vector
    free(r);
    return norm;
}