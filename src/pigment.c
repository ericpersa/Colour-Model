#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"pigment.h"

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n) {
    /*
    purpose: 
     loadPigmentData will read data line by line from the filename data location into a pigment_t  
     structure
    input:
     filename:
         a pointer to the file where the data is stored
     pArray:
         an array of pigment structures where the data is stored
     n:
         a pointer to the number of entries found.
    */
   char *token;
   FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file");
        return NULL;
    } 
    char line[256]; // buffer for each line
    int count_skip = 0;
    int count_line = 0;
    int capacity = 10;

    pArray = malloc(sizeof(pigment_t) * capacity);

    if (pArray == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp)) {
        *n += 1;
        count_skip += 1;
        if (count_skip > 9) {
            
            // check if array is full, allocate 10 extra spots if it is.
            if (count_line >= capacity) {
                capacity += 10;
                pArray = realloc(pArray, sizeof(pigment_t) * capacity);
                if (pArray == NULL) {
                    printf("Failed to allocate memory");
                    exit(EXIT_FAILURE);
                }
            }
            // # pigments.dat: COLOR INDEX, PIGMENT NAME, J, C,aC,bC,HueAngle,Hue Purity,aHP,bHP
            token = strtok(line, ",");
            printf("color index: %s\n", token);
            strcpy(pArray[count_line].ciName, token); 

            token = strtok(NULL, ",");
            printf("pigment name: %s\n", token);
            strcpy(pArray[count_line].pigmentName, token); 

            token = strtok(NULL, ",");
            printf("J: %s\n", token);
            pArray[count_line].value = atoi(token); 

            token = strtok(NULL, ",");
            printf("C: %s\n", token);
            pArray[count_line].chroma = atoi(token);

            token = strtok(NULL, ",");
            printf("aC: %s\n", token);
            pArray[count_line].abValue[0] = atoi(token);

            token = strtok(NULL, ",");
            printf("bC: %s\n", token);
            pArray[count_line].abValue[1] = atoi(token);

            token = strtok(NULL, ",");
            printf("hueAngle: %s\n", token);
            pArray[count_line].hueAngle = atoi(token);

            token = strtok(NULL, ",");
            printf("huePurity: %s\n", token);
            pArray[count_line].huePurity = atoi(token);

            token = strtok(NULL, ",");
            printf("aHp: %s\n", token);
            pArray[count_line].abHp[0] = atof(token);

            token = strtok(NULL, ",");
            printf("bHp: %s\n", token);
            pArray[count_line].abHp[1] = atof(token);

            printf("\n");
            count_line += 1;
        }
    }

    fclose(fp);  // close the file when done
    return pArray;

}

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
