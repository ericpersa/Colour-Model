#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"pigment.h"

int main(void) {
    int quit = 0; // sentinel value to keep the program running
    int menuChoice;
    char paletteType[50] = "";
    char paletteProperty[50] = "";
    int err;


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
            
        }
        if (menuChoice == 4) {
            // help option
            help();
        }
        else if (menuChoice == 0) {
            quit = 1;
        }
    }
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
        (strcmp(getPaletteType, "split") == 0) ) {
        // user input is valid.
        strcpy(paletteType, getPaletteType);
    }
    return 0;
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