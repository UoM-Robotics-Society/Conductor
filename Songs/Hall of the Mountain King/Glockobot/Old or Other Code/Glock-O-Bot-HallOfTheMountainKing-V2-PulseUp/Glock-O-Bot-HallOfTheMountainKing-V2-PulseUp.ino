#include <SPI.h>

// calibration done at 6V and T2 800, notes just striking
// All 30 notes now connected and working 22/06/2016
// Added volume 14/06/2016
// Split into 18 parts 23/07/2016


// #define Tune_Length for each part

#define Tune1_Length 121 
const long Part1_Bars = 8.5; // 8.5 - just over
#define Tune2_Length 185 
const long Part2_Bars = 12.5;  // 12.5
#define Tune3_Length 679 
const long Part3_Bars = 43.5; //43.5

#define Note_Max 1 // Max number of notes struck per beat = 4


const long int BeatTime_Part1 = 150000; // 1/16th beat time in uSec( 100bpm )
const long int BeatTime_Part2 = 125000; // 1/16th beat time in uSec( 120bpm )
const long int BeatTime_Part3 = 90909; // 1/16th beat time in uSec( 165bpm )

//const long int BeatTime_Part1 = 161290; // 1/16th beat time in uSec( 93bpm )
//const long int BeatTime_Part2 = 125000; // 1/16th beat time in uSec( 120bpm )
//const long int BeatTime_Part3 = 90909; // 1/16th beat time in uSec( 165bpm )


long int Beat_Time;

const int start_delay = 0;


const unsigned char Tune1[Note_Max][Tune1_Length] PROGMEM = {{95,0,0,0,90,0,0,0,83,0,0,0,90,0,0,0,95,0,0,0,90,0,0,0,83,0,0,0,90,0,0,0,95,0,0,0,90,0,0,0,83,0,0,0,90,0,0,0,86,0,0,0,93,0,0,0,86,0,0,0,93,0,0,0,90,0,92,0,94,0,95,0,97,0,94,0,97,0,0,0,98,0,94,0,98,0,0,0,97,0,94,0,97,0,0,0,90,0,92,0,94,0,95,0,97,0,94,0,97,0,0,0,98,0,94,0,98,0,0,0,97}};
const unsigned char Tune2[Note_Max][Tune2_Length] PROGMEM = {{83,0,85,0,86,0,88,0,90,0,86,0,90,0,0,0,89,0,85,0,89,0,0,0,88,0,84,0,88,0,0,0,83,0,85,0,86,0,88,0,90,0,86,0,90,0,95,0,93,0,90,0,86,0,90,0,93,0,0,0,0,0,0,0,90,0,92,0,94,0,95,0,97,0,94,0,97,0,0,0,98,0,94,0,98,0,0,0,97,0,94,0,97,0,0,0,90,0,92,0,94,0,95,0,97,0,94,0,97,0,0,0,98,0,94,0,98,0,0,0,97,0,0,0,0,0,0,0,83,0,85,0,86,0,88,0,90,0,86,0,90,0,0,0,89,0,85,0,89,0,0,0,88,0,84,0,88,0,0,0,83,0,85,0,86,0,88,0,90,0,86,0,90,0,95,0,93,0,90,0,86,0,90,0,93}};
const unsigned char Tune3[Note_Max][Tune3_Length] PROGMEM = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,83,83,85,85,86,86,88,88,90,90,86,86,90,90,90,90,89,89,85,85,89,89,89,89,88,88,84,84,88,88,88,88,83,83,85,85,86,86,88,88,90,90,86,86,90,90,95,95,93,93,90,90,86,86,90,90,93,93,93,93,93,93,93,93,83,83,85,85,86,86,88,88,90,90,86,86,90,90,90,90,89,89,85,85,89,89,89,89,88,88,84,84,88,88,88,88,83,83,85,85,86,86,88,88,90,90,86,86,90,90,95,95,93,93,90,90,86,86,90,90,93,93,93,93,93,93,93,93,78,78,80,80,82,82,83,83,85,85,82,82,85,85,85,85,86,86,82,82,86,86,86,86,85,85,82,82,85,85,85,85,78,78,80,80,82,82,83,83,85,85,82,82,85,85,85,85,86,86,82,82,86,86,86,86,85,85,85,85,85,85,85,85,78,78,80,80,82,82,83,83,85,85,82,82,85,85,85,85,87,87,82,82,87,87,87,87,85,85,82,82,85,85,85,85,78,78,80,80,82,82,83,83,85,85,82,82,85,85,85,85,87,87,82,82,87,87,87,87,85,85,85,85,85,85,85,85,83,83,85,85,86,86,88,88,90,90,86,86,90,90,90,90,89,89,85,85,89,89,89,89,88,88,84,84,88,88,88,88,83,83,85,85,86,86,88,88,90,90,86,86,90,90,95,95,93,93,90,90,86,86,90,90,93,93,93,93,93,93,93,93,83,83,85,85,86,86,88,88,90,90,86,86,90,90,90,90,89,89,85,85,89,89,89,89,88,88,84,84,88,88,88,88,83,83,85,85,86,86,88,88,90,90,86,86,90,90,95,95,90,90,86,86,90,90,95,95,83,83,83,83,83,83,83,83,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,71,0,73,0,74,0,76,0,78,0,76,0,78,0,83,0,82,0,78,0,82,0,85,0,83,0,0,0,0,0,0,0,0,0,0,0,86,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,86,85,86,0,0,0,0,0,0,0,0,0,71,0,73,0,74,0,76,0,78,0,76,0,78,0,83,0,82,0,78,0,82,0,85,0,83,0,0,0,0,0,0,0,0,0,0,0,86,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,86,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,86,85,86,0,86,85,86,0,86,85,86,0,86,85,86,0,86,85,86,0,86,85,86,0,86,85,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,85,86}};

  

