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

    FITNESS_DATA array[60];
    unsigned lineCount;

    char dataFile [] = "FitnessData_2023.csv";
    FILE *file = fopen(dataFile, "r");

    int buffer_size = 100;
    char line_buffer[buffer_size];
    char outDate[30];
    char outTime[6];
    char outSteps[6];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        tokeniseRecord(line_buffer, ",", outDate, outTime, outSteps);
        strcpy(array[lineCount].date, outDate);
        strcpy(array[lineCount].time, outTime);
        array[lineCount].steps = atoi(outSteps);
        //printf("%s\n", outTime);
        //printf("%s/%s/%s\n", array[lineCount].date, array[lineCount].time, array[lineCount].steps );
        lineCount ++;
}
printf("Number of records in file: %d\n", lineCount);
for(int i = 0; i<3; i++){
    printf("%s/%s/%d\n",array[i].date, array[i].time, array[i].steps);
}
fclose(file);
}
