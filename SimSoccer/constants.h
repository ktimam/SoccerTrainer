#ifndef CONSTANTS_H
#define CONSTANTS_H

const int PitchWidth = 26;
const int PitchLength = 52;

//Used for 2D rendering
//Maintain proportion between window and pitch width/height
//Maintain whole number rate between window and pitch
const double PitchWindowRate = 20;
const double WindowWidth  = PitchLength * PitchWindowRate;
const double WindowHeight = PitchWidth * PitchWindowRate;

#endif