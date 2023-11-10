// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

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
    // Calculate total fitness of the population
    double total_fitness = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        total_fitness += fitness[i];
    }

    // Calculate probabilities for selection based on fitness
    double fitness_probs[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness_probs[i] = fitness[i] / total_fitness;
    }

    for (int i = 0; i < POPULATION_SIZE; i += 2)
    {
        if (generate_random(0, 1) < crossover_rate)
        {
            // Perform roulette wheel selection based on fitness probabilities
            double rand_num1 = generate_random(0, 1);
            double rand_num2 = generate_random(0, 1);
            int parent1 = 0, parent2 = 0;
            double cumulative_prob = fitness_probs[0];

            while (cumulative_prob < rand_num1)
            {
                parent1++;
                cumulative_prob += fitness_probs[parent1];
            }

            cumulative_prob = fitness_probs[0];
            while (cumulative_prob < rand_num2)
            {
                parent2++;
                cumulative_prob += fitness_probs[parent2];
            }

            // Perform crossover for individuals with indices parent1 and parent2
            int crossover_point = generate_int() % NUM_VARIABLES;
            for (int j = 0; j < crossover_point; j++)
            {
                new_population[i][j] = population[parent1][j];
                new_population[i + 1][j] = population[parent2][j];
            }
            for (int j = crossover_point; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = population[parent2][j];
                new_population[i + 1][j] = population[parent1][j];
            }
        }
        else
        {
            // If no crossover, copy parents to the new population
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = population[i][j];
                new_population[i + 1][j] = population[i + 1][j];
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