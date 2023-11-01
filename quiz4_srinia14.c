#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// random function prototypes
void setRandomSeed(int seedValue);
int* generateRandomIntArray(int size);
char* getRandomMessage();
char* getRandomWord();
float* generateGrades(int size);
char getRandomOperator();
char* encryptMessage(char* message);

// challenge 1
// return the sum of non-negative elements of the input array which are also multiples of 2

int sumNonNegative(int* arr, int size) {
   /* ENTER YOUR CODE HERE*/
   int sum = 0;
   for (int x = 0; x < size; x++) {
        if (arr[x] >= 0 && arr[x] % 2 == 0) {
            sum += arr[x];
        }
    }
    return sum;
   /* STOP WRITING YOUR CODE HERE*/
}

// challenge 2
// return the count of the number of vowels in the input string.

int vc_count(char *str)
{
   /* ENTER YOUR CODE HERE */
   int counter = 0;
    while (*str) {
        if (*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' || *str == 'u' ||
            *str == 'A' || *str == 'E' || *str == 'I' || *str == 'O' || *str == 'U') {
            counter++;
        }
        str++;
    }
    return counter;
   /* STOP WRITING YOUR CODE HERE */
}

// challenge 3
// Implement a basic calculator that performs addition, subtraction and multiplication
// `op` ie. operator will be input, eg : '+'
// return the result of the calculation

float calc(float a, float b, char op)
{
   /* ENTER YOUR CODE HERE */
   float result;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        default:
            result = -1.0; // Invalid operator
    }
    return result;
   /* STOP WRITING YOUR CODE HERE */
}

// challenge 4
// given an encrypted message string as input, return the decrypted message string
// key : subtract 10 from the ascii value of each character of the string

/*
- Output the decrypted message in `decryptedMessage`
- There is no return; this is a void function.
*/

void decryptMessage(char* message, char* decryptedMessage) {   
   /* ENTER YOUR CODE HERE */
   int m = 0;
    while (message[m] != '\0') {
        decryptedMessage[m] = message[m] - 10;
        m++;
    }
    decryptedMessage[m] = '\0';
   /* STOP WRITING YOUR CODE HERE */
}

/* ************ MAIN FUNCTION *********************** */

