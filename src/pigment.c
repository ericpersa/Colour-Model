#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"pigment.h"

int printPigment(pigment_t* pp, int i, int n) {
    // question 1 milestone 2
    /*
    purpose: 
        prints pigments within an array in a formatted way
    input:
    pp
        pointer pointing to an array of pigment structures
    n:
        the size of pp
    i
        index of the array to print. -1 means print whole array.
    */

    // error check for out of bounds index.
    if ((i < -1) || (i > n-1)) {
        return 1;
    }

    // we have a correct range, now we can check if we have -1 or an index.
    if (i == -1) {
        // i = -1, print whole array
        for (int i = 0; i <= n-1; i++) {
            // first paint struct is *(pp + 0)
            printf("--------------");
            printf("ciName        : %s", pp[i].ciName);
            printf("pigmentName   : %s", pp[i].pigmentName);
            printf("value         : %s", pp[i].value);
            printf("chroma        : %s", pp[i].chroma);
            printf("(a,b)         : (%s)", pp[i].abValue);
            printf("hue [degrees] : %s", pp[i].hueAngle);
            printf("huePurity     : %s", pp[i].huePurity);
            printf("(ahp,ahp)     : %s", pp[i].abHp);
        }
        return 0;
    }
    // print with index i
    printf("--------------");
    printf("ciName        : %s", pp[i].ciName);
    printf("pigmentName   : %s", pp[i].pigmentName);
    printf("value         : %s", pp[i].value);
    printf("chroma        : %s", pp[i].chroma);
    printf("(a,b)         : (%s)", pp[i].abValue);
    printf("hue [degrees] : %s", pp[i].hueAngle);
    printf("huePurity     : %s", pp[i].huePurity);
    printf("(ahp,ahp)     : %s", pp[i].abHp);
    return 0;
}

paint_t* getPaintRange(paint_t* pp, int npp, float rmin, float rmax, gRange_t getType, int* nspp ) {
    char identifier[20];
    int actmin;
    int actmax;
    // switch case statement to get the property we are looking for
    switch(getType) {
        case 0:
            actmin = 0;
            actmax = 359 * rmax;
            break;
        case 1:
            actmin = 35 * rmin;
            actmax = 68 * rmax;
            break;
        case 2:
            actmin = 0 * rmin;
            actmax = 2 * rmax;
            break;
        case 3:
            actmin = 0 * rmin;
            actmax = 4 * rmax;
            break;
        case 4:
            actmin = 0 * rmin;
            actmax = 4 * rmax;
            break;
        case 5:
            actmin = 0 * rmin;
            actmax = 4 * rmax;
            break;
        case 6:
            actmin = 1 * rmin;
            actmax = 8 * rmax;
            break;
    }

    //dynamically allocate paint array of structures
    int capacity = 10;
    paint_t* paint_arr = malloc(capacity*sizeof(paint_t));
    if(paint_arr == NULL){
        return(NULL);
    }

    for (int i = 0; i < npp;  i++) {
        // check if range of values falls into normalized range
        int value = 0;
        switch (getType) {
            case 0:
                value = pp[i].hueAngle;
                break;
            case 1:
                value = pp[i].valueRange;
                break;
            case 2:
                value = pp[i].granulating;
                break;
            case 3:
                value = pp[i].transparency;
                break;
            case 4:
                value = pp[i].staining;
                break;
            case 5:
                value = pp[i].blossom;
                break;
            case 6:
                value = pp[i].lightfast;
                break;

            if ((value >= actmin) && (value <= actmax)) {
                // the property we are checking falls within the specified range, append to dynamic list
                *nspp += 1;
                if ((*nspp) > capacity) {
                    capacity += 5;
                    // reallocate as our array is full
                    paint_arr = realloc(paint_arr, (sizeof(paint_t) * capacity));
                }
                // add to memory at [nspp - 1]
                paint_arr[*nspp-1] = pp[i]; 
            }
        return paint_arr;
    }

            
    }
    return pp;
}

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
        count_skip += 1;
        if (count_skip > 9) {
            *n += 1;
            // check if array is full, allocate 10 extra spots if it is.
            if (count_line >= capacity) {
                capacity += 10;
                pArray = realloc(pArray, sizeof(pigment_t) * capacity);
                if (pArray == NULL) {
                    printf("Failed to allocate memory");
                    return NULL;
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
            pArray[count_line].huePurity = atof(token);

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

paint_t* loadPaintData( char* filename, paint_t* pArray, int* n){
    /***
    purpose:
        read in data line by line from file of paints, taking each specified value and putting it 
        into array of paint_t structs.
    input:
        filename: 
            pointer to where the file containing paint values is stored
        pArray:
            Array containing paint_t structs for each paint from file
        n:
            number of paints that have been input into pArray
    ***/

    char line[300];
    char *token;
    int i =0;
    int count=1;

    //open file and check if valid
    FILE* fd = fopen(filename, "r");
    if(fd == NULL){
        printf("Invalid File\n");
        //close file and return failure
        fclose(fd);
        return NULL;
    }

    //skip the first 12 lines as they are comments
    for(int i=0; i<12; i++){
        fgets(line, 300, fd);
    }

    //traverse through lines until reaching the end of file
    while(fgets(line, 300, fd) != NULL){
        (*n)++;
        if( i == count){
            count = count*2;
            pArray = realloc(pArray, count * sizeof(paint_t));
        }

        //token through line to collect each data point of struct
        token = strtok(line, ",");
        strcpy(pArray[i].ciName, token);

        token = strtok(NULL, ",");
        strcpy(pArray[i].marketingName, token);

        token = strtok(NULL, ",");
        strcpy(pArray[i].manufacturer, token);

        token = strtok(NULL, ",");
        strcpy(pArray[i].code, token);

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
    //close file and return success
    fclose(fd);
    return pArray;
}
