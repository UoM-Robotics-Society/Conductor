#include <SPI.h>

//modified correctTiming() to work with crotchets rather than BeatDenom

//changed conductor to pin 13

//||---------------------||---------------------||
//||  Servo Positions    || Facial Expressions  ||
//||---------------------||---------------------||
//|| 0 - no change       || 0 - no change       ||
//|| 1 - centres head    || 1 - 'Smile'         ||
//|| 2 - nods (down)     || 2 - 'Tension'       ||
//|| 3 - nods (up)       || 3 - 'RaiseEyebrows' ||
//|| 4 - looks at snare  || 4 - 'Exclamation'   ||
//|| 5 - looks at cymbal || 5 - 'inquisitive'   ||
//|| 6 - pans full left  || 6 - 'Sad'           ||
//|| 7 - pans full right || 7 - 'Elevated'      ||
//|| 8 - tilts down      || 8 - 'Frown'         ||
//|| 9 - tilts up        || 9 - 'FrownBrows'    ||

//------------------------
// Information about songs for loading
//------------------------
const int MaxNumSongs = 4;  // Number of songs to be loaded
const int NumSongs = 4;     // Number of songs to be loaded
const int DrumMax = 3;      // Max number of robots used

const int Tune1Length = 128;
const int Tune1Tempo = 93;
const int Tune1BeatDenom = 4;

const int Tune2Length = 192;
const int Tune2Tempo = 110;
const int Tune2BeatDenom = 4;

const int Tune3Length = 640;
const int Tune3Tempo = 153;
const int Tune3BeatDenom = 4;

const int Tune4Length = 48;
const int Tune4Tempo = 153;
const int Tune4BeatDenom = 6; 

//----------
// SONG DATA
//----------

  // 1st line - snare, 2nd line - cymbal, 3rd line - bass 
  // Part1
const unsigned int Tune1[DrumMax][Tune1Length] PROGMEM = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; 

  // 1st line - head position, 2nd line - facial expression (see table) 
const unsigned int Tune1Head[2][Tune1Length] PROGMEM = { 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

  
  // Part2 
const unsigned int Tune2[DrumMax][Tune2Length] PROGMEM = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; 

const unsigned int Tune2Head[2][Tune2Length] PROGMEM = { 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


 // Part3 
const unsigned int Tune3[DrumMax][Tune3Length] PROGMEM = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,      0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,   1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,      0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,      1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}};                                      