int main(int argc, char *argv[]) {

   // DON'T PASS ANY ARGUMENTS TO THIS PROGRAM WHEN TESTING YOUR CODE
   if (argc < 2){
      setRandomSeed(0);

      // USE THIS TO TEST YOUR CODE
      
      // challenge 1 :
      int size = 10;
      int* arr = generateRandomIntArray(10); 

      printf("C1 : \nRandom Array: [");
      for (int i = 0; i < size; i++) {
         printf("%d ", arr[i]);
      }
      printf("]");

      int result = sumNonNegative(arr, size);
      printf("\nSum = %d\n", result); // check

      // challenge 2 :
      char* randomMessage = getRandomMessage();
      printf("\nC2 : \nMessage: %s", randomMessage);
      printf("\nvowel count = %d", vc_count(randomMessage)); // check

      // challenge 3 :
      int size2 = 5;
      float* rand_arr = generateGrades(size2);
      char randomOperator = getRandomOperator();

      // check
      printf("\n\nC3 : \nrandom calculation = %.2f %c %.2f = %.2f", rand_arr[0], randomOperator, rand_arr[1], calc(rand_arr[0], rand_arr[1], randomOperator));

      // challenge 4 :
      printf("\n\nC4 : \nMessage: %s", randomMessage);
      char* encryptedMessage = encryptMessage(randomMessage);
      printf("\nencrypted message : %s", encryptedMessage);

      char* decryptedMessage = (char*)malloc(strlen(encryptedMessage) + 1); // +1 for the null-terminator
      decryptMessage(encryptedMessage, decryptedMessage);
      printf("\ndecrypted message : %s", decryptedMessage); // check

      // free the memory
      free(arr);
      free(rand_arr);
      free(encryptedMessage);
      free(decryptedMessage);
   } 

   /* -------- INGORE FROM HERE ------------- */ 
   else if (argc == 2) {
      int seedValue = atoi(argv[1]);
      setRandomSeed(seedValue);

      // randomly generated values for functions
      int size = 10;
      int* arr = generateRandomIntArray(10);   

      char* randomMessage = getRandomMessage();

      int size2 = 5;
      float* rand_arr = generateGrades(size2);
      
      char randomOperator = getRandomOperator();
      char* encryptedMessage = encryptMessage(randomMessage);
      char* decryptedMessage = (char*)malloc(strlen(encryptedMessage) + 1); // +1 for the null-terminator

      // call the functions
      int test1 = sumNonNegative(arr, size);
      int test2 = vc_count(randomMessage);
      float test3 = calc(rand_arr[0], rand_arr[1], randomOperator);
      
      decryptMessage(encryptedMessage, decryptedMessage);
      char* test4 = decryptedMessage;

      char file1_name[256], file2_name[256], file3_name[256], file4_name[256];

      // name the files
      snprintf(file1_name, sizeof(file1_name), "test1_%i.txt", seedValue);
      snprintf(file2_name, sizeof(file2_name), "test2_%i.txt", seedValue);
      snprintf(file3_name, sizeof(file3_name), "test3_%i.txt", seedValue);
      snprintf(file4_name, sizeof(file4_name), "test4_%i.txt", seedValue);

      // open files in write mode (existing files will be overwritten)
      FILE *file1 = fopen(file1_name, "w");
      FILE *file2 = fopen(file2_name, "w");
      FILE *file3 = fopen(file3_name, "w");
      FILE *file4 = fopen(file4_name, "w");

      // Check if file openings were successful
      if (file1 == NULL || file2 == NULL || file3 == NULL || file4 == NULL) {
         printf("Error opening files!\n");
         exit(1);
      }

      // Write test results to their respective files
      fprintf(file1, "%d", test1);
      fprintf(file2, "%d", test2);
      fprintf(file3, "%.2f", test3);
      fprintf(file4, "%s", test4);

      // close the files
      fclose(file1), fclose(file2), fclose(file3), fclose(file4);
   
      free(arr);
      free(rand_arr);
      free(encryptedMessage);
      free(test4);
   }

   // cmd-line passed test cases
   else if (argc == 3) {

      // Open the input file
      char* filename = argv[2];

      FILE* file = fopen(filename, "r");
      if (file == NULL) {
         perror("Error opening file");
         return 2;
      }

      char* substring;

      // Find the position of the last period ('.') character
      // strrchr() returns a pointer to the last occurrence of the character
      char* lastPeriod = strrchr(filename, '.');

      if (lastPeriod != NULL) {
         // Allocate memory for the substring
         substring = (char*)malloc((lastPeriod - filename + 1) * sizeof(char));

         // Copy the substring
         strncpy(substring, filename, lastPeriod - filename);
         substring[lastPeriod - filename] = '\0'; // Null-terminate the string

         printf("Extracted substring: %s\n", substring);

      } else {
         printf("No period found in the filename.\n");
         return 3;
      }

      int N1, N2, N3, N4;
      int i;
      char* string_N2 = NULL;
      char* string_N4 = NULL;

      // Read N1
      fscanf(file, "%d", &N1);

      // Read the array of N1 integers
      int* arr = (int*)malloc(N1 * sizeof(int));
      for (i = 0; i < N1; i++) {
         fscanf(file, "%d", &arr[i]);
      }

      // Read N2
      fscanf(file, "%d", &N2);

      // Allocate memory for the string of N2 characters
      string_N2 = (char*)malloc((N2 + 1) * sizeof(char));

      // Read the string of N2 characters
      fscanf(file, "%s", string_N2);

      // Read N3
      fscanf(file, "%d", &N3);

      // Read the array of N3 floats
      float* grades = (float*)malloc(N3 * sizeof(float));
      for (i = 0; i < N3; i++) {
         fscanf(file, "%f", &grades[i]);
      }

      // Read N4
      fscanf(file, "%d", &N4);

      // Allocate memory for the string of N4 characters
      string_N4 = (char*)malloc((N4 + 1) * sizeof(char));

      // Read the string of N4 characters
      fscanf(file, "%s", string_N4);

      // Close the file
      fclose(file);

      // call functions
      int test1 = sumNonNegative(arr, N1);
      int test2 = vc_count(string_N2);

      // using 1st and 2nd ele of grades array as operands and testing all operations :
      float test3_1 = calc(grades[0], grades[1], '+');
      float test3_2 = calc(grades[0], grades[1], '-');
      float test3_3 = calc(grades[0], grades[1], '*');

      // sum the results of all operations
      float test3 = test3_1 + test3_2 + test3_3;

      char* decryptedMessage = (char*)malloc(N4 + 1); // +1 for the null-terminator
      decryptMessage(string_N4, decryptedMessage);
      char* test4 = decryptedMessage;

      char file1_name[256], file2_name[256], file3_name[256], file4_name[256];

      // name the files
      snprintf(file1_name, sizeof(file1_name), "test1_%s.txt", substring);
      snprintf(file2_name, sizeof(file2_name), "test2_%s.txt", substring);
      snprintf(file3_name, sizeof(file3_name), "test3_%s.txt", substring);
      snprintf(file4_name, sizeof(file4_name), "test4_%s.txt", substring);

      // open files in write mode (existing files will be overwritten)
      FILE* file1 = fopen(file1_name, "w");
      FILE* file2 = fopen(file2_name, "w");
      FILE* file3 = fopen(file3_name, "w");
      FILE* file4 = fopen(file4_name, "w");

      // Check if file openings were successful
      if (file1 == NULL || file2 == NULL || file3 == NULL || file4 == NULL) {
         printf("Error opening files!\n");
         exit(1);
      }

      // Write test results to their respective files
      fprintf(file1, "%d", test1);
      fprintf(file2, "%d", test2);
      fprintf(file3, "%.2f", test3);
      fprintf(file4, "%s", test4);

      // close the files
      fclose(file1), fclose(file2), fclose(file3), fclose(file4);

      printf("C1 : \nArray: [ ");
      for (int i = 0; i < N1; i++) {
         printf("%d ", arr[i]);
      }
      printf("]");

      printf("\nSum = %d\n\nC2 :", test1); // check

      printf("\nWord = %s", string_N2);
      printf("\vowel count = %d", test2); // check

      // check
      // using 1st and 2nd ele of grades array
      printf("\n\nC3 : \nrandom calculation = %.2f %c %.2f = %.2f", grades[0], '+', grades[1], calc(grades[0], grades[1], '+'));
      printf("\ncalculation (test3_1) = %.2f %c %.2f = %.2f", grades[0], '+', grades[1], calc(grades[0], grades[1], '+'));
      printf("\ncalculation (test3_2) = %.2f %c %.2f = %.2f", grades[0], '+', grades[1], calc(grades[0], grades[1], '-'));
      printf("\ncalculation (test3_3) = %.2f %c %.2f = %.2f", grades[0], '+', grades[1], calc(grades[0], grades[1], '*'));
      printf("\nsum of all operations (test3) = %.2f",test3);

      printf("]\n\nC4 : \nEncrypted Message: %s", string_N4);
      printf("\nDecrypted message : %s", decryptedMessage); // check

      free(arr);
      free(grades);
      free(test4);
      free(string_N2);
      free(string_N4);

   } else {
      printf("Too many command line arguments");
      return 1;
   }

   return 0;
}

