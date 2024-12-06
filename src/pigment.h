// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leew 3147578

typedef enum {
    HUE,
    VALUE,
    GRANULATING,
    TRANSPARENT,
    STAINING,
    BLOOM,
    LIGHTFAST
} gRange_t;

typedef enum {
    RED,
    RED_ORANGE,
    ORANGE,
    YELLOW_ORANGE,
    YELLOW,
    YELLOW_GREEN,
    GREEN,
    BLUE_GREEN,
    BLUE,
    BLUE_VIOLET,
    VIOLET,
    RED_VIOLET
} colour_t;

typedef struct pigment_t {
    char ciName[50];
    char pigmentName[50];
    int value;
    int abValue[2];
    int chroma;  
    int hueAngle;   
    float huePurity;    
    float abHp[2];        
} pigment_t;

typedef struct paint_t{
    char ciName[50];
    char marketingName[50];
    char manufacturer[50];
    char code[5];
    int transparency;
    int staining;
    int valueRange;
    int granulating;
    int blossom;
    int diffusion;
    int hueAngle;
    int hueShift;
    int lightfast;
} paint_t;

typedef enum {CINAME, MARKETINGNAME, MANUFACTURER} gValue_t;

paint_t* loadPaintData( char* , paint_t* , int*);
/***
    purpose:
        read in data line by line from file of paints, taking each specified value and putting it 
        into array of paint_t structs.
    input:
        filename: 
            pointer to where the file containing paint values is stored
        pArray:
            Array containing paint_t structs for each paint from file
        n:
            number of paints that have been input into pArray
***/

paint_t* getPaintValue(paint_t*, int, char*, gValue_t, int*);
/***
    purpose:
        
    input:
        pp:
            pointer to loaded array of paint data
        npp
            number of elements within the paint data array
        name:
            name that the code is looking to match within the array
        getType:
            enumeration of ciName, marketingName, manufacturer
        nspp:
            pointer to the number of elements found that contain the same value as name
***/

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n);
/*
    purpose: 
     loadPigmentData will read data line by line from the filename data location into a pigment_t  
     structure
    input:
     filename:
         a pointer to the file where the data is stored
     pArray:
         an array of pigment structures where the data is stored
     n:
         a pointer to the number of entries found.
*/

paint_t* getPaintRange(paint_t* pp, int npp, float rmin, float rmax, gRange_t getType, int* nspp);

int printPigment(pigment_t* pp, int i, int n); // question 1 of milestone 2
// question 1 milestone 2
    /*
    purpose: 
        prints pigments within an array in a formatted way
    input:
    pp
        pointer pointing to an array of pigment structures
    n:
        the size of pp
    i
        index of the array to print. -1 means print whole array.
    */

int printPaint(paint_t* pp, int i, int n); // question 2 of milestone 2
// question 1 milestone 2
    /*
    purpose: 
        prints paints within an array in a formatted way
    input:
    pp
        pointer pointing to an array of paint structures
    n:
        the size of pp
    i
        index of the array to print. -1 means print whole array.
    */

paint_t* getPaintValue(paint_t*, int, char*, gValue_t, int*);
/***
get paint value - 
    purpose: inputs type (enum) of value to look for as well as string to look for, code will look through
        the pp array of paints and look for the correlating value in the column given type
        
    input:
        pp:
            pointer to loaded array of paint data
        npp
            number of elements within the paint data array
        name:
            name that the code is looking to match within the array
        getType:
            enumeration of ciName, marketingName, manufacturer
        nspp:
            pointer to the number of elements found that contain the same value as name
    ***/

int printPaintHelper(paint_t* pp, int j);
/* 
    purpose: helper function for printPaint
    input: pp, a paint_t struct, and j, the index that is being printed
    output: 1 if error occured 0 if good.
 */

int printPigmentHelper(pigment_t* pp, int j);
/* 
    purpose: helper function for printPigment
    input: pp, a paint_t struct, and j, the index that is being printed
    output: 1 if error occured 0 if good.
 */


int getPaintRangeHelper(gRange_t getType, float* actmin, float* actmax, float rmin, float rmax);
/* 
    purpose: helper function for getPaintRange that executes a switch statement to get min and max values
    input: enumeration getType, a pointer to actmin and actmax, and rmin and rmax, floats used for
    the calculation
    output: modified actmin and actmax values, return 0 or 1 based on success or failure.
*/

int getPaintRangeValueHelper (gRange_t getType, paint_t* pp, int i, int* value);
/* 
    purpose: helper function for getPaintRange that executes a switch statement to get values for v
    alidity checking
    input: enumeration getType, a pointer to pp, an array of paint_t structs, integer i for indexing,
    and a pointer to int value, the value we are looking for
    output: modified value, returns 0 or 1 based on success or failure.
*/


