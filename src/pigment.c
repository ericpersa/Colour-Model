// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leew 3147578
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
    for (int i = 0; i < *n; i++) {
        if((index+1) == size){
            size = size *2;
            spa = realloc(spa, size*sizeof(paint_t));
        }

        if (colour == 0) {
            // RED is a weird case where it must be between 345 and 15 degrees
            if (((pp[i].hueAngle >= 0) && (pp[i].hueAngle <= 15)) || 
            ((pp[i].hueAngle >= 345) && (pp[i].hueAngle <= 360))) {
                // valid for red
                int err = getPaintValueHelperCopy(spa, pp, &index, i);
                if (err == 1) {
                    printf("Error Copying values in getPaintHue. returning NULL");
                    return(NULL);
                }
                index++;  
            }
        }
        else if ((pp[i].hueAngle >= hue_range_low) && (pp[i].hueAngle <= hue_range_high)) {
            int err = getPaintValueHelperCopy(spa, pp, &index, i);
            if (err == 1) {
                printf("Error Copying values in getPaintHue. returning NULL");
                return(NULL);
            }
            index++;
        }
    }
    printf("%d",index);
    /* n that we got is the size of the full paint array, want it to return size of
    newly made array, which should be tracked by index
    */
   *n = index;
    return spa;
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
        case 0: // RED
            *hue_range_low = 345;
            *hue_range_high = 15;
            break;
        case 1: // RED_ORANGE
            *hue_range_low = 15;
            *hue_range_high = 45;
            break;
        case 2: // ORANGE
            *hue_range_low = 45;
            *hue_range_high = 75;
            break;
        case 3: // YELLOW_ORANGE
            *hue_range_low = 75;
            *hue_range_high = 105;
            break;
        case 4: // YELLOW
            *hue_range_low = 105;
            *hue_range_high = 135;
            break;
        case 5: // YELLOW_GREEN
            *hue_range_low = 135;
            *hue_range_high = 165;
            break;
        case 6: // GREEN
            *hue_range_low = 165;
            *hue_range_high = 195;
            break;
        case 7: // BLUE_GREEN
            *hue_range_low = 195;
            *hue_range_high = 225;
            break;
        case 8: // BLUE
            *hue_range_low = 225;
            *hue_range_high = 255;
            break;
        case 9: // BLUE_VIOLET
            *hue_range_low = 255;
            *hue_range_high = 285;
            break;
        case 10: // VIOLET
            *hue_range_low = 285;
            *hue_range_high = 315;
            break;
        case 11: // RED_VIOLET
            *hue_range_low = 315;
            *hue_range_high = 345;
            break;
    }
    return 0;
}

