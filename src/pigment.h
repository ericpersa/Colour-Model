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
}paint_t;

typedef enum{ciName, marketingName, manufacturer}gValue_t;

paint_t* loadPaintData( char* , paint_t* , int*);

paint_t* (paint*, int, char*, gVlaue_t, int*);

pigment_t* loadPigmentData(char* filename, pigment_t* pArray, int* n);