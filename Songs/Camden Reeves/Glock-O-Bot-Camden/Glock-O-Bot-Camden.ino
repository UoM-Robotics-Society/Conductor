#include <SPI.h>

// calibration done at 6V and T2 800, notes just striking
// All 30 notes now connected and working 22/06/2016
// Added volume 14/06/2016
// Split into 18 parts 23/07/2016
// Final version for Manchester Cenral Performance 24-07-2016
// Transitions between 14-15 and 15-16 known issue ( delay lowed to 60mSec for these transitions)


// #define Tune_Length for each part (Bar Length is Grahene spacing)



#define Tune1_Length 1 
const int Part1_Bars = 1;
#define Tune2_Length 1
const int Part2_Bars = 1;
#define Tune3_Length 1
const int Part3_Bars = 1;
#define Tune4_Length 1
const int Part4_Bars = 1;
#define Tune5_Length 1
const int Part5_Bars = 1;
#define Tune6_Length 1 
const int Part6_Bars = 1;
#define Tune7_Length 1
const int Part7_Bars = 1;
#define Tune8_Length 1 
const int Part8_Bars = 1;
#define Tune9_Length 1 
const int Part9_Bars = 1;
#define Tune10_Length 1 
const int Part10_Bars = 1;

#define Note_Max 4 // Max number of notes struck per beat = 4
#define Tempo 144 // Beats per minute

const long Beat_Time = 57692; // 1/8th beat time in uSec( 130bpm )

const int start_delay = 120; // delay after graphene signal in msec