paint_t* getPalette (paint_t* pp, int* n, char* type, char* properties){
    //input of type = "<palette type> : <color>"
    //input of properties = "<property type> : <value of property>"

    char palette[20];
    char color[50];
    char proptype[50];
    int propval;
    char* token;
    paint_t* pps;
    int ncopy = *n;

    //error check 
    if( pp == NULL || n<0){
        return NULL;
    }
    printf("Null check complete\n");
    printf("%s\n", type);
    //separate the palette type from the colour specified 
    token = strtok(type, ":");
    strcpy(palette, token);

    // printf("Quarter token\n");

    token = strtok(NULL, "\0");
    strcpy(color, token);

    printf("Halfway token\n");
    
    if(properties != NULL){
        printf("%s\n", properties);
        //seperate the property type from the value specified 
        token = strtok(properties, ":");
        strcpy(proptype, token);
        token = strtok(NULL, "\0");
        propval = atoi(token);
    }
    else{
        strcpy(proptype, "NULL");
        propval = -1;
    }



    printf("Helper functions start\n");
    //determine other colours needed based on the palette type
    //type full
    if(strcmp(palette, "full")==0){
        if(proptype == NULL){
            return pp;
        }
        pps = paletteFullHelper(pp, n, proptype, propval);
        *n = ncopy;
        return(pps);
    }
    //type triad
    else if(strcmp(palette, "triad")==0){
        //get unsorted array of colors, then send to helper to get palette with only values that fit properties 
        printf("Triad if statement entered\n");
        paint_t* unsortedpps = paletteTriadHelper(pp, &ncopy, color);
        printf("prop type: %s\n", proptype);

        // if there are no properties to sort through return subarray
        if(strcmp(proptype, "NULL") == 0){
            printf("prop type null\n");
            *n = ncopy;
            return(unsortedpps);
        }
        pps = paletteFullHelper(unsortedpps, &ncopy, proptype, propval);

        //free unsorted since it is done being used
        free(unsortedpps);
        unsortedpps = NULL;

        //return sorted palette
        *n = ncopy;
        printf("*n leaving getPalette: %d\n", *n);
        return(pps);
    }
    //type complementary
    else if(strcmp(palette, "complementary")==0){
        paint_t* unsortedpps = paletteComplementaryHelper(pp, &ncopy, color);

        // if there are no properties to sort through return subarray
        if(proptype == NULL){
            return(unsortedpps);
        }
        pps = paletteFullHelper(unsortedpps, &ncopy, proptype, propval);

         //free unsorted since it is done being used
        free(unsortedpps);
        unsortedpps = NULL;

        *n = ncopy;
        return(pps);
    }
    //type split complementary
    else if(strcmp(palette, "split complementary")==0){
        paint_t* unsortedpps = paletteSplitCompHelper(pp, &ncopy, color);
        // if there are no properties to sort through return subarray
        if(proptype == NULL){
            return(unsortedpps);
        }
        pps = paletteFullHelper(unsortedpps, &ncopy, proptype, propval);

        //free unsorted since it is done being used
        free(unsortedpps);
        unsortedpps = NULL;

        *n = ncopy;
        return(pps);
    }
    //if palette entered is not a valid palette type
    printf("Invalid palette\n");
    return(NULL);
    
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
    // int value = 0;
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

paint_t* paletteFullHelper(paint_t* pp, int* n, char* proptype, int propval){
    //error check inputs
    if(pp== NULL || n<0){
        return(NULL);
    }
    if(proptype == NULL){
        return(pp);
    }

    int size = 1;
    int count = 0;

    paint_t* pps = malloc(size * sizeof(paint_t));
    if (pps == NULL) {
        printf("Failed to allocate memory");
        return(NULL);
    }
    //granulation 0-4
    if(strcmp(proptype, "granulating")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].granulating == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //transparency 0-4
    if(strcmp(proptype, "transparency")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].transparency == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //diffusion 0-4
    if(strcmp(proptype, "diffusion")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].diffusion == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //chroma 0-100
    if(strcmp(proptype, "value range")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].valueRange == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //staining 0-4
    if(strcmp(proptype, "staining")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].staining == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //blossom
    if(strcmp(proptype, "blossom")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].blossom == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    //lightfastness
    if(strcmp(proptype, "lightfast")==0){
        for(int i = 0; i<*n; i++){
            if(pp[i].lightfast == propval){
                if(count == size){
                    size += 10; 
                    pps = realloc(pps, size*sizeof(paint_t));
                }
                getPaintValueHelperCopy(pps, pp, &count, i);
                count ++;
            }
        }
    }
    *n = count;
    return(pps);
}

paint_t* paletteTriadHelper(paint_t* pp, int* n, char* color){
    //error check inputs
    if(pp == NULL || n<0){
        return(NULL);
    }
     //get a new n for each call to get back the number of values in sub arrays
    int n1 = *n;
    int n2 = *n;
    int n3 = *n;
        
    printf("TRAID HELPER ENTERED\n");
    //create pointers for sub arrays for output of getPaintHue
    paint_t* array1;
    paint_t* array2;
    paint_t* array3;

    //check colors to find which trio of colors need to be found   
    if(strcmp(color, "YELLOW")==0 || strcmp(color, "RED")==0 || strcmp(color, "BLUE")==0){
        //call getPaintHue to get data
        array1 = getPaintHue(pp, &n1, YELLOW);
        array2 = getPaintHue(pp, &n2, RED);
        array3 = getPaintHue(pp, &n3, BLUE);
    }
    else if(strcmp(color, "YELLOW_ORANGE")==0 ||strcmp(color, "BLUE_GREEN")==0 || strcmp(color, "RED_VIOLET")==0){
        array1 = getPaintHue(pp, &n1, YELLOW_ORANGE);
        array2 = getPaintHue(pp, &n2, BLUE_GREEN);
        array3 = getPaintHue(pp, &n3, RED_VIOLET);
    }
    else if(strcmp(color, "ORANGE")==0 || strcmp(color, "GREEN")==0 || strcmp(color, "VIOLET")==0){
        array1 = getPaintHue(pp, &n1, ORANGE);
        array2 = getPaintHue(pp, &n2, GREEN);
        array3 = getPaintHue(pp, &n3, VIOLET);
    }   
    else if(strcmp(color, "RED_ORANGE")==0 || strcmp(color, "YELLOW_GREEN")==0 || strcmp(color, "BLUE_VOILET")==0){
        array1 = getPaintHue(pp, &n1, RED_ORANGE);
        array2 = getPaintHue(pp, &n2, YELLOW_GREEN);
        array3 = getPaintHue(pp, &n3, BLUE_VIOLET);
    }
    //if no color is called
    else{
        return(NULL);
    }

    printf("GOT PAINT HUES\n");

    //create dynamic array for putting final array into
    int size = 1;
    paint_t* pps = malloc(size * sizeof(paint_t));
    if (pps == NULL) {
        printf("Failed to allocate memory");
        return(NULL);
    }
    //implement all colours into one array
    int count = 0;
    int ret;
    for(int i = 0; i<n1; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array1, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }
    for(int i = 0; i<n2; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret =getPaintValueHelperCopy(pps, array2, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }
    for(int i = 0; i<n3; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array3, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }

    //set n equal to sum of array 1+2+3
    // *n = n1+n2+n3;
    *n = count;
    printf("*n at the end of triad helper: %d\n", *n);

    //return array
    return(pps);

}

paint_t* paletteComplementaryHelper(paint_t* pp, int* n, char* color){
     //get a new n for each call to get back the number of values in sub arrays without altering original n
    int n1 = *n;
    int n2 = *n;
    //create pointers for sub arrays for output of getPaintHue
    paint_t* array1;
    paint_t* array2;

    if(strcmp(color,"YELLOW") == 0 || strcmp(color, "VIOLET") == 0){
        array1 = getPaintHue(pp, &n1, YELLOW);
        array2 = getPaintHue(pp, &n2, VIOLET);
    }
    else if(strcmp(color,"YELLOW_ORANGE") == 0 || strcmp(color, "BLUE_VOILET") ==0){
        array1 = getPaintHue(pp, &n1, YELLOW_ORANGE);
        array2 = getPaintHue(pp, &n2, BLUE_VIOLET);

    }
    else if(strcmp(color, "BLUE") ==0 || strcmp(color, "ORANGE") ==0){
        array1 = getPaintHue(pp, &n2, BLUE);
        array2 = getPaintHue(pp, &n1, ORANGE);
    }
    else if(strcmp(color, "RED_ORANGE")==0 || strcmp(color, "BLUE_GREEN")==0){
        array1 = getPaintHue(pp, &n1, RED_ORANGE);
        array2 = getPaintHue(pp, &n2, BLUE_GREEN);
    }
    else if(strcmp(color, "RED")==0 || strcmp(color,"GREEN") ==0){
        array1 = getPaintHue(pp, &n1, RED);
        array2 = getPaintHue(pp, &n2, GREEN);
    }
    else if(strcmp(color, "RED_VIOLET")==0 || strcmp(color, "YELLOW_GREEN")==0){
        array1 = getPaintHue(pp, &n1, RED_VIOLET);
        array2 = getPaintHue(pp, &n2, YELLOW_GREEN);
    }
     else{
        return(NULL);
    }

    //create dynamic sub array for colours 
    int size = 1;
    paint_t* pps = malloc(size * sizeof(paint_t));
    if (pps == NULL) {
        printf("Failed to allocate memory");
        return(NULL);
    }
    //implement all colours into one array
    int count = 0;
    int ret;
    //add array 1 into total array
    for(int i = 0; i<n1; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array1, &count, i);
            count ++;
    }
    //error check copy
    if(ret == 1){
        return(NULL);
    }
    //add array2 into total array
    for(int i = 0; i<n2; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array2, &count, i);
            count ++;
    }
    //error check copy
    if(ret == 1){
        return(NULL);
    }
    //set n equal to sum of array 1+2
    *n = n1+n2;
    return(pps);
}

 paint_t* paletteSplitCompHelper(paint_t* pp, int* n, char* color){
    //error check inputs
    if(pp == NULL || n<0){
        return(NULL);
    }

     //get a new n for each call to get back the number of values in sub arrays
    int n1 = *n;
    int n2 = *n;
    int n3 = *n;
        
    //create pointers for sub arrays for output of getPaintHue
    paint_t* array1;
    paint_t* array2;
    paint_t* array3;
    
    //check each color 
    if(strcmp(color, "YELLOW") ==0){
        array1 = getPaintHue(pp, &n1, YELLOW);
        array2 = getPaintHue(pp, &n2, BLUE_VIOLET);
        array3 = getPaintHue(pp, &n3, RED_VIOLET);
    }
    else if (strcmp(color, "YELLOW-ORANGE")==0){
        array1 = getPaintHue(pp, &n1, YELLOW_ORANGE);
        array2 = getPaintHue(pp, &n2, BLUE);
        array3 = getPaintHue(pp, &n3, VIOLET);
    }
    else if(strcmp(color, "ORANGE")==0){
        array1 = getPaintHue(pp, &n1, ORANGE);
        array2 = getPaintHue(pp, &n2, BLUE_GREEN);
        array3 = getPaintHue(pp, &n3, BLUE_VIOLET);
    }
    else if(strcmp(color, "RED-ORANGE")==0){
        array1 = getPaintHue(pp, &n1, RED_ORANGE);
        array2 = getPaintHue(pp, &n2, GREEN);
        array3 = getPaintHue(pp, &n3, BLUE);
    }
    else if(strcmp(color, "RED")==0){
        array1 = getPaintHue(pp, &n1, RED);
        array2 = getPaintHue(pp, &n2, YELLOW_GREEN);
        array3 = getPaintHue(pp, &n3, BLUE_GREEN);
    }
    else if(strcmp(color, "RED-VIOLET")==0){
        array1 = getPaintHue(pp, &n1, RED_VIOLET);
        array2 = getPaintHue(pp, &n2, YELLOW);
        array3 = getPaintHue(pp, &n3, GREEN);
    }
    else if(strcmp(color, "VIOLET")==0){
        array1 = getPaintHue(pp, &n1, VIOLET);
        array2 = getPaintHue(pp, &n2, YELLOW_ORANGE);
        array3 = getPaintHue(pp, &n3, YELLOW_GREEN);
    }
    else if(strcmp(color, "BLUE-VIOLET")==0){
        array1 = getPaintHue(pp, &n1, BLUE_VIOLET);
        array2 = getPaintHue(pp, &n2, ORANGE);
        array3 = getPaintHue(pp, &n3, YELLOW);
    }
    else if(strcmp(color, "BLUE")==0){
        array1 = getPaintHue(pp, &n1, BLUE);
        array2 = getPaintHue(pp, &n2, RED_ORANGE);
        array3 = getPaintHue(pp, &n3, YELLOW_ORANGE);
    }
    else if(strcmp(color, "BLUE-GREEN")==0){
        array1 = getPaintHue(pp, &n1, BLUE_GREEN);
        array2 = getPaintHue(pp, &n2, RED);
        array3 = getPaintHue(pp, &n3, ORANGE);
    }
    else if(strcmp(color, "GREEN")==0){
        array1 = getPaintHue(pp, &n1, GREEN);
        array2 = getPaintHue(pp, &n2, RED_VIOLET);
        array3 = getPaintHue(pp, &n3, RED_ORANGE);
    }
    else if(strcmp(color, "YELLOW-GREEN")==0){
        array1 = getPaintHue(pp, &n1, YELLOW_GREEN);
        array2 = getPaintHue(pp, &n2, VIOLET);
        array3 = getPaintHue(pp, &n3, RED);
    }

    int size = 1;
    paint_t* pps = malloc(size * sizeof(paint_t));
    if (pps == NULL) {
        printf("Failed to allocate memory");
        return(NULL);
    }

    //implement all colours into one array
    int count = 0;
    int ret;
    for(int i = 0; i<n1; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array1, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }
    for(int i = 0; i<n2; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret =getPaintValueHelperCopy(pps, array2, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }
    for(int i = 0; i<n3; i++){
        if(count == size){
            size += 10; 
            pps = realloc(pps, size*sizeof(paint_t));
        }
        ret = getPaintValueHelperCopy(pps, array3, &count, i);
            count ++;
    }
    //error check copy
    if(ret ==1){
        return(NULL);
    }

    //set n equal to sum of array 1+2+3
    *n = n1+n2+n3;
    return(pps);
 }