/* -------------- RANDOM FUNCTIONS ----------- */

void setRandomSeed(int seed)
{
   if (seed == 0)
   {
      seed = (int)time(NULL);
   }
   srand(seed); // Set the seed
}

int* generateRandomIntArray(int size) {

   int* array = (int*)malloc(size * sizeof(int));

   if (array == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
   }

   for (int i = 0; i < size; i++) {
      array[i] = rand() % 201 - 100; // Generates random values between -100 and 100
   }

   return array;
}

float* generateGrades(int size) {
   float* array = (float*)malloc(size * sizeof(float));

   if (array == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      exit(1);
   }

   for (int i = 0; i < size; i++) {
      // Generate random values between 0 and 100
      float randomValue = ((float)rand() / RAND_MAX) * 100.0;
      array[i] = randomValue;
   }

   return array;
}

char* getRandomMessage() {

   static char* messages[] = {
      "Hello, World!",
      "This is a test case?",
      "2MP3 - Programming for Mechatronics!",
   };

   int numMessages = sizeof(messages) / sizeof(messages[0]);
   int randomIndex = rand() % numMessages;

   return messages[randomIndex];
}

char* getRandomWord() {
   static char* words[] = {
      "racecar", "programming", "level", "civic", "code",
      "deified", "software", "rotor", "algorithm", "madam"
   };

   int numWords = sizeof(words) / sizeof(words[0]);
   int randomIndex = rand() % numWords;

   return words[randomIndex];
}

char getRandomOperator() {
   char operators[] = {'+', '-', '*'};
   int numOperators = sizeof(operators) / sizeof(operators[0]);
   int randomIndex = rand() % numOperators;
   return operators[randomIndex];
}

// string encryption
char* encryptMessage(char* message)
{
   int length = strlen(message);
   char* encryptedMessage = (char*)malloc(length + 1);  // +1 for the null-terminator

   for (int i = 0; i < length; i++) {
      encryptedMessage[i] = message[i] + 10;
   }
   encryptedMessage[length] = '\0';  // Null-terminate the encrypted message

   return encryptedMessage;
}