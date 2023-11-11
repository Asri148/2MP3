#include <math.h>
#include "functions.h"
// Define M_PI and M_E if not defined
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#ifndef M_E
#define M_E  (2.71828182845904523536028747135266250)
#endif

// Do know change anything in this file. You will not submit this file.

// Define the objective function function for optimization

double Objective_function(int NUM_VARIABLES, double x[NUM_VARIABLES])
{
    // While the objective function could be anything here it is to minimize Ackley function
    double sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        sum1 += x[i] * x[i];
        sum2 += cos(2.0 * M_PI * x[i]);
    }
    return -20.0 * exp(-0.2 * sqrt(sum1 / NUM_VARIABLES)) - exp(sum2 / NUM_VARIABLES) + 20.0 + M_E;
}