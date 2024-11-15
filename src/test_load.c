
#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int ret;
    int paint_count = 10;
    //char line[200];

    //open file
    FILE* fd = fopen("../data/paints.dat", "r");
    if (fd == NULL) {
        printf("File Error\n");
        return 1;
    }

    //dynamically allocate paint array of structures
    paint_t* paint_arr = malloc(sizeof(paint_t)*10);
    fclose(fd);

    // call paint function and check output
    ret = loadPaintData("../data/paints.dat", paint_arr ,&paint_count);
    if(ret == 1){
        printf("Error loading paint_t");
        exit(EXIT_FAILURE);
    }

    //int testnum = 3;
    int testnum = 8;
    printf("testing lines in array:\n");
    printf("ci:%s, Mn:%s, man:%s", paint_arr[testnum].ciName, paint_arr[testnum].marketingName, paint_arr[testnum].manufacturer);
    printf(" ,code:%i ,tran:%i, sta:%i, VR:%i", paint_arr[testnum].code, paint_arr[testnum].transparency, paint_arr[testnum].staining, paint_arr[testnum].valueRange);
    printf(" ,gr:%i, bl:%i, di:%i", paint_arr[testnum].granulating, paint_arr[testnum].blossom, paint_arr[testnum].diffusion);
    printf(" ,HA:%i, HS:%i, LF:%i\n", paint_arr[testnum].hueAngle, paint_arr[testnum].hueShift, paint_arr[testnum].lightfast);

    exit(EXIT_SUCCESS);
}