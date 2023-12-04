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

    // Read matrix properties from the first readable line of the .mtx file
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

    // Initialize row_ptr to zeros
    for (int i = 0; i <= matrix->num_rows; i++) {
        matrix->row_ptr[i] = 0;
    }

    int row, col;
    double value;

    for (int i = 0; i < matrix->num_non_zeros; i++) {
        if (fscanf(file, "%d %d %lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error reading matrix entry #%d from file %s\n", i + 1, filename);
            fclose(file);
            exit(1);
        }
        // Fill data and col_ind arrays
        matrix->csr_data[i] = value;
        matrix->col_ind[i] = col - 1; // Adjust for 0-based indexing

        // Increment count for the current row
        matrix->row_ptr[row]++;
    }
    // Calculate the cumulative sum to get the final row_ptr (at the end of reading each row)
    for (int i = 1; i <= matrix->num_rows; i++) {
        matrix->row_ptr[i] += matrix->row_ptr[i - 1];
    }
    fclose(file);  
}

//Sparse matrix multiplication 
void spmv_csr(const CSRMatrix *A, const double *x, double *y) {
    for (int i = 0; i < A->num_rows; i++) {
        y[i] = 0.0;
        // A->row_ptr[i] is the starting index of the ith row in the col_ind and csr_data arrays
        // A->row_ptr[i + 1] indicates the end of the ith row (the starting index of the next row)
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) {
            y[i] += A->csr_data[j] * x[A->col_ind[j]];
        }
        // Multiplies the non-zero element A->csr_data[j] from the matrix to the corresponding value in 
        //the vector x at index A->col_ind[j]
    }
}

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

//Function to solve the linear system Ax = b - Conjugate Gradient Method
double solver(const CSRMatrix *A, const double *b, double *x) {
    int n = A->num_rows;

    // Allocate memory for temporary vectors
    double *r = (double *)malloc(n * sizeof(double));
    double *p = (double *)malloc(n * sizeof(double));
    double *Ap = (double *)malloc(n * sizeof(double));

    // Check for memory allocation errors
    if (r == NULL || p == NULL || Ap == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // Initialize vectors
    compute_residual(A, x, b, r);  // r = b - Ax
    for (int i = 0; i < n; ++i) {
        p[i] = r[i];         // p = r (initially)
    }

    // Conjugate Gradient iteration - defining all necessary variables
    const int max_iter = 100000;  // Set a maximum number of iterations
    const double tolerance = 1e-25;  // Set a tolerance for convergence 
    double alpha, beta;
    double r_norm, r_norm_old = 1.0;

    for (int iter = 0; iter < max_iter; ++iter) {
        // Ap = A * p
        spmv_csr(A, p, Ap);

        // initializing and calculating the values of r'*r and p'*Ap
        double r_dot_r = 0.0;
        double p_dot_Ap = 0.0;
        for (int i = 0; i < n; ++i) {
            r_dot_r += r[i] * r[i];
            p_dot_Ap += p[i] * Ap[i];
        }

        if (fabs(p_dot_Ap) < tolerance) {
            alpha = 0.0;
        } else {
            alpha = r_dot_r / p_dot_Ap;
        }

        // x = x + alpha * p
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
        }

        // r = r - alpha * Ap
        for (int i = 0; i < n; ++i) {
            r[i] -= alpha * Ap[i];
        }

        // Check for NaN in vectors and set to zero
        for (int i = 0; i < n; ++i) {
            if (isnan(x[i]) || isnan(r[i]) || isnan(p[i]) || isnan(Ap[i])) {
                x[i] = 0.0;
                r[i] = 0.0;
                p[i] = 0.0;
                Ap[i] = 0.0;
            }
        }

        // Check for convergence
        r_norm = compute_norm(r, n);
        if (r_norm < tolerance) {
            printf("Converged after %d iterations \n", iter+1);
            return(r_norm);
            break;  // Convergence achieved
        }

        // beta = (r_new' * r_new) / (r_old' * r_old)
        beta = r_norm * r_norm / r_norm_old;

        // p = r + beta * p - update the search direction 
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
    return(0);
}
