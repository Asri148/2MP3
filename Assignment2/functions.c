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
    for (int x = 0; x < POPULATION_SIZE; ++x){
        for (int y = 0; y < NUM_VARIABLES; ++y){
            population[x][y] = generate_random(Lbound[x], Ubound[y]);
        }
    }  
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
     for (int x = 0; x < POPULATION_SIZE; x++){
        fitness[x] = Objective_function(NUM_VARIABLES, population[x]);
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
     for (int x = 0; x < POPULATION_SIZE; x += 2){
        if (generate_random(0, 1) < crossover_rate){
            // Perform crossover for individuals with indices i and i+1
            int crossover_point = generate_int() % NUM_VARIABLES;
            for (int y = 0; y < crossover_point; y++){
                new_population[x][y] = population[x][y];
                new_population[x + 1][y] = population[x + 1][y];
            }
            for (int y = crossover_point; y < NUM_VARIABLES; y++){
                new_population[x][y] = population[x + 1][y];
                new_population[x + 1][y] = population[x][y];
            }
        }
        else{
            // If no crossover, copy parents to the new population
            for (int y = 0; y < NUM_VARIABLES; y++){
                new_population[x][y] = population[x][y];
                new_population[x + 1][y] = population[x + 1][y];
            }
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate){
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/
     for (int x = 0; x < POPULATION_SIZE; x++){
        for (int y = 0; y < NUM_VARIABLES; y++){
            if (generate_random(0, 1) < mutate_rate){
                // Mutate the gene
                new_population[x][y] = generate_random(Lbound[x], Ubound[y]);
            }
            else{
                // Keep the gene unchanged
                new_population[x][y] = population[x][y];
            }
        }
    }
}