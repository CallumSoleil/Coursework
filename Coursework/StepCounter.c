#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
int lineCount = 0;
int arrSize = 0;
int buffer_size = 100;
char outDate[11];
char outTime[6];
char outSteps[6];
int lowestStepsIndex = 0;
int highestStepsIndex = 0;
int conti500 = 0;
float total = 0;
char inLoop = 'F';
int tempConti = 0;
int contiEnd = 0;

FITNESS_DATA array[1000];
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
    
    char menu;
    char filename[100];
    while (1==1){
        printf("\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the data and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Exit \n");
        scanf(" %c", &menu);

        switch (menu){
            case 'A':
            printf("Input file name: ");
            scanf("%s", filename);

            FILE *file1 = fopen(filename, "r");

            if (!file1){
               printf("Error: could not open file\n");
            }
            else{
                arrSize = 0;
                char line_buffer1[buffer_size];
                while (fgets(line_buffer1, buffer_size, file1) != NULL) {
                    arrSize ++;
                }
                fclose(file1);
                
                FILE *file2 = fopen(filename, "r");
                char line_buffer2[buffer_size];

                lineCount = 0;
                while (fgets(line_buffer2, buffer_size, file2) != NULL) {
                    tokeniseRecord(line_buffer2, ",", outDate, outTime, outSteps);
                    strcpy(array[lineCount].date, outDate);
                    strcpy(array[lineCount].time, outTime);
                    array[lineCount].steps = atoi(outSteps);
                    lineCount ++;
                }
            }
            break;

            case 'B':
                printf("Total records: %d\n", arrSize);
            break;

            case 'C':
                
                for(int i = 1; i<arrSize; i++){
                    if (array[i].steps < array[lowestStepsIndex].steps){
                        lowestStepsIndex = i;
                    }
                }
                printf("Fewest steps: %s %s\n", array[lowestStepsIndex].date, array[lowestStepsIndex].time);

            break;

            case 'D':
            for(int i = 1; i<arrSize; i++){
                    if (array[i].steps > array[highestStepsIndex].steps){
                        highestStepsIndex = i;
                    }
                }
                printf("Largest steps: %s %s\n", array[lowestStepsIndex].date, array[lowestStepsIndex].time);
            break;

            case 'E':
            for(int i = 0; i<arrSize; i++){
                total = total + array[i].steps;
            }
            printf("Mean step count: %d\n", (int)((total/arrSize)+ 0.5));
            break;

            case 'F':
        
            for(int i = 0; i<arrSize; i++){
                if (array[i].steps >= 500){
                    if(inLoop == 'T'){
                        tempConti += 1;
                    }
                    else{
                        tempConti = 1;
                        inLoop = 'T';
                    }
                }
                else{
                    inLoop = 'F';
                    if (tempConti > conti500){
                        conti500 = tempConti;
                        contiEnd = i-1;
                    }
                }

                }
                if (tempConti > conti500){
                        conti500 = tempConti;
                        contiEnd = arrSize-2;
                }
                printf("Longest period start: %s %s\n", array[contiEnd+1-conti500].date, array[contiEnd+1-conti500].time);
                printf("Longest period end: %s %s\n", array[contiEnd].date, array[contiEnd].time);
            
            break;

            case 'Q':
            return 0;
        
            default:
            printf("Invalid choice\n");
        }
    }
}