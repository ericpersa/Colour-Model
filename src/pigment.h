typedef enum {
    HUE,
    VALUE,
    GRANULATING,
    TRANSPARENT,
    STAINING,
    BLOOM,
    LIGHTFAST
} gRange_t;

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

paint_t* getPaintValue(paint_t*, int, char*, gValue_t, int*);

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n);

paint_t* getPaintRange(paint_t* pp, int npp, float rmin, float rmax, gRange_t getType, int* nspp);

int printPigment(pigment_t* pp, int i, int n); // question 1 of milestone 2

int printPaint(paint_t* pp, int i, int n); // question 2 of milestone 2


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