const unsigned char Tune1[Note_Max][Tune1_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune2[Note_Max][Tune2_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune3[Note_Max][Tune3_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune4[Note_Max][Tune4_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune5[Note_Max][Tune5_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune6[Note_Max][Tune6_Length] PROGMEM = {{84},{0},{0},{0}};
const unsigned char Tune7[Note_Max][Tune7_Length] PROGMEM ={{84},{0},{0},{0}};
const unsigned char Tune8[Note_Max][Tune8_Length] PROGMEM ={{84},{0},{0},{0}};
const unsigned char Tune9[Note_Max][Tune9_Length] PROGMEM ={{84},{0},{0},{0}};
const unsigned char Tune10[Note_Max][Tune10_Length] PROGMEM ={{84},{0},{0},{0}};


int Beat_Count = 0; // Used to index Tune array
int Note_Count = 0; // Used to index Tune array
int Graphene_Signal = 0; // Used to track conductor


// define I/O pins
const int ledpin = 13; // flash led
const int SR_Latch_Pin = 53; // latch shift register
const int SR_Reset_Pin = 41; // reset shift register
const int Ext_Voltage_On = 48; // checks fo external +5v
const int Graphene_Sen_P = 23; // singnal from graphine conductor, read for status low indicates star
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

unsigned long part1_start_time= 0;
unsigned long part1_tempo= 0;
unsigned long part1_stop_time= 0;
unsigned long part2_start_time= 0;
unsigned long part2_tempo= 0;
unsigned long part2_stop_time= 0;
unsigned long part3_start_time= 0;
unsigned long part3_tempo= 0;
unsigned long part3_stop_time= 0;
unsigned long part4_start_time= 0;
unsigned long part4_tempo= 0;
unsigned long part4_stop_time= 0;
unsigned long part5_start_time= 0;
unsigned long part5_tempo= 0;
unsigned long part5_stop_time= 0;
unsigned long part6_start_time= 0;
unsigned long part6_tempo= 0;
unsigned long part6_stop_time= 0;
unsigned long part7_start_time= 0;
unsigned long part7_tempo= 0;
unsigned long part7_stop_time= 0;
unsigned long part8_start_time= 0;
unsigned long part8_tempo= 0;
unsigned long part8_stop_time= 0;
unsigned long part9_start_time= 0;
unsigned long part9_tempo= 0;
unsigned long part9_stop_time= 0;
unsigned long part10_start_time= 0;
unsigned long part10_tempo= 0;
unsigned long part10_stop_time= 0;
unsigned long part11_start_time= 0;


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

volatile unsigned int Timer1_Beat_Count =0; // Used to set Timmer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timmer 1 Interrupt CHANGED


void setup() {
  
  // configure I/O pins
  pinMode(ledpin, OUTPUT);
  pinMode(SR_Latch_Pin, OUTPUT);
  pinMode(SR_Reset_Pin, OUTPUT);
  pinMode(Graphene_Sen_N, OUTPUT);
  pinMode(Graphene_Sen_P, INPUT_PULLUP);
    
  digitalWrite(ledpin, LOW);
  digitalWrite(SR_Latch_Pin, LOW);
  digitalWrite(SR_Reset_Pin, LOW);
  digitalWrite(Graphene_Sen_N, LOW);
  digitalWrite(Graphene_Sen_P, HIGH);
  
  // start the SPI library:
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
  Clear_SR_Note_Data();
  Clear_SR_LED_Data();
  Reset_SR();
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
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part1_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
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

        
  
// Part 2 ...............................

  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part1_stop_time = micros();
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
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
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


        
// Part 3 ............................................
 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part2_stop_time = micros();
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
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
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


// Part 4 ........................................................................
 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part3_stop_time = micros();
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part4_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);         
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune4_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              Load_Note = pgm_read_byte(&Tune4[Note_Count][Beat_Count]);
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

// Part 5 ........................................................................
 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part4_stop_time = micros();
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part5_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);         
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune5_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              Load_Note = pgm_read_byte(&Tune5[Note_Count][Beat_Count]);
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

// Part 6 .......................
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part5_stop_time = micros();
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part6_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune6_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune6[Note_Count][Beat_Count]);
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

        
  
// Part 7 ...............................

  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part6_stop_time = micros();
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part7_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);             
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune7_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              Load_Note = pgm_read_byte(&Tune7[Note_Count][Beat_Count]);
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


// Part 8 .......................
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part7_stop_time = micros();
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part8_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune8_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune8[Note_Count][Beat_Count]);
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

        
  // Part 9 .......................
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part8_stop_time = micros();
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part9_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune9_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune9[Note_Count][Beat_Count]);
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

        
// Part 10 .......................
  digitalWrite(ledpin,HIGH); 
  Graphene_Signal = 1;
  Solenoid_On_Time_2 = 1200;
  part9_stop_time = micros();
  
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
        }
  Graphene_Signal = 1; // debounce 1msec
  part10_start_time = micros();
  digitalWrite(ledpin, LOW);
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
        {
      Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
        }
  delay(start_delay);      
  Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
  Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
      
  for (int Beat_Count=0; Beat_Count < Tune10_Length; Beat_Count++)
      {
        
       for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
            {
              
              Load_Note = pgm_read_byte(&Tune10[Note_Count][Beat_Count]);
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

part10_stop_time = micros();
part11_start_time = micros();      
  
  
//-----------------
        



    
// calculate tempo's - use this for code check
   part1_tempo = ((min_us*Part1_Bars)/(part1_stop_time-part1_start_time));  
   part2_tempo = ((min_us*Part2_Bars)/(part2_stop_time-part2_start_time));  
   part3_tempo = ((min_us*Part3_Bars)/(part3_stop_time-part3_start_time));  
   part4_tempo = ((min_us*Part4_Bars)/(part4_stop_time-part4_start_time));  
   part5_tempo = ((min_us*Part5_Bars)/(part5_stop_time-part5_start_time));  
   part6_tempo = ((min_us*Part6_Bars)/(part6_stop_time-part6_start_time));  
   part7_tempo = ((min_us*Part7_Bars)/(part7_stop_time-part7_start_time));   
  

// calculate tempo's - use this with graphene
   part1_tempo = ((min_us*Part1_Bars)/(part2_start_time-part1_start_time));  
   part2_tempo = ((min_us*Part2_Bars)/(part3_start_time-part2_start_time));  
   part3_tempo = ((min_us*Part3_Bars)/(part4_start_time-part3_start_time));  
   part4_tempo = ((min_us*Part4_Bars)/(part5_start_time-part4_start_time));  
   part5_tempo = ((min_us*Part5_Bars)/(part6_start_time-part5_start_time));  
   part6_tempo = ((min_us*Part6_Bars)/(part7_start_time-part6_start_time));  
   part7_tempo = ((min_us*Part7_Bars)/(part8_start_time-part7_start_time));  
  
         
// display results   
       
  Serial.begin(9600);
  
  Serial.print("Shift Register Load Time: ");  
  Serial.println(sr_stop_time-sr_start_time);
  
  Serial.print("Part 1 Tempo: ");
  Serial.print(part1_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part2_start_time-part1_stop_time)/1000);
  
  Serial.print("Part 2 Tempo: ");
  Serial.print(part2_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part3_start_time-part2_stop_time)/1000);
  
  Serial.print("Part 3 Tempo: ");
  Serial.print(part3_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part4_start_time-part3_stop_time)/1000);
  
  Serial.print("Part 4 Tempo: ");
  Serial.print(part4_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part5_start_time-part4_stop_time)/1000);
  
  Serial.print("Part 5 Tempo: ");
  Serial.print(part5_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part6_start_time-part5_stop_time)/1000);
  
  Serial.print("Part 6 Tempo: ");
  Serial.print(part6_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part7_start_time-part6_stop_time)/1000);
  
  Serial.print("Part 7 Tempo: ");
  Serial.print(part7_tempo);
  Serial.print("   Dwell: ");  
  Serial.println((part8_start_time-part7_stop_time)/1000);
  
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

