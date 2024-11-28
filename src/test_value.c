#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test value
int main(void){
    // load data into array
    int paint_count = 0;
    FILE* fd = fopen("../data/paints.dat", "r");
    if (fd == NULL) {
        printf("File Error\n");
        fclose(fd);
        return 1;
    }

    //dynamically allocate paint array of structures
    paint_t* pp = malloc(sizeof(paint_t));
    
    // call paint function and check output
    pp= loadPaintData("../data/paints.dat", pp ,&paint_count);
    if(pp == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }

    //test values for getPaintValue
    int npp = paint_count;
    gValue_t type;
    int nspp = 0;
    
    //test case 1
    char name[] = "cerulean blue";
    type = MARKETINGNAME;
    //test case 2
    //char name[] = "pr122";
    //type = CINAME;
    //test case 3
    //char name[] = "Winsor & Newton";
    //type = MANUFACTURER;

    //call get paint value function
    paint_t* spa;
    spa = getPaintValue(pp, npp, name, type, &nspp);

    if(spa == NULL){
        printf("Error in subarray");
        return(1);
    }

    printPaint(spa, -1, nspp);

    free(pp);
    free(spa);
    spa = NULL;
    pp = NULL;
}