#include<stdio.h>
#include"pigment.h"


int main(void) {
    int n = 0;

    //open file
    FILE* fd = fopen("../data/paints.dat", "r");
    if (fd == NULL) {
        printf("File Error\n");
        fclose(fd);
        return 1;
    }

    //dynamically allocate paint array of structures
    paint_t* pp = malloc(sizeof(paint_t));
    
    // call paint function and check output
    pp = loadPaintData("../data/paints.dat", pp , &n);
    if(paint_arr == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }

    return(0);
}