int Beat_Count = 0; // Used to index Tune array
int Note_Count = 0; // Used to index Tune array
int Graphene_Signal = 0; // Used to track conductor


// define I/O pins
const int ledpin = 13; // flash led
const int SR_Latch_Pin = 53; // latch shift register
const int SR_Reset_Pin = 41; // reset shift register
const int Ext_Voltage_On = 48; // checks fo external +5v
//const int Graphene_Sen_P = 23; // singnal from graphine conductor, read for status low indicates start
const int Graphene_Sen_P = 5; // singnal from graphine conductor, read for status low indicates start, used for tests on Uno
const int Graphene_Sen_N = 25; // singnal from graphine conductor, set low with output pin

// define Shift Register Length
const int SR_Length    = 30; // Adjust to match instrument

// define key positions in sfift register

const int SR_Note_G0   = 29; //79
const int SR_Note_A1   = 28; //81
const int SR_Note_B1   = 27; //83
const int SR_Note_C1   = 26; //84
const int SR_Note_D1   = 25; //86
const int SR_Note_E1   = 24; //88
const int SR_Note_F1   = 23; //89
const int SR_Note_G1   = 22; //91
const int SR_Note_A2   = 21; //93
const int SR_Note_B2   = 20; //95
const int SR_Note_C2   = 19; //96
const int SR_Note_D2   = 18; //98
const int SR_Note_E2   = 17; //100
const int SR_Note_F2   = 16; //101
const int SR_Note_G2   = 15; //103
const int SR_Note_A3   = 14; //105
const int SR_Note_B3   = 13; //107
const int SR_Note_C3   = 12; //108
const int SR_Note_A3s  = 11; //106
const int SR_Note_G2s  = 10; //104
const int SR_Note_F2s  =  9; //102
const int SR_Note_D2s  =  8; //99
const int SR_Note_C2s  =  7; //97
const int SR_Note_A2s  =  6; //94
const int SR_Note_G1s  =  5; //92
const int SR_Note_F1s  =  4; //90
const int SR_Note_D1s  =  3; //87
const int SR_Note_C1s  =  2; //85
const int SR_Note_A1s  =  1; //82
const int SR_Note_G0s  =  0; //80

// Timing check variables

unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;

unsigned long part1_start_time = 0;
unsigned long part1_tempo = 0;
unsigned long part1_stop_time = 0;
unsigned long part2_start_time = 0;
unsigned long part2_tempo = 0;
unsigned long part2_stop_time = 0;
unsigned long part3_start_time = 0;
unsigned long part3_tempo = 0;
unsigned long part3_stop_time = 0;

unsigned long parttempo1_beats = 0;
unsigned long parttempo2_beats = 0;
unsigned long parttempo3_beats = 0;

float part1_time = 0;
float part2_time = 0;
float part3_time = 0;

