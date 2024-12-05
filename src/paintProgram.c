#include<stdio.h>
#include"pigment.h"

int main(void) {
    printMenu();
}

int printMenu(void) {
    printf("Welcome to Paints Program");
    printf("Choose one of the following:");
    printf("(0) Quit");
    printf("(1) Enter a Palette type (Currently set at: None)");
    printf("(2) Enter a Palette Property (Currently set at: None)");
    printf("(3) Print Palette Choice");
    printf("(4) Help (view valid palette types and properties");
}