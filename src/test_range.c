// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leew 3147578

#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
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
    paint_t* result_arr;
    int nspp = 0;
    float rmin_good = 0.1;
    float rmax_good = 1.0;
    gRange_t checkType = HUE;
    
    // testing getPaintRange
    result_arr = getPaintRange(paint_arr, paint_count, rmin_good, rmax_good, checkType, &nspp);
    if (result_arr == NULL) {
        printf("Error with getPaintRange: returned NULL\n");
        return 1;
    }
    int err = printPaint(result_arr, -1, nspp);
    if (err == 1) {
        printf("Error printing paints. printPaint returned 1\n");
        return 1;
    }

    // testing good values and expecting a return
    result_arr = NULL;
    nspp = 0;
    rmin_good = 0.6;
    rmax_good = 0.8;
    checkType = STAINING;
    
    // testing getPaintRange
    result_arr = getPaintRange(paint_arr, paint_count, rmin_good, rmax_good, checkType, &nspp);
    if (result_arr == NULL) {
        printf("Error with getPaintRange: returned NULL\n");
        return 1;
    }
    err = printPaint(result_arr, -1, nspp);
    if (err == 1) {
        printf("Error printing paints. printPaint returned 1\n");
        return 1;
    }

    int rmin_bad = -3;
    int rmax_bad = 1.1111;
    paint_t* bad_arr;
    gRange_t checkType_2 = GRANULATING;
    bad_arr = getPaintRange(paint_arr, paint_count, rmin_bad, rmax_bad, checkType_2, &nspp);
    if (bad_arr == NULL) {
        printf("Error with getPaintRange: returned NULL\n");
        return 1;
    }
    int err_2 = printPaint(bad_arr, -1, nspp);
    if (err_2 == 1) {
        printf("Error printing paints. printPaint returned 1\n");
        return 1;
    }



    free(result_arr); 
    free(paint_arr);
    free(bad_arr);
    paint_arr = NULL;
    result_arr = NULL;
}