// Voltage set to 6.5V use Time_2 between 1000 - 2000 for vol 0-100

const int Solenoid_On_Time_1 = 1000; // Pulse width in uSec Fixed
const int Solenoid_Off_Time = 1000; // Pulse width in uSec Fixed
int Solenoid_On_Time_2 = 1000; // Pulse width in uSec Variable

// Shift Register Output patterns

byte      Solenoid_ON  = B00000010;
byte      LED_ON       = B00000100;
byte      All_OFF      = B00000000;
byte      SR_Note_Data[SR_Length];
byte      SR_LED_Data[SR_Length]; 

unsigned char    Load_Note;

volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt CHANGED


void setup() {
  
  // configure I/O pins
  pinMode(ledpin, OUTPUT);
  pinMode(SR_Latch_Pin, OUTPUT);
  pinMode(SR_Reset_Pin, OUTPUT);
  pinMode(Graphene_Sen_N, OUTPUT);
  pinMode(Graphene_Sen_P, INPUT);
    
  digitalWrite(ledpin, LOW);
  digitalWrite(SR_Latch_Pin, LOW);
  digitalWrite(SR_Reset_Pin, LOW);
  digitalWrite(Graphene_Sen_N, LOW);
  //digitalWrite(Graphene_Sen_P, LOW);
  
  // start the SPI library:
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
  Clear_SR_Note_Data();
  Clear_SR_LED_Data();
  Reset_SR();

  Serial.begin(9600);

  Beat_Time = BeatTime_Part1;
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo ADDED FIXED First Time THROUGH ISSUES !!!
  while (Next_Beat < 1)
        {
      //           Waitfor Beat Timer 
        }
        
  }


// --------------------------------------------------------------------------------------

void loop() 
  {

// Part 1 .......................
  Serial.println("Part 1");
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 0;
  Solenoid_On_Time_2 = 1200;
  
  while (Graphene_Signal < 1)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 0; // debounce 1msec
  Serial.println("1");
  part1_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal < 1)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  Serial.println("2");
  delay(start_delay);      
  
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Beat_Time = BeatTime_Part1;
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune1_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune1[Note_Count][Beat_Count]);
              if (Load_Note >= 149)
                {
                     // Volume 5
                     Solenoid_On_Time_2 = 1300;
                     Load_Note = Load_Note -70;
                }
              else if (Load_Note >= 114)
                {
                    // Volume 4
                    Solenoid_On_Time_2 = 1200;
                    Load_Note = Load_Note -35;
                }
              else if (Load_Note >= 79)
                {
                    // Volume 3
                    Solenoid_On_Time_2 = 1100; // use to cal at lowest level , move to 1100 for playing
                    Load_Note = Load_Note -0;
                }
              else if (Load_Note >= 44)
                {
                    // Volume 2
                    Solenoid_On_Time_2 = 1000;
                    Load_Note = Load_Note +35;
                }
              else 
                {
                    // Volume 1
                    Solenoid_On_Time_2 = 900;
                    Load_Note = Load_Note +70;
                }
              Load_Beat(Load_Note);
              
              Play_Beat();
            }
      Flash_LED_ON();   

      Clear_SR_Note_Data();
      
      while (Next_Beat < 1)
        {
      //           Waitfor Beat Timer 
        }
      
      // Turn OFF LEDs
       Reset_SR();
       Next_Beat = 0;
       
      }
      
   digitalWrite(ledpin,HIGH); 
    
   while (Graphene_Signal < 1)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
        }
  
  part1_stop_time = micros(); 
  

 // Part 2 .......................
  Serial.println("Part 2");
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part2_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Beat_Time = BeatTime_Part2;
  Start_Beat_Timer(); // Start Timer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune2_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune2[Note_Count][Beat_Count]);
              if (Load_Note >= 149)
                {
                     // Volume 5
                     Solenoid_On_Time_2 = 1300;
                     Load_Note = Load_Note -70;
                }
              else if (Load_Note >= 114)
                {
                    // Volume 4
                    Solenoid_On_Time_2 = 1200;
                    Load_Note = Load_Note -35;
                }
              else if (Load_Note >= 79)
                {
                    // Volume 3
                    Solenoid_On_Time_2 = 1100; // use to cal at lowest level , move to 1100 for playing
                    Load_Note = Load_Note -0;
                }
              else if (Load_Note >= 44)
                {
                    // Volume 2
                    Solenoid_On_Time_2 = 1000;
                    Load_Note = Load_Note +35;
                }
              else 
                {
                    // Volume 1
                    Solenoid_On_Time_2 = 900;
                    Load_Note = Load_Note +70;
                }
              Load_Beat(Load_Note);
              
              Play_Beat();
            }
      Flash_LED_ON();   

      Clear_SR_Note_Data();
      
      while (Next_Beat < 1)
        {
      //           Waitfor Beat Timer 
        }
      
      // Turn OFF LEDs
       Reset_SR();
       Next_Beat = 0;
       
      }
      
   digitalWrite(ledpin,HIGH); 
    
   while (Graphene_Signal < 1)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
        }
  
  part2_stop_time = micros(); 


  // Part 3 .......................
  Serial.println("Part 3");
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part3_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Beat_Time = BeatTime_Part3;
  Start_Beat_Timer(); // Start Timer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune3_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune3[Note_Count][Beat_Count]);
              if (Load_Note >= 149)
                {
                     // Volume 5
                     Solenoid_On_Time_2 = 1300;
                     Load_Note = Load_Note -70;
                }
              else if (Load_Note >= 114)
                {
                    // Volume 4
                    Solenoid_On_Time_2 = 1200;
                    Load_Note = Load_Note -35;
                }
              else if (Load_Note >= 79)
                {
                    // Volume 3
                    Solenoid_On_Time_2 = 1100; // use to cal at lowest level , move to 1100 for playing
                    Load_Note = Load_Note -0;
                }
              else if (Load_Note >= 44)
                {
                    // Volume 2
                    Solenoid_On_Time_2 = 1000;
                    Load_Note = Load_Note +35;
                }
              else 
                {
                    // Volume 1
                    Solenoid_On_Time_2 = 900;
                    Load_Note = Load_Note +70;
                }
              Load_Beat(Load_Note);
              
              Play_Beat();
            }
      Flash_LED_ON();   

      Clear_SR_Note_Data();
      
      while (Next_Beat < 1)
        {
      //           Waitfor Beat Timer 
        }
      
      // Turn OFF LEDs
       Reset_SR();
       Next_Beat = 0;
       
      }
      
   digitalWrite(ledpin,HIGH); 
    
   while (Graphene_Signal < 1)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
        }
  
  part3_stop_time = micros(); 


