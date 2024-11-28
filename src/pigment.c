// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leaw 3147578
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <strings.h>
#include"pigment.h"


int printPigment(pigment_t* pp, int i, int n) {
    // error check for out of bounds index.
    if ((i < -1) || (i > n-1)) {
        return 1;
    }

    // we have a correct range, now we can check if we have -1 or an index.
    if (i == -1) {
        // i = -1, print whole array
        for (int j = 0; j <= n-1; j++) {
            // first paint struct is *(pp + 0)
            int err = printPigmentHelper(pp, j);
            if (err == 1) {
                printf("printPigment: error printing with index -1");
            }
        }
        return 0;
    }
    // print with index i
    int err = printPigmentHelper(pp, i);
    if (err == 1) {
        printf("printPigment: error printing at given index");
    }
    return 0;
}

int printPaint(paint_t* pp, int i, int n) {
    // error check for out of bounds index.
    if ((i < -1) || (i > n-1)) {
        return 1;
    }

    // we have a correct range, now we can check if we have -1 or an index.
    if (i == -1) {
        // i = -1, print whole array
        for (int j = 0; j <= n-1; j++) {
            // first paint struct is *(pp + 0)
            int err = printPaintHelper(pp, j);
            if (err == 1) {
                printf("printPaint: error with index -1, printing paints");
            }
        }
        return 0;
    }
    // print with index i
    int err = printPaintHelper(pp, i);
    if (err == 1) {
        printf("printPaint: error with index -1, printing paints");
    }
    return 0;
}

