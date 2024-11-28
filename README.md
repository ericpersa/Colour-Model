# Colour-Model

# COMPILATION

# Milestone 2
To compile and run the project:
1. Ensure you have the necessary environment and dependencies installed:
    - A C compiler (e.g. GCC)
    - Make (to run make commands)

2.  Compile using the following command
    make 

3. Change to the bin directory

4. To test everything is working properly, use the following command(s)
    ./test_load
    ./test_value
    ./test_range


# Colour Wheel Decisions
345° - 15° - Red:Orange
15° - 45° - Orange
45° - 75° - Yellow Orange
75° - 105° - Yellow
105° - 135° - Yellow Green
135° - 165° - Green
165° - 195° - Blue Green
195° - 225° - Blue
225° - 255° - Blue Violet
255° - 285° - Violet
285° - 315° - Red Violet
315° - 345° - Red


# VARIABLES

Source - https://handprint.com/HP/WCL/huepurity.html
## in pigments.dat
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

Source - https://www.handprint.com/HP/WCL/pigmt8.html 
## in paints.dat
C.I.NAME - colour index name/number of paint 
MARKETING NAME - name given to colour from the paint manufacterer
Manufacturer - company that produces and sells the paint
Code - manufacterer - an identifying number used by the manufacterer to differentiate products
Tr - transparency - the amount of masking that occurs when paint is swatched overtop of a different coloured surface
St - staining - the amount of lifting of paint particles from a surface that occurs after paint has dried 
VR - valueRange - The lightness or darkness of the watercolor paint, as painted full strength on white watercolor paper
Gr - granulating - visible or tractile texture caused by particle seperation after the paint has dried 
Bl - blossom - amount of paint particles redissolved and moved by water after drying, adjustibility of particles
Df - Diffusion - amount of movement by paint when swatched onto a pre-moistened surface 
HA - HueAngle - a paint's masstone hue, as measured by the CIELAB a*b* plane
HS - HueShift - shift in the paint's hue, undertone hue - masstone hue
Lf - lightfast - measurement of the amount of discolouration that occurs when exposed to high intensity light for period of time
