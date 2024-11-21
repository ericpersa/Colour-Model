# Colour-Model

#COMPILATION

# Milestone 1
To compile and run the project:
1. Ensure you have the necessary environment and dependencies installed:
    - A C compiler (e.g. GCC)
    - Make (to run make commands)

2. Change to the src directory

3. Compile using the following command
    make

4. To test everything is working properly, use the following command
    ./test_load

#VARIABLES

Source - https://handprint.com/HP/WCL/huepurity.html
##in pigments.dat
COLOR INDEX - generic C.I. name of the pigment (this is missing for convenience mixtures and unclassified mineral pigments)
PIGMENT NAME - common pigment name or marketing name
J - pigment location in the CIECAM color appearance space
C - CIECAM pigment chroma, defined as (aC2+bC2)0.5
aC -pigment location in the CIECAM color appearance space
bC - pigment location in the CIECAM color appearance space
HueAngle - CIECAM hue angle, defined as ARCTAN(bC/aC)
Hue Purity - CIECAM hue purity, the ratio between the pigment chroma
aHP - ab coordinates for pigment hue purity, scaled so that maximum possible hue purity equals 1.0
bHP - ab coordinates for pigment hue purity, scaled so that maximum possible hue purity equals 1.0

##in paints.dat
C.I.NAME
MARKETING NAME
Manufacturer
Code - manufacterer (char)
Tr - transparency (int)
St - staining 
VR - valueRange
Gr - granulating 
Bl - blossom
Df - Diffusion
HA - HueAngle
HS - HueShift
Lf - lightfast
