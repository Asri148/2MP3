#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "functions.h"


//Comparison function for qsort to sort the column indecies to match the row_ptr array - Used in ReadMMtoCSR
int comp_entries_values(const void *a, const void *b) {
    return ((Vals *)a)->row == ((Vals *)b)->row ?
           ((Vals *)a)->column - ((Vals *)b)->column :
           ((Vals *)a)->row - ((Vals *)b)->row;
}

//Read .mtx file to CSR format
void ReadMMtoCSR(const char *filename, CSRMatrix *matrix) {
    //open file and if there is an error exit
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    //Skip all header lines 
    char line[400];
    while (fgets(line, sizeof(line), file) != NULL && line[0] == '%') {
        // Skip any commented lines in the .mtx file
    }

    //Store the matrix properties from the first line in the .mtx file and if there is an error exit
    sscanf(line, "%d %d %d", &(matrix->num_rows), &(matrix->num_cols), &(matrix->num_non_zeros));

    matrix->csr_data = (double *)malloc(matrix->num_non_zeros * sizeof(double));
    matrix->col_ind = (int *)malloc(matrix->num_non_zeros * sizeof(int));
    matrix->row_ptr = (int *)malloc((matrix->num_rows + 1) * sizeof(int));

    if (matrix->csr_data == NULL || matrix->col_ind == NULL || matrix->row_ptr == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    //Initialize variables to use in fscanf
    int row, col;
    double value;

    //Read all non-zero matrix entries and if there is an error exit
    for (int i = 0; i < matrix->num_non_zeros; i++) {
        if (fscanf(file, "%d %d %lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error reading matrix entry #%d from file %s\n", i + 1, filename);
            fclose(file);
            exit(1);
        }

        matrix->csr_data[i] = value;
        matrix->col_ind[i] = col;
        matrix->row_ptr[row]++;
    }

    //Calculate the cumulative sum to get the final row_ptr (at the end of reading each row)
    for (int i = 1; i <= matrix->num_rows; i++) {
        matrix->row_ptr[i] += matrix->row_ptr[i - 1];
    }

    //Create an array of Entry structures to store matrix entries temporarily and if there is an error exit
    Vals *entries = (Vals *)malloc(matrix->num_non_zeros * sizeof(Vals));

    if (entries == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    //Read all non-zero matrix entries again to fill the entries array
    fseek(file, 0, SEEK_SET);  //Reset file pointer to the beginning

    //Skip all header lines 
    while (fgets(line, sizeof(line), file) != NULL && line[0] == '%') {
        //Skip any commented lines in the .mtx file
    }

    //For the number of non-zero values in the matrix store the values in 
    //their respective properties in the entries structure
    for (int i = 0; i < matrix->num_non_zeros; i++) {
        //If there is an error in reading the .mtx file exit
        if (fscanf(file, "%d %d %lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error reading matrix entry #%d from file %s\n", i + 1, filename);
            fclose(file);
            exit(1);
        }

        entries[i].row = row;
        entries[i].column = col-1;
        entries[i].value = value;
    }

    //Close the opened file
    fclose(file);

    //Sort entries based on row order to patch with the enties in row_ptr
    qsort(entries, matrix->num_non_zeros, sizeof(Vals), comp_entries_values);

    //Rearrange the data to store it according to row
    for (int i = 0; i < matrix->num_non_zeros; i++) {
        matrix->col_ind[i] = entries[i].column;
        matrix->csr_data[i] = entries[i].value;
    }

    //Free memory for temporary structures
    free(entries);  
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

//Function to compute the residual r = Ax - b
void compute_residual(const CSRMatrix *A, const double *x, const double *b, double *r) {
    //perform multiplication (A*x) using the multiplication function
    spmv_csr(A, x, r);  // r = Ax
    //for each row in vector 'r' (result of multiplication that has the same number of rows as the matrix A)
    for (int i = 0; i < A->num_rows; ++i) {
        r[i] -= b[i];   // r = Ax - b
    }
}

//Function to compute the norm of a vector
double compute_norm(const double *vector, int size) {
    //initiate norm_value to be zero
    double norm = 0.0;
    //iterate through all elements in the given vector and square it. Then and add it to norm
    for (int i = 0; i < size; ++i) {
        norm += vector[i] * vector[i];
    }
    //take the square root of norm to get the magnitude of the vector given as input
    return sqrt(norm);
}

//Function to solve the linear system Ax = b using Conjugate Gradient Method
double solver(const CSRMatrix *A, const double *b, double *x) {
    int n = A->num_rows;

    //Allocate memory for the temporary vectors
    double *r = (double *)malloc(n * sizeof(double));
    double *p = (double *)malloc(n * sizeof(double));
    double *Ap = (double *)malloc(n * sizeof(double));

    //Check for and memory allocation errors and exit if an error occurs
    if (r == NULL || p == NULL || Ap == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    //Initialize vectors and compute the initial residual vector 'r'
    compute_residual(A, x, b, r);  //r = Ax - b
    for (int i = 0; i < n; ++i) {
        p[i] = r[i]; //p (the initial serach direction) = r (initially)
    }

    // For Conjugate Gradient Method iteration(s) - defining all necessary variables
    const int max_iter = 100000;  // Set a maximum number of iterations
    const double tolerance = 1e-15;  // Set a tolerance for convergence - if the magnitude of the residual is less than this tolerence the system is considered solved
    double alpha, beta;
    double r_norm, r_norm_old = 1.0; 

    for (int iter = 0; iter < max_iter; ++iter) {
        //Ap = A * p
        spmv_csr(A, p, Ap);

        //initializing and calculating the values of r'*r and p'*Ap
        double r_dot_r = 0.0;
        double p_dot_Ap = 0.0;
        for (int i = 0; i < n; ++i) {
            r_dot_r += r[i] * r[i]; //r'*r
            p_dot_Ap += p[i] * Ap[i]; //p'*Ap
        }

        //Checking for division by zero (really small number)
        if (fabs(p_dot_Ap) < tolerance) {
            alpha = 0.0;
        } else {
            alpha = r_dot_r / p_dot_Ap;
        }

        //Updating the solution vector x
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i]; //x(i+1) = x(i) + alpha * p 
        }

        //Updating the residual vector r
        for (int i = 0; i < n; ++i) {
            r[i] -= alpha * Ap[i]; //r = r - alpha * Ap
        }

        //Check for convergence 
        //if the norm of the residual is less than the tolerence convergence is achieved (a.k.a the system is solved)
        r_norm = compute_norm(r, n);
        if (r_norm < tolerance) {
            printf("Converged after %d iterations \n", iter+1);
            return(r_norm);
            break;  // exit function as convergence has been achieved
        }

        //if convergence is not acheieved
        //beta = (r_new' * r_new) / (r_old' * r_old)
        beta = r_norm * r_norm / r_norm_old;

        //p = r + beta * p - update the search direction 
        for (int i = 0; i < n; ++i) {
            p[i] = r[i] + beta * p[i];
        }

        //Update the old residual norm
        r_norm_old = r_norm;
    }

    //Free the memory allocated to the temporary vectors
    free(r);
    free(p);
    free(Ap);
    return(0);
}
