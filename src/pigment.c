#include<stdio.h>
#include"pigment.h"

int main(void) {
    // lets just try to parse through the lines in data/data.dat
    FILE* fp = fopen("../data/data.tar", "r");

    if (fp == NULL) {
        printf("Error opening file");
        return 1;
    } 
    char line[256]; // buffer for each line
    while (fgets(line, sizeof(line), fp)) {
        // Each line is now stored in 'line' as a string, up to 255 characters
        printf("%s", line);  // Print or process the line as needed
    }

    fclose(fp);  // Close the file when done
    return 0;
}


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