const unsigned int Tune3Head[2][Tune3Length] PROGMEM = { 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,      1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,      1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

// Part 4
const unsigned int Tune4[DrumMax][Tune4Length] PROGMEM = {
  {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},
  {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},
  {1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0}};

const unsigned int Tune4Head[2][Tune4Length] PROGMEM = {
  {1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},  
  {2,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0}};

//------------------------
// OUTPUT DEFINITIONS
//------------------------
const int On_Button = 7;           // signal from conductor, set low with output pin (White Wire)
const int ledpin; // flash led
const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

//output pins for link to raspberry pi and arduino
const int piB0 = 45,piB1 = 43,piB2 = 41,piB3 = 39;
const int n0 = 9, n1 = 10, n2 = 11, n3 = 12;

//------------------------
// TIME CONSTANTS
//------------------------
const int drumTime = 30;        //solenoid 'on' time for drums (in ms)
const int bassOffset = 20;      //gives bass drum a head start
const int start_delay = 0;
const int long bootTime = 90000;     //delay to allow raspberry pi/supercollider to load before starting


//------------------------  
// Create program variables
//------------------------
volatile int On_Signal;    // Used to track conductor
unsigned int Load_Drum[DrumMax];
unsigned int Load_Head[2];
unsigned int Load_Timing;

int BeatCount = 0; // Used to index Tune array
int DrumCount = 0; // Used to index Tune array
int SongCount = 0;

int SR_Count = 0;

// Create array to store information about songs
int Tune_Info[MaxNumSongs][4];
 
// Timing check variables

unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;
long int Beat_Time;

unsigned long part_start_time = 0;
unsigned long part_tempo = 0;
unsigned long part_stop_time = 0;
float part_time = 0;
float parttempo_beats = 0;

volatile unsigned int Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt

//---------------------------------------------
// Global Variables for Pushbutton/Demo control
//---------------------------------------------
const int snareInput = 52;
const int bassInput = 50;
const int cymbalInput = 48;
const int playInput = 46;

const int DemoTempo = 110; //sets tempo of demo beat
double  writeTime = 50; //time taken (in us) to write to output pins
double  delayMS = 0;
double  delayUS = 0;
double  beatTime = 0;

const int Demo1Length = 96;
const int Demo1BeatDenom = 12;
const int Demo2Length = 96;
const int Demo2BeatDenom = 12;
const int Demo3Length = 96;
const int Demo3BeatDenom = 12;

  // 1st line - snare, 2nd line - cymbal, 3rd line - bass 
const int Demo1[3][Demo1Length] = {
  {1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}}; 

  // 1st line - head position, 2nd line - facial expression (see table) 
const int Demo1Head[2][Demo1Length] = { 
  {1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,4,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  2,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}};

const int Demo2[3][Demo2Length] = {
  {1,0,0,1,0,0,1,0,0,1,0,0,  1,0,0,0,0,0,1,1,1,1,1,1,  1,0,0,1,0,0,1,0,0,1,0,0,  1,0,0,0,0,0,1,1,1,1,1,1,  1,0,0,0,0,0,1,0,0,0,0,0,  1,0,0,1,0,0,0,0,0,1,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0}}; 
const int Demo2Head[2][Demo2Length] = { 
  {0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,1,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}};

const int Demo3[3][Demo3Length] = {
  {1,0,0,1,0,0,1,0,0,1,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,1,1,1,1,1,1,  1,0,0,0,0,0,1,0,0,0,0,0,  1,0,0,1,0,0,0,0,0,1,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,1,1,1,1,1,  1,0,0,1,0,0,1,0,0,1,0,0,  1,0,0,0,0,0,1,1,1,1,1,1,  1,0,0,0,0,0,1,0,0,0,0,0,  1,0,0,1,0,0,0,0,0,1,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,1,0,0,0,0,0,  1,0,0,1,0,0,0,0,0,1,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}}; 
const int Demo3Head[2][Demo3Length] = { 
  {0,0,0,0,0,0,0,0,0,0,0,0,  5,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0,0,0,0,0,  2,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,2,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,  1,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0}};


//------------------------
// Setup Function 
//------------------------
void setup() 
{
    // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1Tempo;
    Tune_Info[0][2] =  Tune1BeatDenom;
    Tune_Info[1][0] =  Tune2Length;
    Tune_Info[1][1] =  Tune2Tempo;
    Tune_Info[1][2] =  Tune2BeatDenom;
    Tune_Info[2][0] =  Tune3Length;
    Tune_Info[2][1] =  Tune3Tempo;
    Tune_Info[2][2] =  Tune3BeatDenom;
    Tune_Info[3][0] =  Tune4Length;
    Tune_Info[3][1] =  Tune4Tempo;
    Tune_Info[3][2] =  Tune4BeatDenom;
        
    // configure I/O pins
    pinMode(ledpin, OUTPUT);
    pinMode(On_Button, INPUT_PULLUP);
   
    digitalWrite(ledpin, LOW);
    digitalWrite(On_Button, HIGH);

    pinMode(SnarePin, OUTPUT);
    pinMode(BassPin, OUTPUT);
    pinMode(CymbalPin, OUTPUT);

    digitalWrite(SnarePin,LOW);
    digitalWrite(BassPin,LOW);
    digitalWrite(CymbalPin,LOW);
  
    pinMode(piB0,OUTPUT);
    pinMode(piB1,OUTPUT);
    pinMode(piB2,OUTPUT);
    pinMode(piB3,OUTPUT);
    pinMode(n0,OUTPUT);
    pinMode(n1,OUTPUT);
    pinMode(n2,OUTPUT);
    pinMode(n3,OUTPUT);

    digitalWrite(piB0,LOW);
    digitalWrite(piB1,LOW);
    digitalWrite(piB2,LOW);
    digitalWrite(piB3,LOW);
    digitalWrite(n0,LOW);
    digitalWrite(n1,LOW);
    digitalWrite(n2,LOW);
    digitalWrite(n3,LOW);

    pinMode(snareInput,INPUT_PULLUP);
    pinMode(bassInput,INPUT_PULLUP);
    pinMode(cymbalInput,INPUT_PULLUP);
    pinMode(playInput,INPUT_PULLUP);

    // Start USB Serial for monitoring
    Serial.begin(115200);   
    Serial.println("USB Working!");

    //centres head
    moveHead(1);
    
    delay(1000);
    
}


// --------------------------------------------------------------------------------------
//------------------------
//Loop Function
//------------------------
void loop() 
{
      
        for(SongCount = 0; SongCount < NumSongs; SongCount++)
        {                             
              On_Signal = 1;
              while (On_Signal > 0)
              {
                  //On_Signal = digitalRead(On_Button); // Wait for Graphene ON (LOW)
                  manualControl();
              }
              
             correctTiming(Tune_Info[SongCount][1],Tune_Info[SongCount][2]); 
    
              part_start_time = micros();
              delay(start_delay);
   
              Beat_Time = (1/(Tune_Info[SongCount][1]/60.0))/Tune_Info[SongCount][2]*1000000.0;
              Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
              Start_Beat_Timer(); // Start Timer 1
    
              for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
              {
                    // Load Song Beats
                    for (DrumCount=0; DrumCount < DrumMax; DrumCount++)
                    {  
                          if(SongCount == 0)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune1[DrumCount][BeatCount]);
                          }
                          if(SongCount == 1)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune2[DrumCount][BeatCount]);                                  
                          }
                          if(SongCount == 2)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune3[DrumCount][BeatCount]);
                          }
                          if(SongCount == 3)
                          {
                              Load_Drum[DrumCount] = pgm_read_byte(&Tune4[DrumCount][BeatCount]);
                          }
                    }

                    // Load Head/Face Movement
                    if(SongCount == 0)
                    { 
                        Load_Head[0] = pgm_read_byte(&Tune1Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune1Head[1][BeatCount]);
                    }
                    if(SongCount == 1)
                    {
                        Load_Head[0] = pgm_read_byte(&Tune2Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune2Head[1][BeatCount]);                                  
                    }
                    if(SongCount == 2)
                    {
                        Load_Head[0] = pgm_read_byte(&Tune3Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune3Head[1][BeatCount]);
                    }
                     if(SongCount == 3)
                    {
                        Load_Head[0] = pgm_read_byte(&Tune4Head[0][BeatCount]);
                        Load_Head[1] = pgm_read_byte(&Tune4Head[1][BeatCount]);
                    }
                    
                    Play_Beat();                                

                    moveHead(Load_Head[0]);
                    changeFace(Load_Head[1]);                                             
                        
                    while (Next_Beat < 1)
                    {
                      // Waitfor Beat Timer 
                    } 
                    Next_Beat = 0;
              }
    
              while (On_Signal < 1)
              {
                  On_Signal = digitalRead(On_Button); //  Wait for Graphene signal OFF (HIGH)
              }
              
              digitalWrite(ledpin,LOW); 
              part_stop_time = micros();
            
              // calculate tempo                                  
              part_time = (part_stop_time-part_start_time)/1000000.0; 
              part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][2])/part_time)*60.0;
           
        }
                   
}