//-----------------
        


// calculate tempo's - use this with graphene
//   part1_tempo = ((min_us*Part1_Bars)/(part2_start_time-part1_start_time));  
    
    
// calculate tempo's - use this for code check
   part1_tempo = ((min_us*Part1_Bars)/(part1_stop_time-part1_start_time));
   part2_tempo = ((min_us*Part2_Bars)/(part2_stop_time-part2_start_time));
   part3_tempo = ((min_us*Part3_Bars)/(part3_stop_time-part3_start_time));  

   part1_time = (part1_stop_time-part1_start_time)/1000000.0; 
   part2_time = (part2_stop_time-part2_start_time)/1000000.0;
   part3_time = (part3_stop_time-part3_start_time)/1000000.0;
   
   parttempo1_beats = Tune1_Length/part1_time*60; 
   parttempo2_beats = Tune2_Length/part2_time*60; 
   parttempo3_beats = Tune3_Length/part3_time*60;      

// display results   
  Serial.print("Shift Register Load Time: ");  
  Serial.println(sr_stop_time-sr_start_time);
  
  Serial.print("Part 1 Time (S): ");
  Serial.println(part1_time);
  Serial.print("Part 1 Tempo (Bars): ");
  Serial.println(part1_tempo);
  Serial.print("Part 1 Tempo (Beats): ");
  Serial.println(parttempo1_beats);
  Serial.print("   Dwell: ");  
//  Serial.println((part2_start_time-part1_stop_time)/1000);
  Serial.println();

  Serial.print("Part 2 Time (S): ");
  Serial.println(part2_time);
  Serial.print("Part 2 Tempo (Bars): ");
  Serial.println(part2_tempo);
  Serial.print("Part 2 Tempo (Beats): ");
  Serial.println(parttempo2_beats);
  Serial.print("   Dwell: ");  
