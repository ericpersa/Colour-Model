#include<stdio.h>
#include<stdlib.h>
#include"pigment.h"


int main(void) {
    //open file
    FILE* fd = fopen("../data/paints.dat", "r");
    if (fd == NULL) {
        printf("File Error\n");
        fclose(fd);
        return 1;
    }


    //dynamically allocate paint array of structures
    paint_t* pp = malloc(sizeof(paint_t));
    int n = 0;
    
    pp = loadPaintData("../data/paints.dat", pp , &n);
    if(pp == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }

    paint_t* spa;
    colour_t colour = RED_ORANGE; // testing this one specifically as it's a weird case
    spa = getPaintHue(pp, &n, colour);
    if(spa == NULL) {
        perror("An error has occured");
    }


    free(pp); pp=NULL; //free malloced array

    return(0);
}