int getPaintValueHelperCopy(paint_t* spa, paint_t* pp, int* nspp, int i);
/* 
    purpose: helper function for getPaintValue that copies data from a subarray spa to the main array
    pp
    input: emain array pp, subarray spa, a pointer to an integer nspp representing the number of
    entries, and i, which is the index of the paint_t struct being copied from the pp array to the spa 
    array
    output: spa has a paint_t structure copied into it. 0 or 1 is returned based on success or failure.
*/

// question 1 milestone 3
paint_t* getPaintHue(paint_t* pp, int* n, colour_t colour);
/*
    purpose: given a color, return a subarray of the main paint array which contains all colours
    specified
    input: pp, a pointer to the paint array with data loaded from paints.dat
    n a pointer to the number of paint structs in pp
    colour: an enumeration type which is given by the user based on the colour they want to input
*/

int getPaintHueSwitchHelper(colour_t colour, int* hue_range_low, int* hue_range_high);
    /*
purpose: helper function for getPaintHue. takes an enumerated colour and modified hue_range low and high
so that they have the range for where that colour is found
input: colour, a enum type, and a pointer to hue_range_low and high which will store the range of
hueAngles at which the colour is found
return: 1 or 0 based on success or failure, hue_range ints are modified.
*/

void printMenu(char* paletteType, char* paletteProperty);
/*
    Prints out the main menu of the program.
*/

void help(void);
/* 
    prints the help menu in the main program menu
*/

int paletteTypeHelper(char* paletteType);
/*
    Helper function in paintProgram.c for setting the paletteType
*/

int palettePropertyHelper(char* paletteProperty);
/*
    Helper function in paintProgram.c for setting the paletteProperty
*/

paint_t* getPalette (paint_t* pp, int* n, char* type, char* properties);
/***
get palette - 
    Purpose: depending on given palette type (type), palette color(type), property(properties) and property value(properties),
        function will return a pallet of all colours that fit within specified pallet pattern based on the inputted palette color, 
        only containing the inputted value of specified property
    Input: 
        pp:
            a pointer to paint array containing paint_t structures for each paint in paint.dat 
        n:
            pointer to an integer of the number of paint_t structures within pp
        type:
            a character string with two values palette type and palette color
        properties:
            a character string with two values property type and property value
    Return: paint_t array containing a subarray of main paint array only containing the paints that are within desired color 
        ranges of the palette and contain desired properties
 */

 paint_t* paletteFullHelper(paint_t* pp, int* n, char* proptype, int propval);
 /***
    Purpose: creates a dynamic array to store sub array of values that fit the inputed property type and value
    Input:
        pp: 
            pointer to paint array containing paint_t structures for paints in paint.dat 
        n:
            pointer to an interger of size of pp array
        proptype:
            the type of property within paint_t structure that needs to be checked for correct value
        propval: 
            value that proptype needs to be in order for struct to be added to the subarray
    Return: subarray of structures that match propval 
  */

paint_t* paletteTriadHelper(paint_t* pp, int* n, char* color);
/***
    Purpose: if the pallet type is triad this function checks to see whcih of 4 groups of palettes the given
        colour is present within, once identified getPaintHue is called for each color in the pallet and 3
        sub arrays are formed, these subarrays are combined and returned
    Input:
        pp: 
            pointer to paint array containing paint_t structures for paints within paints.dat
        n: 
            pointer to size of pp array
        color:
            the color needed to determine which palette will be used 
    Return: subarray of structures with colors within the 3 colors in triad palette 
 */

 paint_t* paletteComplementaryHelper(paint_t* pp, int* n, char* color);
 /***
    Purpose: if the palette type is complementary colors, this function checks to see which of 6 pallets the 
        given colour is present in, once identified getPaintHue is called and 2 subarrays are formed for the 
        2 complementary colors in the pallet, subarrays are combines and returned 
    Input:
        pp:
            pointer to paint array containing paint_t structures for paints within paints.dat
        n: 
            pointer to size of pp array
        color:
            specifying colour to determine the palette
    Return: subarray of structures with colours within ranges of 2 colors in palette
  */

  paint_t* paletteSplitCompHelper(paint_t* pp, int* n, char* color);
  /***
    Purpose: if the palette type is split complementary colours, this function checks to see which of the 12 possible
        pallets the given color is present within, once identified getPainthue is called and 3 subarrays are formed
        for the colors presnet in palette, subarrays are combined and returned
    Input:
        pp:
            pointer to paint array containing paint_t structures for paints within paints.dat
        n:
            pointer to size of pp array
        color:
            specifying colour to determine the palette
    Return: subarray of structures containing colours that fit within ranges of 3 palette colors 
   */


