typedef struct pigment_t {
    char ciName[50];        // Color Index
    char pigmentName[50];   // Pigment Name
    int value;              // J (Value)
    int abValue[2];         // aC, bC
    int chroma;             // Chroma
    int hueAngle;           // Hue Angle
    float huePurity;        // Hue Purity
    float abHp[2];          // aHP, bHP
} pigment_t;

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

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n);