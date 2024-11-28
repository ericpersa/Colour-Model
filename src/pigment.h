// ID BOX: Eric Persa 3123945
// ID BOX : Jenna Leaw 3147578

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
