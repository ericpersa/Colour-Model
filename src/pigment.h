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
}

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