paint_t* getPaintRange(paint_t* pp, int npp, float rmin, float rmax, gRange_t getType, int* nspp ) {
    // add purpose
    
    // error checking for rmin and max, must be between 0 and 1 inclusive
    if (((rmin < 0) || (rmin > 1)) || ((rmax > 1) || (rmax < 0)) || (rmin > rmax)) {
        return NULL;
    }
    
    *nspp = 0;
    float actmin = 0.0;
    float actmax = 0.0;

    // switch case helper
    int err = getPaintRangeHelper(getType, &actmin, &actmax, rmin, rmax);
    if (err != 0) {
        printf("Error with getPaintRangeHelper in getPaintRange function. exiting getPaintRange");
        return(NULL);
    }

    //dynamically allocate paint array of structures
    int capacity = 10;
    paint_t* paint_arr = malloc(capacity*sizeof(paint_t));
    if (paint_arr == NULL){
        return(NULL);
    }
    for (int i = 0; i < npp;  i++) {
        // check if range of values falls into normalized range
        int value = 0;
        err = getPaintRangeValueHelper (getType, pp, i, &value); 
        if (err != 0) {
            printf("Error with getPaintRangeValueHelper in getPaintRange function. exiting getPaintRange");
        return(NULL);
    }

        if ((value >= actmin) && (value <= actmax)) {
            // the property we are checking falls within the specified range, append to dynamic list
            *nspp += 1;
            if ((*nspp) > capacity) {
                capacity += 5;
                // reallocate as our array is full
                paint_arr = realloc(paint_arr, (sizeof(paint_t) * capacity));
                if (paint_arr == NULL) {
                    free(paint_arr);
                    return(NULL);
                }
            }   
            // add to memory at [nspp - 1]
            paint_arr[*nspp-1] = pp[i]; // -1 because we increment nspp for every iteration
        }      
    }
    return paint_arr;
}

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n) {
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

paint_t* getPaintValue(paint_t* pp, int npp, char* name, gValue_t getType, int* nspp){

    //create new array of structures for structs with proper prerequisites
    paint_t* spa = malloc(sizeof(paint_t));
    if (spa == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int size = 1;

    //if getType is ciName (0 because of enum)
    if(getType == 0){
        //traverse through array of apaints to look for the same name in column getType
        for(int i =0; i<npp; i++){
            //make 


            // if the name is the same copy that structure into another array and increase number of nspp
            //use strcasecmp to compare and ignore case 
            if( strcasecmp(pp[i].ciName, name) ==0){
                if( *nspp == size){
                    size = size *2;
                    spa = realloc(spa, size*sizeof(paint_t));
                }
                int err = getPaintValueHelperCopy(spa, pp, nspp, i);
                if (err == 1) {
                    printf("Error with getPaintValueHelperCopy in getPaintValue. Returning with NULL");
                    return (NULL);
                }
                (*nspp)++;
            }
        }
    }
    //if getType is marketingName (1 because of enum)
    else if(getType == 1){
        for(int i =0; i<npp; i++){
            if( strcasecmp(pp[i].marketingName, name) ==0){
                if( *nspp == size){
                    size = size *2;
                    spa = realloc(spa, size*sizeof(paint_t));
                 }
                int err = getPaintValueHelperCopy(spa, pp, nspp, i);
                if (err == 1) {
                    printf("Error with getPaintValueHelperCopy in getPaintValue. Returning with NULL");
                    return (NULL);
                }
                (*nspp)++;
            }
        }
    }
    //if getType is manufacterer (2 because of enum)
    else if(getType == 2){
        for(int i =0; i<npp; i++){
            if( strcasecmp(pp[i].manufacturer, name) ==0){
                if( *nspp == size){
                    size = size *2;
                    spa = realloc(spa, size*sizeof(paint_t));
                 }
                 int err = getPaintValueHelperCopy(spa, pp, nspp, i);
                 if (err == 1) {
                    printf("Error with getPaintValueHelperCopy in getPaintValue. Returning with NULL");
                    return (NULL);
                 }
                 (*nspp)++;
            }
        }
    }
    else{
        //if the type is not input correctly return error
        return (NULL);
    }
    //return new sub array 
    return(spa);
}

paint_t* getPaintHue(paint_t* pp, int* n, colour_t colour) {
    // error check inputs
    if ((pp == NULL) || (n<0)) {
        return NULL;
    }

    // create malloced paint_t array
    int size = 2;
    paint_t* spa = malloc(size * sizeof(paint_t));
    if (spa == NULL) {
        printf("Failed to allocate memory");
        return(NULL);
    }


    int hue_range_low = 0;
    int hue_range_high = 0;
    // each colour we get from enum corresponds to a certain hue angle.
    int err = getPaintHueSwitchHelper(colour, &hue_range_low, &hue_range_high);
    if (err == 1) {
        printf("Error occured in with Switch Helper in getPaintHue. Returning with NULL");
        return(NULL);
    }

    int index = 0;
    // loop through pp
    for (int i = 0; i < n; i++) {
        if((index+1) == size){
            size = size *2;
            spa = realloc(spa, size*sizeof(paint_t));
        }

        if (colour == 1) {
            // RED_ORANGE is a weird case where it must be between 345 and 15 degrees
            if (((pp[i].hueAngle >= 0) && (pp[i].hueAngle <= 15)) || 
            ((pp[i].hueAngle >= 345) && (pp[i].hueAngle <= 359))) {
                // valid for red orange
                int err = getPaintValueHelperCopy(spa, pp, index, i);
                if (err == 1) {
                    printf("Error Copying values in getPaintHue. returning NULL");
                    return(NULL);
                }
                
            }
        }
        else if ((pp[i].hueAngle >= hue_range_low) && (pp[i].hueAngle <= hue_range_high)) {
            int err = getPaintValueHelperCopy(spa, pp, index, i);
            if (err == 1) {
                printf("Error Copying values in getPaintHue. returning NULL");
                return(NULL);
            }
        }
    }
}

int getPaintHueSwitchHelper(colour_t colour, int* hue_range_low, int* hue_range_high) {
    /*
    purpose: helper function for getPaintHue. takes an enumerated colour and modified hue_range low and high
    so that they have the range for where that colour is found
    input: colour, a enum type, and a pointer to hue_range_low and high which will store the range of
    hueAngles at which the colour is found
    return: 1 or 0 based on success or failure, hue_range ints are modified.
    */
    switch(colour) {
        default:
            return 1;
            break;
        case 0: //RED,
            *hue_range_low = 315;
            *hue_range_high = 345;
            break;
        case 1: //RED_ORANGE,
            // this is a weird case. could cause errors
            *hue_range_low = 345;
            *hue_range_high = 15;
            break;
        case 2: //ORANGE,
            *hue_range_low = 15;
            *hue_range_high = 45;
            break;
        case 3: //YELLOW_ORANGE,
            *hue_range_low = 45;
            *hue_range_high = 75;
            break;
        case 4: //YELLOW,
            *hue_range_low = 76;
            *hue_range_high = 105;
            break;
        case 5: //YELLOW_GREEN,
            *hue_range_low = 105;
            *hue_range_high = 135;
            break;
        case 6: //GREEN,
            *hue_range_low = 135;
            *hue_range_high = 165;
            break;
        case 7: //BLUE_GREEN,
            *hue_range_low = 165;
            *hue_range_high = 195;
            break;
        case 8: //BLUE,
            *hue_range_low = 195;
            *hue_range_high = 225;
            break;
        case 9: //BLUE_VIOLET,
            *hue_range_low = 225;
            *hue_range_high = 255;
            break;
        case 10: //VIOLET,
            *hue_range_low = 255;
            *hue_range_high = 285;
            break;
        case 11: //RED_VIOLET
            *hue_range_low = 285;
            *hue_range_high = 315;
            break;
    }
    return 0;
}


// helper functions

int getPaintValueHelperCopy(paint_t* spa, paint_t* pp, int* nspp, int i) {
    if (((spa == NULL) || (pp == NULL)) || (*nspp < 0)) {
        return 1;
    }
    strcpy(spa[*nspp].ciName, pp[i].ciName);
    strcpy(spa[*nspp].marketingName, pp[i].marketingName);
    strcpy(spa[*nspp].manufacturer, pp[i].manufacturer);
    strcpy(spa[*nspp].code, pp[i].code);
    spa[*nspp].transparency = pp[i].transparency;
    spa[*nspp].staining = pp[i].transparency;
    spa[*nspp].valueRange = pp[i].valueRange;
    spa[*nspp].granulating = pp[i].granulating;
    spa[*nspp].blossom = pp[i].blossom;
    spa[*nspp].diffusion = pp[i].diffusion;
    spa[*nspp].hueAngle = pp[i].hueAngle;
    spa[*nspp].hueShift = pp[i].hueShift;
    spa[*nspp].lightfast = pp[i].lightfast;

    return 0;
}


int printPaintHelper(paint_t* pp, int j) {
    if ((pp == NULL) || (j < 0)) {
        return 1;
    }
    printf("--------------\n");
    printf("ciName       : %s\n", pp[j].ciName);
    printf("marketingName: %s\n", pp[j].marketingName);
    printf("manufacturer : %s\n", pp[j].manufacturer);
    printf("transparency : %d\n", pp[j].transparency);
    printf("staining     : %d\n", pp[j].staining);
    printf("valueRange   : %d\n", pp[j].valueRange);
    printf("granulating  : %d\n", pp[j].granulating);
    printf("blossom      : %d\n", pp[j].blossom);
    printf("diffusion    : %d\n", pp[j].diffusion);
    printf("hueAngle     : %d\n", pp[j].hueAngle);
    printf("hueShift     : %d\n", pp[j].hueShift);
    printf("lightfast    : %d\n", pp[j].lightfast);
    return 0;
}

int printPigmentHelper(pigment_t* pp, int j) {
    if ((pp == NULL) || (j < 0)) {
        return 1;
    }
    printf("--------------\n");
    printf("ciName        : %s\n", pp[j].ciName);
    printf("pigmentName   : %s\n", pp[j].pigmentName);
    printf("value         : %d\n", pp[j].value);
    printf("chroma        : %d\n", pp[j].chroma);
    printf("(a,b)         : %ls\n", pp[j].abValue);
    printf("hue [degrees] : %d\n", pp[j].hueAngle);
    printf("huePurity     : %f\n", pp[j].huePurity);
    printf("(ahp,bhp)     : %f\n", *(pp[j].abHp));
    return 0;
}

int getPaintRangeHelper(gRange_t getType, float* actmin, float* actmax, float rmin, float rmax) {
    if (getType < 0 || getType > 6)  {
        return 1; // invalid input
    }
    if (actmin == NULL || actmax == NULL) {
        return 1; // null pointer error
    }
    switch(getType) {
        default:
                return 1;
        case 0:
            *actmin = 0;
            *actmax = 359 * rmax;
            break;
        case 1:
            *actmin = 35 * rmin;
            *actmax = 68 * rmax;
            break;
        case 2:
            *actmin = 0 * rmin;
            *actmax = 2 * rmax;
            break;
        case 3:
            *actmin = 0 * rmin;
            *actmax = 4 * rmax;
            break;
        case 4:
            *actmin = 0 * rmin;
            *actmax = 4 * rmax;
            break;
        case 5:
            *actmin = 0 * rmin;
            *actmax = 4 * rmax;
            break;
        case 6:
            *actmin = 1 * rmin;
            *actmax = 8 * rmax;
            break;
    }
    return 0;
}

int getPaintRangeValueHelper (gRange_t getType, paint_t* pp, int i, int* value) {
    if (getType < 0 || getType > 6)  {
        return 1; // invalid input
    }
    if (pp == NULL) {
        return 1;
    }
    int value = 0;
    switch (getType) {
        default:
            return 1;
        case 0:
            *value = pp[i].hueAngle;
            break;
        case 1:
            *value = pp[i].valueRange;
            break;
        case 2:
            *value = pp[i].granulating;
            break;
        case 3:
            *value = pp[i].transparency;
            break;
        case 4:
            *value = pp[i].staining;
            break;
        case 5:
            *value = pp[i].blossom;
            break;
        case 6:
            *value = pp[i].lightfast;
            break;
    }   
    return 0;
}