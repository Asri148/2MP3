// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double generate_random(double min, double max){
    // implement a function to return a value between min and max
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

unsigned int generate_int(){
    // implement a function to return a random integer value
    return rand();
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // randomly initialize for all values in "population[i][j]""
    srand((unsigned int)time(NULL));
    for (int i = 0; i < POPULATION_SIZE; ++i){
        for (int j = 0; j < NUM_VARIABLES; ++j){
            population[i][j] = generate_random(Lbound[j], Ubound[j]);
        }
    }  
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
     for (int i = 0; i < POPULATION_SIZE; i++){
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
     for (int i = 0; i < POPULATION_SIZE; i += 2){
        if (generate_random(0, 1) < crossover_rate){
            // Perform crossover for individuals with indices i and i+1
            int crossover_point = generate_int() % NUM_VARIABLES;
            for (int j = 0; j < crossover_point; j++){
                new_population[i][j] = population[i][j];
                new_population[i + 1][j] = population[i + 1][j];
            }
            for (int j = crossover_point; j < NUM_VARIABLES; j++){
                new_population[i][j] = population[i + 1][j];
                new_population[i + 1][j] = population[i][j];
            }
        }
        else{
            // If no crossover, copy parents to the new population
            for (int j = 0; j < NUM_VARIABLES; j++){
                new_population[i][j] = population[i][j];
                new_population[i + 1][j] = population[i + 1][j];
            }
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate){
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/
     for (int i = 0; i < POPULATION_SIZE; i++){
        for (int j = 0; j < NUM_VARIABLES; j++){
            if (generate_random(0, 1) < mutate_rate){
                // Mutate the gene
                new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
            }
            else{
                // Keep the gene unchanged
                new_population[i][j] = population[i][j];
            }
        }
    }
}