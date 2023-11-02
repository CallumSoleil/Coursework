 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() {

    int lineCount = 0;

    char dataFile1 [] = "FitnessData_2023.csv";
    FILE *file1 = fopen(dataFile1, "r");
    int arrSize = 0;
    int buffer_size1 = 100;
    char line_buffer1[buffer_size1];

    while (fgets(line_buffer1, buffer_size1, file1) != NULL) {
        arrSize ++;
    }
    fclose(file1);
    FITNESS_DATA array[arrSize];


    int buffer_size2 = 100;
    char line_buffer2[buffer_size2];
    char outDate[11];
    char outTime[6];
    char outSteps[6];

    char dataFile2 [] = "FitnessData_2023.csv";
    FILE *file2 = fopen(dataFile2, "r");

    while (fgets(line_buffer2, buffer_size2, file2) != NULL) {

        tokeniseRecord(line_buffer2, ",", outDate, outTime, outSteps);

        strcpy(array[lineCount].date, outDate);
        strcpy(array[lineCount].time, outTime);
        array[lineCount].steps = atoi(outSteps);
        
        lineCount ++;
    }
    printf("Number of records in file: %d\n", lineCount);
    for(int i = 0; i<3; i++){
        printf("%s/%s/%d\n",array[i].date, array[i].time, array[i].steps);
    }
    fclose(file2);
}