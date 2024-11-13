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
};