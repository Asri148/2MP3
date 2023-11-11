// All the necessary libraries and header file 
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[]){
    // Handle the possible errors in input data given by the user and say how to execute the code>
    if (argc != 6){
        printf("Usage: %s <POPULATION SIZE> <MAX GENERATIONS> <crossover rate> <mutate rate> <stop criteria>\n", argv[0]);
        return 1;
    }
    // Assign all inputs given by the user argv[i]>
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);

    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    // ###################################################################################

    // Initiating all the variables necessary to print CPU time 
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // Initialize the random number generator seed
    srand(time(NULL));

    // Declaring the arrays for the population and fitness values
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];

    //Call generate_population function to initialize the "population" like:
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);

    // Iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    int best_index = 0; 
    for (int generation = 0; generation < MAX_GENERATIONS; generation++)
    {
        //Compute the fitness values using objective function for
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

        //Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria>
        double best_fitness = fitness[0];
        for (int x = 1; x < POPULATION_SIZE; x++){
            if (fitness[x] < best_fitness){
                best_fitness = fitness[x];
                best_index = x;
            }
        }
        //Print the generation number and best fitness value
        printf("Generation %d: Best Fitness = %lf\n", generation, best_fitness);
        //Check stopping criteria
        if (best_fitness < stop_criteria){
            printf("Stopping criteria met. Best solution found.\n");
            break;
        }
        //Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);
        // Here call the mutation function>
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
    }
    // ###################################################################################
    // Print the input parameters
    printf("Lower Bounds: [%.2lf, %.2lf]\n", Lbound[0], Lbound[1]);
    printf("Upper Bounds: [%.2lf, %.2lf]\n", Ubound[0], Ubound[1]);
    printf("Number of Variables: %d\n", NUM_VARIABLES);
    printf("Population Size: %d\n", POPULATION_SIZE);
    printf("Max Number of Generations: %d\n", MAX_GENERATIONS);
    printf("Crossover Rate: %.2lf\n", crossover_rate);
    printf("Mutation Rate: %.2lf\n", mutate_rate);
    printf("Stopping Criteria: %.15lf\n", stop_criteria);
    // ###################################################################################
    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################
    // Print the best solution and objective function value for the best solution
    printf("Best Solution:\n");
    for (int i = 0; i < NUM_VARIABLES; i++){
        printf("Variable %d: %lf\n", i, population[best_index][i]);
    }
    printf("Objective Function Value: %lf\n", fitness[best_index]);
    return 0;
}