#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //Jenna's test
    int paint_count = 0;

    //open file
    FILE* fd = fopen("../data/paints.dat", "r");
    if (fd == NULL) {
        printf("File Error\n");
        fclose(fd);
        return 1;
    }

    //dynamically allocate paint array of structures
    paint_t* paint_arr = malloc(sizeof(paint_t));
    
    // call paint function and check output
    paint_arr = loadPaintData("../data/paints.dat", paint_arr ,&paint_count);
    if(paint_arr == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }

    // testing good values and expecting a return
    int nspp = 0;
    float rmin_good = 0.4;
    float rmax_good = 1.0;
    gRange_t checkType = "hue";

    paint_t* getPaintRange(paint_arr, paint_count, rmin_good, rmax_good, getType, &nspp)


    free(paint_arr);
    paint_arr = NULL;
}