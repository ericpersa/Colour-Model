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
    paint_arr = loadPaintData("../data/paints.dat", pp ,&paint_count);
    if(paint_arr == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }

    //call get paint value function


}