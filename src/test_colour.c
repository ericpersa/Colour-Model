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
    colour_t colour = RED; // testing this one specifically as it's a weird case

    int size_new = n; // copy n
    
    
    
    spa = getPaintHue(pp, &size_new, colour);
    if(spa == NULL) {
        perror("An error has occured");
    }

    printPaint(spa, -1, size_new);


    free(pp); pp=NULL; //free malloced array
    free(spa); spa=NULL;

    return(0);
}