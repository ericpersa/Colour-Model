// function prototype for question 4. function will be used to load data into an array of pigment structures
// int loadPigmentData(char* filename, pigment_t* pArray, int* n);

struct pigment_t {
    float abHp[2];
    int hueAngle;
    int chroma;
    float huePurity;
    int abValue[2];
    int value;
    char* ciName;
    char* pigmentName;
}

typedef struct paint_t{
    char ciName[30];
    char marketingName[30];
    char manufacturer[30];
    int code;
    int transparency;
    int staining;
    int valueRange;
    int granulating;
    int blossom;
    int diffusion;
    int hueAngle;
    int hueShift;
    int lightfast;
}paint_t;

int loadPaintData( char* , paint_t* , int*);