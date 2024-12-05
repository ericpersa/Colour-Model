// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leew 3147578

//test for getPalette

#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    //test conditions 
    char type[] = "triad:YELLOW";
    //char type[] = "complimentary:GREEN";
    //char type[] = "split complementary: ORANGE";
    char* properties = NULL;
    //char properties[] = "granulating:4";
    //char properties[] = "transparency:2";
    //char properties[] = "valueRange:50";

    //paint_t newpalette = malloc()
    paint_t* newpalette = getPalette(pp, &paint_count, type, properties);
    //error check
    if(newpalette == NULL){
        printf("Error in creating new palette");
        return(1);
    }
    //print out all paints in pallete
    printPaint(newpalette, -1, paint_count);

    //free data before return
    free(pp);
    free(newpalette);
    pp = NULL;
    newpalette = NULL;

    return(0);
}
