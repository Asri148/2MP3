/*
2MP3 QUIZ-6 : THE FINAL ROUND

- You are provided a list of car names, a list of max speeds (in mph) and a list of prices (in $).
- The first line of the input_names_1.txt file contains the number of cars.
- You are also provided a 'car' structure, which has the following members:

struct car {
   char name[20];
   int max_speed;
   int price;
};

- You have to read the data from the files and store them in the structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
   char name[20];
   int max_speed;
   int price;
};

/*
PART-A : (5 marks)
- You have to sort the cars in the following order:
   - First sort by price (ascending)
   - Then sort by max_speed (descending) ONLY IF the prices are equal.

-  code to print the sorted list of cars in the following format has been provided to you:
      <name> <max_speed> <price>
- You also have to output the sorted list of cars in a file named 'output_a.txt' INSIDE THE MAIN function.

*/

// function which sorts the cars and returns a list of sorted cars:
struct car* sort_cars(struct car* cars, int n)
{
   struct car temp;
   for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (cars[j].price > cars[j + 1].price) {
            temp = cars[j];
            cars[j] = cars[j + 1];
            cars[j + 1] = temp;
         } else if (cars[j].price == cars[j + 1].price && cars[j].max_speed < cars[j + 1].max_speed) {
            temp = cars[j];
            cars[j] = cars[j + 1];
            cars[j + 1] = temp;
         }
      }
   }
   return cars;
}

/*
PART-B
- Find the average max speed and average price of the cars.
- Ouput the results in a txt file named 'output_b_i.txt' in the following format within the same function:
      Average max speed: <average_max_speed>
      Average price: <average_price>
*/

// function which finds the average max speed and average price of the cars in INTEGER format:
void find_average(struct car* cars, int n, int index)
{
   // default values:
   int total_max_speed = 0;
   int total_price = 0;


   for (int i = 0; i < n; i++) {
      total_max_speed += cars[i].max_speed;
      total_price += cars[i].price;
   }

   int average_max_speed = total_max_speed / n;
   int average_price = total_price / n;

   // print the results to the console:
   printf("\nResults:\n");
   printf("Average max speed: %d mph\n", average_max_speed);
   printf("Average price: $%d\n", average_price);

   // write the results to the output file:
   FILE *fp;
   char output_b_1[100];
   sprintf(output_b_1, "output_b_%d.txt", index);
   fp = fopen(output_b_1, "w");

   fprintf(fp, "Average max speed: %d mph\n", average_max_speed);
   fprintf(fp, "Average price: $%d\n", average_price);

   fclose(fp);
}

// main function:
int main(int argc, char const *argv[]) {
   // check if the user provided the correct number of command-line arguments
   if (argc != 5) {
      printf("Usage: ./program_name index names_file max_speeds_file prices_file\n");
      return 1;
   }

   // used for testing, use 1 for testing your code with the sample input files:
   int index = atoi(argv[1]);

   // read input data from the text files:
   FILE *fp1, *fp2, *fp3;
   fp1 = fopen(argv[2], "r");
   fp2 = fopen(argv[3], "r");
   fp3 = fopen(argv[4], "r");

   if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
      printf("Error in opening the files!\n");
      exit(1);
   }

   int n = 7; // default value for number of cars

   //(write your code here for) reading the number of cars ie. first line of the input_names_1.txt file:
   fscanf(fp1, "%d", &n);

   struct car* cars = (struct car*)malloc(n * sizeof(struct car));
   cars[0].name[0] = '\0'; // default value for name
   cars[0].max_speed = 0; // default value for max_speed
   cars[0].price = 0; // default value for price

   
   for (int i = 0; i < n; i++) {
      fscanf(fp1, "%s", cars[i].name);
      fscanf(fp2, "%d", &cars[i].max_speed);
      fscanf(fp3, "%d", &cars[i].price);
   }


   // close the files:
   fclose(fp1), fclose(fp2), fclose(fp3);

   // print the list of cars:
   printf("\nList of cars:\n");
   for (int i = 0; i < n; i++) {
      printf("< Build: %s, Top Speed: %d mph, Price: $%d >\n", cars[i].name, cars[i].max_speed, cars[i].price);
   }

   // sort the cars uisng the function you wrote:
   struct car* sorted_cars = sort_cars(cars, n);

   // print the sorted list of cars:
   printf("\nSorted list of cars:\n");
   for (int i = 0; i < n; i++) {
      printf("< Build: %s, Top Speed: %d mph, Price: $%d >\n", sorted_cars[i].name, sorted_cars[i].max_speed, sorted_cars[i].price);
   }

   // write the sorted list of cars to the output file:
   FILE *fp4;
   char output_a_1[100];
   sprintf(output_a_1, "output_a_%d.txt", index);
   fp4 = fopen(output_a_1, "w");

   for (int i = 0; i < n; i++) {
      fprintf(fp4, "< Build: %s, Top Speed: %d mph, Price: $%d >\n", sorted_cars[i].name, sorted_cars[i].max_speed, sorted_cars[i].price);
   }

   fclose(fp4);

   // find the average max speed and average price of the cars:
   find_average(cars, n, index);

   free(cars);
   free(sorted_cars);
   return 0;
}