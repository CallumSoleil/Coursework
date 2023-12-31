#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"
#include <ctype.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

int lineCount = 0;
int arrSize = 0;
int buffer_size = 100;
char outDate[11];
char outTime[6];
char outSteps[6];
char filename[100];
char accept = 'T';
FITNESS_DATA array[1000];

// Function to tokenize a record
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

int main() {

    printf("Input file name: ");
    scanf("%s", filename);

    FILE *file1 = fopen(filename, "r");

    if (!file1){
        printf("Error: invalid file\n");
        return 1;
    }
    /*else if (INVALID DATA IN FILE){
        printf("Error: invalid file\n");
        return 1;
    }*/
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
        char stepTemp[100];

        for(; lineCount < arrSize; lineCount ++){
        //while (fgets(line_buffer2, buffer_size, file2) != NULL) {
            fgets(line_buffer2, buffer_size, file2);
            tokeniseRecord(line_buffer2, ",", outDate, outTime, outSteps);
            strcpy(array[lineCount].date, outDate);
            strcpy(array[lineCount].time, outTime);
            strcpy(stepTemp, outSteps);

            char stepExist = 'F';
            size_t length = strlen(stepTemp);
            
            if(lineCount == arrSize -1){
                for (size_t i = 0; i < length; i++) {
                stepExist ='T';
                if (isdigit(stepTemp[i]) == 0){
                    
                    accept = 'F';
                }
            }
            }


            for (size_t i = 0; i < length-2; i++) {
                stepExist ='T';
                if (isdigit(stepTemp[i]) == 0){
                    
                    accept = 'F';
                }
            }
            
            if(stepExist == 'F'){
                accept = 'F';
            }
            

            array[lineCount].steps = atoi(outSteps);
             if((strchr(array[lineCount].date, '-') == NULL) || (strchr(array[lineCount].time, ':') == NULL) || accept == 'F'){
                printf("Error: invalid file\n");
                return 1;
             }
        }


        FITNESS_DATA temp;
        for(int i = 0; i < arrSize; i++){
            for(int j = 0; j < arrSize-i-1 ; ++j){
                if(array[j].steps < array[j+1].steps){
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
        printf("%s\n", strcat(filename,".tsv"));
        for(int i=0;i<arrSize;i++)
        printf(" %s\t%s\t%d\n",array[i].date, array[i].time, array[i].steps);
        return 0;
    }
    
}
