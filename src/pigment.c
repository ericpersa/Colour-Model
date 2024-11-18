#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"pigment.h"

// int main(void) {
//     // lets just try to parse through the lines in data/data.dat
//     FILE* fp = fopen("../data/data.tar", "r");

//     if (fp == NULL) {
//         printf("Error opening file");
//         return 1;
//     } 
//     char line[256]; // buffer for each line
//     while (fgets(line, sizeof(line), fp)) {
//         // Each line is now stored in 'line' as a string, up to 255 characters
//         printf("%s", line);  // Print or process the line as needed
//     }

//     fclose(fp);  // Close the file when done
//     return 0;
// }


// int loadPigmentData(char* filename, pigment_t* pArray, int* n) {
//     //purpose: 
//     //  loadPigmentData will read data line by line from the filename data location into a pigment_t  
//     //  structure
//     //input:
//     //  filename:
//     //      a pointer to the file where the data is stored
//     //  pArray:
//     //      an array of pigment structures where the data is stored
//     //  n:
//     //      a pointer to the number of entries found.
// }

int loadPaintData( char* filename, paint_t* pArray, int* n){
    /***
    purpose:

    //input:

    output:
    ***/

    char line[300];
    char *token;
    int i =0;

    //open file and check if valid
    FILE* fd = fopen(filename, "r");
    if(fd == NULL){
        printf("Invalid File\n");
        return 1;
    }

    //skip the first 12 lines as they are comments
    for(int i=0; i<12; i++){
        fgets(line, 300, fd);
    }

    //traverse through lines until reaching the end of file
    while(fgets(line, 300, fd) != NULL){
        if( i == *n){
            *n = *n *2;
            pArray = realloc(pArray, *n*sizeof(paint_t));
        }

        //token through line to collect each data point of struct
        token = strtok(line, ",");
        strcpy(pArray[i].ciName, token);
        token = strtok(NULL, ",");
        strcpy(pArray[i].marketingName, token);
        token = strtok(NULL, ",");
        strcpy(pArray[i].manufacturer, token);
        token = strtok(NULL, ",");
        pArray[i].code = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].transparency = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].staining = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].valueRange = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].granulating = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].blossom = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].diffusion = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].hueAngle = atoi(token);
        token = strtok(NULL, ",");
        pArray[i].hueShift = atoi(token);
        //last input has 2 values, last value after '/' is desired value for lightfast
        token = strtok(NULL, "/");
        token = strtok(NULL, "\n");
        pArray[i].lightfast = atoi(token);
        i++;
    }
    return 0;
}