// --------------------------------------------------------------------------------------

// Play drums functions

void Play_Beat() 
{
 
      if(Load_Drum[2] == 1)
      {
          digitalWrite(BassPin,HIGH);
      }

      delay(bassOffset);
      
      if(Load_Drum[0] == 1)
      {
          digitalWrite(SnarePin,HIGH);
      }
      if(Load_Drum[1] == 1)
      {
          digitalWrite(CymbalPin,HIGH);
      }
      
      delay(drumTime);

      if(Load_Drum[0] == 1)
      {
          digitalWrite(SnarePin,LOW);
      }
      if(Load_Drum[1] == 1)
      {
          digitalWrite(CymbalPin,LOW);
      }
      if(Load_Drum[2] == 1)
      {
          delay(bassOffset);
          digitalWrite(BassPin,LOW);
      }
}

//==============================
// Functions for Head and Face
//==============================

void  moveHead(int headInput)
{
    digitalWrite(n0,!bitRead(headInput,0));
    digitalWrite(n1,!bitRead(headInput,1));
    digitalWrite(n2,!bitRead(headInput,2));
    digitalWrite(n3,!bitRead(headInput,3)); 
}

void  changeFace(int faceInput)
{
    digitalWrite(piB0,bitRead(faceInput,0));
    digitalWrite(piB1,bitRead(faceInput,1));
    digitalWrite(piB2,bitRead(faceInput,2));
    digitalWrite(piB3,bitRead(faceInput,3)); 
}
  

//==============================
// Functions for interrupt timer
//==============================

void Start_Beat_Timer() 
{
  //Serial.println(Beat_Time);
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  TCNT1 = Timer1_Beat_Count;   // preload timer
  TCCR1B |= (1 << CS12);    // Sets 256 prescaler 16 uSec counts
  Timer1_Beat_Count = (65536 -(Beat_Time/16));   // preload timer 65536-(416666/16) = 39494
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = Timer1_Beat_Count;   // Reload timer1 with beacount
  Next_Beat= 1;
}