//  Serial.println((part2_start_time-part1_stop_time)/1000);
  Serial.println();

  Serial.print("Part 3 Time (S): ");
  Serial.println(part3_time);
  Serial.print("Part 3 Tempo (Bars): ");
  Serial.println(part3_tempo);
  Serial.print("Part 3 Tempo (Beats): ");
  Serial.println(parttempo3_beats);
  Serial.print("   Dwell: ");  
//  Serial.println((part2_start_time-part1_stop_time)/1000);
  Serial.println();
  
  Serial.println("-----------------------------------------------------------------");
  }


// --------------------------------------------------------------------------------------

void Clear_SR_Note_Data() {

  //function body
  for ( int i=0; i < SR_Length; i++){
  SR_Note_Data[i] = All_OFF;                  // clear all bits
  }
}
  
void Clear_SR_LED_Data() {

  //function body
  for ( int i=0; i < SR_Length; i++){
  SR_LED_Data[i] = All_OFF;                  // clear all bits
  }
}

void Load_Beat(unsigned char Note) {

// Load upto 4 notes for single beat

switch (Note) {
    case 00:
      // No Note
      break;
    case 79:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 300; // not vol calibration
      SR_Note_Data[SR_Note_G0] = Solenoid_ON;
      SR_LED_Data[SR_Note_G0] = LED_ON;
      break;
    case 80:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 0; // #not vol calibration
      SR_Note_Data[SR_Note_G0s] = Solenoid_ON;
      SR_LED_Data[SR_Note_G0s] = LED_ON;
      break;
    case 81:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 220; // not vol calibration
      SR_Note_Data[SR_Note_A1] = Solenoid_ON;
      SR_LED_Data[SR_Note_A1] = LED_ON;
      break;
    case 82:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 120; // #not vol calibration
      SR_Note_Data[SR_Note_A1s] = Solenoid_ON;
      SR_LED_Data[SR_Note_A1s] = LED_ON;
      break;
    case 83:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 300; // not vol calibration
      SR_Note_Data[SR_Note_B1] = Solenoid_ON;
      SR_LED_Data[SR_Note_B1] = LED_ON;
      break;
    case 84:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 220; // not vol calibration
      SR_Note_Data[SR_Note_C1] = Solenoid_ON;
      SR_LED_Data[SR_Note_C1] = LED_ON;
      break;
    case 85:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 100; // #not vol calibration
      SR_Note_Data[SR_Note_C1s] = Solenoid_ON;
      SR_LED_Data[SR_Note_C1s] = LED_ON;
      break;
    case 86:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 250; // not vol calibration
      SR_Note_Data[SR_Note_D1] = Solenoid_ON;
      SR_LED_Data[SR_Note_D1] = LED_ON;
      break;
    case 87:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 100; // #not vol calibration
      SR_Note_Data[SR_Note_D1s] = Solenoid_ON;
      SR_LED_Data[SR_Note_D1s] = LED_ON;
      break;
    case 88:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 200; // not vol calibration
      SR_Note_Data[SR_Note_E1] = Solenoid_ON;
      SR_LED_Data[SR_Note_E1] = LED_ON;
      break;
    case 89:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 200; // not vol calibration
      SR_Note_Data[SR_Note_F1] = Solenoid_ON;
      SR_LED_Data[SR_Note_F1] = LED_ON;
      break;
    case 90:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 150; // #not vol calibration
      SR_Note_Data[SR_Note_F1s] = Solenoid_ON;
      SR_LED_Data[SR_Note_F1s] = LED_ON;
      break;
    case 91:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 250; // not vol calibration
      SR_Note_Data[SR_Note_G1] = Solenoid_ON;
      SR_LED_Data[SR_Note_G1] = LED_ON;
      break;
    case 92:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 50; // #not vol calibration
      SR_Note_Data[SR_Note_G1s] = Solenoid_ON;
      SR_LED_Data[SR_Note_G1s] = LED_ON;
      break;
    case 93:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 350; // not vol calibration
      SR_Note_Data[SR_Note_A2] = Solenoid_ON;
      SR_LED_Data[SR_Note_A2] = LED_ON;
      break;
    case 94:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 50; // #not vol calibration
      SR_Note_Data[SR_Note_A2s] = Solenoid_ON;
      SR_LED_Data[SR_Note_A2s] = LED_ON;
      break;
    case 95:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 400; // not vol calibration
      SR_Note_Data[SR_Note_B2] = Solenoid_ON;
      SR_LED_Data[SR_Note_B2] = LED_ON;
      break;
    case 96:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 300; // not vol calibration
      SR_Note_Data[SR_Note_C2] = Solenoid_ON;
      SR_LED_Data[SR_Note_C2] = LED_ON;
      break;
    case 97:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 0; // #not vol calibration
      SR_Note_Data[SR_Note_C2s] = Solenoid_ON;
      SR_LED_Data[SR_Note_C2s] = LED_ON;
      break;
    case 98:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 300; // not vol calibration
      SR_Note_Data[SR_Note_D2] = Solenoid_ON;
      SR_LED_Data[SR_Note_D2] = LED_ON;
      break;
    case 99:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 50; // #not vol calibration
      SR_Note_Data[SR_Note_D2s] = Solenoid_ON;
      SR_LED_Data[SR_Note_D2s] = LED_ON;
      break;
    case 100:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 270; // not vol calibration
      SR_Note_Data[SR_Note_E2] = Solenoid_ON;
      SR_LED_Data[SR_Note_E2] = LED_ON;
      break;
    case 101:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 420; // not vol calibration
      SR_Note_Data[SR_Note_F2] = Solenoid_ON;
      SR_LED_Data[SR_Note_F2] = LED_ON;
      break;
    case 102:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 50; // #not vol calibration
      SR_Note_Data[SR_Note_F2s] = Solenoid_ON;
      SR_LED_Data[SR_Note_F2s] = LED_ON;
      break;
    case 103:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 350; // not vol calibration
      SR_Note_Data[SR_Note_G2] = Solenoid_ON;
      SR_LED_Data[SR_Note_G2] = LED_ON;
      break;
    case 104:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 - 220; // #not vol calibration
      SR_Note_Data[SR_Note_G2s] = Solenoid_ON;
      SR_LED_Data[SR_Note_G2s] = LED_ON;
      break;
    case 105:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 250; // not vol calibration
      SR_Note_Data[SR_Note_A3] = Solenoid_ON;
      SR_LED_Data[SR_Note_A3] = LED_ON;
      break;
    case 106:
      Solenoid_On_Time_2 = Solenoid_On_Time_2 + 50; // #not vol calibration
      SR_Note_Data[SR_Note_A3s] = Solenoid_ON;
      SR_LED_Data[SR_Note_A3s] = LED_ON;
      break;
//    case 107:
//      SR_Note_Data[SR_Note_B3] = Solenoid_ON;
//      SR_LED_Data[SR_Note_B3] = LED_ON;
//      break;
//    case 108:
//      SR_Note_Data[SR_Note_C3] = Solenoid_ON;
//      SR_LED_Data[SR_Note_C3] = LED_ON;
//      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }

}

void Flash_LED_ON() {

// function body

    digitalWrite(SR_Reset_Pin, HIGH);
    Load_LED_SR();
    Clear_SR_LED_Data();

}


void Load_LED_SR() {

  //function body
  digitalWrite(SR_Latch_Pin, LOW);
  for ( int i=0; i < SR_Length; i++){
  SPI.transfer(SR_LED_Data[i]);                  // clear all bits
  }
  Set_SR();
}

void Play_Beat() {

// sends two timed pulses to the selected solenoid

    //First Pulse
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_Notes_SR();
    delayMicroseconds(Solenoid_On_Time_1);
    Reset_SR();
    delayMicroseconds(Solenoid_Off_Time);

    //Second Pulse
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_Notes_SR();
    delayMicroseconds(Solenoid_On_Time_2);
    Reset_SR();
    Clear_SR_Note_Data();

}

void Reset_SR() 
    {
    digitalWrite(SR_Reset_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(SR_Latch_Pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(SR_Latch_Pin, LOW);
//    digitalWrite(SR_Reset_Pin, HIGH);
    }

void Set_SR() 
    {
    digitalWrite(SR_Latch_Pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(SR_Latch_Pin, LOW);
    }
  

void Load_Notes_SR() {

  //function body
  sr_start_time=micros();
  digitalWrite(SR_Latch_Pin, LOW);
  for ( int i=0; i < SR_Length; i++)
  {
    SPI.transfer(SR_Note_Data[i]);           
  }
  Set_SR();
  sr_stop_time=micros();
}

void Start_Beat_Timer() {

  Serial.print("Beat Time: ");
  Serial.println(Beat_Time);
  
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

