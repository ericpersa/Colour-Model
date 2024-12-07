#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"pigment.h"

int valAndValidate(const char* paletteProperty);

int main(void) {
    int quit = 0; // sentinel value to keep the program running
    int menuChoice;
    char paletteType[50] = "";
    char paletteProperty[50] = "";
    char colour[20] = "";
    int err;
    paint_t* prArr;
    int sizeMainArr = 0;


    //dynamically allocate paint array of structures
    paint_t* mainArr = malloc(sizeof(paint_t));
    
    // call paint function and check output
    mainArr = loadPaintData("data/paints.dat", mainArr ,&sizeMainArr);
    if(mainArr == NULL){
        printf("Error loading paint_t\n");
        return(1);
    }






    while (quit == 0) {
        printMenu(paletteType, paletteProperty);
        char buffer[50];

        if (fgets(buffer, 50, stdin) != NULL) {
            menuChoice = atoi(buffer);
        }

        if ((menuChoice < 0) || (menuChoice > 4)) {
            printf("ERROR: Selection must be between 0 and 4.");
        }
        

        if (menuChoice == 1) {

            err = paletteTypeHelper(paletteType);
            if (err == 1) {
                printf("Error occured setting a paletteType");
            }

        }
        if (menuChoice == 2) {

            err = palettePropertyHelper(paletteProperty);
            if (err == 1) {
                printf("Error occured setting a paletteProperty");
            }


        }
        if (menuChoice == 3) {

            // we need to ensure that palette type is not null
            if (strcmp(paletteType, "") == 0) {
                // the string is empty and this we do not have a palette type
                printf("Error printing palette choice: palette type has no value. A palette type must be set using option (1)\n");
            }
            else {
                // we need to get a color from the user.
                char input[20] = "";
                // user enters a color
                printf("Please enter a a color in all caps - (RED, RED_ORANGE, ORANGE, YELLOW_ORANGE, YELLOW, YELLOW_GREEN, GREEN, BLUE_GREEN, BLUE, BLUE_VIOLET, VIOLET, RED_VIOLET): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                
                if (getColourHelper(input) != NULL) {
                    strcpy(colour, getColourHelper(input));
                    if (strcmp(paletteProperty, "") == 0) {
                        // case where we now have enough information to print
                        char combined[100];
                        snprintf(combined, sizeof(combined), "%s:%s\n", paletteType, colour);
                        prArr = getPalette(mainArr, &sizeMainArr, combined, NULL);
                        printPaint(prArr, -1, sizeMainArr);
                    }
                    else {
                        int getValue = valAndValidate(paletteProperty);
                        char combined[100];
                        snprintf(combined, sizeof(combined), "%s:%s\n", paletteType, colour);
                        char combined2[100];
                        snprintf(combined2, sizeof(combined2), "%s:%d\n", paletteProperty, getValue);
                        prArr = getPalette(mainArr, &sizeMainArr, combined, combined2);
                        printPaint(prArr, -1, sizeMainArr);
                    }
                    
                }
            }
            // create valid input

        }
        if (menuChoice == 4) {
            // help option
            help();
        }
        else if (menuChoice == 0) {
            quit = 1;
        }
    }
    free(mainArr);
    mainArr = NULL;
}




void printMenu(char* paletteType, char* paletteProperty) {
    printf("(0) Quit\n");
    printf("(1) Enter a Palette type (Currently set at: %s)\n", ((paletteType && paletteType[0] != '\0') ? paletteType : "None"));
    printf("(2) Enter a Palette Property (Currently set at: %s)\n", ((paletteProperty && paletteProperty[0] != '\0') ? paletteProperty : "None"));
    printf("(3) Print Palette Choice\n");
    printf("(4) Help (view valid palette types and properties\n");
}

void help(void) {
    printf("\nHelp: Palette Types and Their Properties\n\n");

    printf("1) Full Palette:\n");
    printf("   This palette contains 12 colours: red, red-orange, orange, yellow-orange,\n");
    printf("   yellow, yellow-green, green, blue-green, blue, blue-violet, violet, and red-violet.\n\n");

    printf("2) Triad Palette:\n");
    printf("   This palette consists of 3 colours equally spaced around the colour wheel.\n");
    printf("   To create this palette, specify one colour (e.g., triad:yellow gives yellow, blue, red).\n\n");

    printf("3) Complimentary Palette:\n");
    printf("   This palette has 2 colours that are directly opposite on the colour wheel.\n");
    printf("   To create this palette, specify one colour (e.g., complimentary:yellow gives yellow and violet).\n\n");

    printf("4) Split Complimentary Palette:\n");
    printf("   This palette has 3 colours: the base colour and the two adjacent to its complement.\n");
    printf("   To create this palette, specify one colour (e.g., split complimentary:yellow gives yellow, red-violet, and blue-violet).\n\n");

    printf("Note: When defining a palette, type the palette name followed by the base colour (e.g., triad:blue).\n");
}

int paletteTypeHelper(char* paletteType) {
    char getPaletteType[50] = "";
    // user enters a palette type
    printf("Select Palette Type - full, triad, complimentary, split (split complimentary): ");
    
    if (fgets(getPaletteType, 49, stdin) == NULL) {
        printf("Error occurred setting a palette type.\n");
        return 1;
    } 
    else {
        getPaletteType[strcspn(getPaletteType, "\n")] = 0;
    }
    
    if ((strcmp(getPaletteType, "full") == 0) ||
        (strcmp(getPaletteType, "triad") == 0) ||
        (strcmp(getPaletteType, "complimentary") == 0) ||
        (strcmp(getPaletteType, "split complimentary") == 0) ) {
        // user input is valid.
        strcpy(paletteType, getPaletteType);
    }
    return 0;
}


char* getColourHelper(char* input) {

    if (strcmp(input, "RED") == 0) return "RED";
    if (strcmp(input, "RED_ORANGE") == 0) return "RED_ORANGE";
    if (strcmp(input, "ORANGE") == 0) return "ORANGE";
    if (strcmp(input, "YELLOW_ORANGE") == 0) return "YELLOW_ORANGE";
    if (strcmp(input, "YELLOW") == 0) return "YELLOW";
    if (strcmp(input, "YELLOW_GREEN") == 0) return "YELLOW_GREEN";
    if (strcmp(input, "GREEN") == 0) return "GREEN";
    if (strcmp(input, "BLUE_GREEN") == 0) return "BLUE_GREEN";
    if (strcmp(input, "BLUE") == 0) return "BLUE";
    if (strcmp(input, "BLUE_VIOLET") == 0) return "BLUE_VIOLET";
    if (strcmp(input, "VIOLET") == 0) return "VIOLET";
    if (strcmp(input, "RED_VIOLET") == 0) return "RED_VIOLET";

    return NULL; // If no match, return INVALID_COLOR
}


int palettePropertyHelper(char* paletteProperty) {
    char getPaletteProperty[50] = "";
    // user enters a palette type
    printf("Select Palette Property - granulating, transparency, diffusion, value range, staining, blossom and lightfast: ");

    if (fgets(getPaletteProperty, 49, stdin) == NULL) {
        printf("Error occurred setting a palette property.\n");
        return 1;
    } 
    else {
        getPaletteProperty[strcspn(getPaletteProperty, "\n")] = 0;
    }

    if ((strcmp(getPaletteProperty, "granulating") == 0) ||
        (strcmp(getPaletteProperty, "transparency") == 0) ||
        (strcmp(getPaletteProperty, "diffusion") == 0) ||
        (strcmp(getPaletteProperty, "value range") == 0) ||
        (strcmp(getPaletteProperty, "staining") == 0) ||
        (strcmp(getPaletteProperty, "blossom") == 0) ||
        (strcmp(getPaletteProperty, "lightfast") == 0)) {
        // valid input, copy into given paletteProperty
        strcpy(paletteProperty, getPaletteProperty);
    }
    return 0;
}


int valAndValidate(const char* paletteProperty) {

    int value = -1;

    if (strcmp(paletteProperty, "granulating") == 0) {
        while (value < 0 || value > 4) {
            printf("Enter value for Granulation (0 - 4): ");
            scanf("%d", &value);
            if (value < 0 || value > 4) {
                printf("Invalid value. Granulation must be between 0 and 4.\n");
            }
        }
        return value;
    } 
    else if (strcmp(paletteProperty, "transparency") == 0) {
        while (value < 0 || value > 4) {
            printf("Enter value for Transparency (0 - 4): ");
            scanf("%d", &value);
            if (value < 0 || value > 4) {
                printf("Invalid value. Transparency must be between 0 and 4.\n");
            }
        }
        return value;
    }
    else if (strcmp(paletteProperty, "diffusion") == 0) {
        while (value < 0 || value > 4) {
            printf("Enter value for Diffusion (0 - 4): ");
            scanf("%d", &value);
            if (value < 0 || value > 4) {
                printf("Invalid value. Diffusion must be between 0 and 4.\n");
            }
        }
        return value;
    }
    else if (strcmp(paletteProperty, "value range") == 0) {
        while (value < 0 || value > 100) {
            printf("Enter value for Value Range (0 - 100): ");
            scanf("%d", &value);
            if (value < 0 || value > 100) {
                printf("Invalid value. Value Range must be between 0 and 100.\n");
            }
        }
        return value;
    }

    else if (strcmp(paletteProperty, "staining") == 0) {
        while (value < 0 || value > 4) {
            printf("Enter value for Staining (0 - 4): ");
            scanf("%d", &value);
            if (value < 0 || value > 4) {
                printf("Invalid value! Staining must be between 0 and 4.\n");
            }
        }
        return value;
    }
    else if (strcmp(paletteProperty, "blossom") == 0) {
        while (value < 0 || value > 4) {
            printf("Enter value for Blossom (0 - 4): ");
            scanf("%d", &value);
            if (value < 0 || value > 4) {
                printf("Invalid value! Blossom must be between 0 and 4.\n");
            }
        }
        return value;
    }
    else if (strcmp(paletteProperty, "lightfast") == 0) {
        while (value < 1 || value > 8) {
            printf("Enter value for Lightfastness (1 - 8): ");
            scanf("%d", &value);
            if (value < 1 || value > 8) {
                printf("Invalid value. Lightfastness must be between 1 and 8.\n");
            }
        }
        return value;
    } 
    else {
        printf("Unknown palette property: %s\n", paletteProperty);
        return value;
    }
}