void  correctTiming(int tempoIn,int beatDenom){
    double offsetMS = (((60.0/((double)tempoIn)) * 1000.0) - 50);
    double offsetUS = (((offsetMS - (int)offsetMS) * 1000) - 50);
    delay((int)offsetMS);
    delayMicroseconds((int)offsetUS);    
}

//===================================
// Functions for Demo/Pushbutton mode
//===================================

void playDrums(int snare, int cymbal, int bass, double bigdelay, double smalldelay) 
{
    digitalWrite(BassPin,bass);
    delay(bassOffset);
    digitalWrite(SnarePin,snare);
    digitalWrite(CymbalPin,cymbal);
    delay(drumTime);
    digitalWrite(CymbalPin,LOW);
    digitalWrite(SnarePin,LOW);
    digitalWrite(BassPin,LOW);
    delay((int)bigdelay);
    delayMicroseconds((int)smalldelay);   
}

void manualControl(void){
  while(On_Signal = digitalRead(On_Button)){
      if(!digitalRead(playInput)){
          delay(100);
          if(!digitalRead(playInput)){ 
  
              digitalWrite(BassPin,LOW);
              digitalWrite(SnarePin,LOW);
              digitalWrite(CymbalPin,LOW);

//              calculates beat time in ms with remainder in us
              if((delayMS = (((60.0/((double)(Tune4Tempo * Tune4BeatDenom))) * 1000.0) - drumTime - bassOffset)) < 0)
                  delayMS = 0;
              if((delayUS = ((delayMS - ((int)delayMS)) * 1000.0) - writeTime) < 0)
                  delayUS = 0;
                  
const unsigned int Test[DrumMax][Tune4Length]  = {
  {1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1,1,1,   0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},
  {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0},
  {1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0,   1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0}};
  
              //plays song section
              for(int i = 0; i < Tune4Length; i++){
               //   moveHead(Tune4Head[0][i]);
               //   changeFace(Tune4Head[1][i]);                
                  playDrums(Test[0][i],Test[1][i],Test[2][i],delayMS,delayUS);
              }
      
//              //calculates beat time in ms with remainder in us
//              if((delayMS = (((60.0/((double)(DemoTempo * Demo1BeatDenom))) * 1000.0) - drumTime - bassOffset)) < 0)
//                  delayMS = 0;
//              if((delayUS = ((delayMS - ((int)delayMS)) * 1000.0) - writeTime) < 0)
//                  delayUS = 0;
//          
//              //plays song section
//              for(int i = 0; i < Demo1Length; i++){
//                  moveHead(Demo1Head[0][i]);
//                  changeFace(Demo1Head[1][i]);                
//                  playDrums(Demo1[0][i],Demo1[1][i],Demo1[2][i],delayMS,delayUS);
//              }
//          
//          
//              //Demo2
//              if((delayMS = (((60.0/((double)(DemoTempo * Demo2BeatDenom))) * 1000.0) - drumTime - bassOffset)) < 0)
//                  delayMS = 0;
//              if((delayUS = ((delayMS - ((int)delayMS)) * 1000.0) - writeTime) < 0)
//                  delayUS = 0;
//              for(int i = 0; i < Demo2Length; i++){
//                  moveHead(Demo2Head[0][i]);
//                  changeFace(Demo2Head[1][i]);                
//                  playDrums(Demo2[0][i],Demo2[1][i],Demo2[2][i],delayMS,delayUS);
//              }   
//          
//          
//              //Demo3
//              if((delayMS = (((60.0/((double)(DemoTempo * Demo3BeatDenom))) * 1000.0) - drumTime - bassOffset)) < 0)
//                  delayMS = 0;
//              if((delayUS = ((delayMS - ((int)delayMS)) * 1000.0) - writeTime) < 0)
//                  delayUS = 0;
//              for(int i = 0; i < Demo3Length; i++){
//                  moveHead(Demo3Head[0][i]);
//                  changeFace(Demo3Head[1][i]);                
//                  playDrums(Demo3[0][i],Demo3[1][i],Demo3[2][i],delayMS,delayUS);
//              } 
          }
      }
      else{
          digitalWrite(BassPin,!digitalRead(bassInput));
          digitalWrite(SnarePin,!digitalRead(snareInput));
          digitalWrite(CymbalPin,!digitalRead(cymbalInput));
      }
   }
}


