#include "pigment.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("FILE OPEN\n\n");

    //dynamically allocate paint array of structures
    paint_t* pp = malloc(sizeof(paint_t));
    
    // call paint function and check output
    pp= loadPaintData("../data/paints.dat", pp ,&paint_count);
    if(pp == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }
    printf("data loaded\n\n");
    //test values for getPaintValue
    int npp = paint_count;
    char name[] = "cerulean blue";
    gValue_t type;
    type = MARKETINGNAME;
    int* nspp = 0;

    printf("DECLARE VAR\n\n");
    //call get paint value function
    paint_t* spa = getPaintValue(pp, npp, name, type, nspp);
    printf("exit get val\n\n");

    for(int i =0; i<*nspp; i++){
        printf("---------");
        printf("%s",spa[i].manufacturer);
        printf("%s",spa[i].ciName);
    }

    free(pp);
    free(spa);
    spa = NULL;
    pp = NULL;
}