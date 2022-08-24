#include <SPI.h>
#include <SD.h>


// Information about songs for loading
const int MaxNumSongs = 3;  // Number of songs to be loaded
const int NumSongs = 3;     // Number of songs to be loaded
const int RobotMax = 5;     // Max number of robots used

const int Tune1Length = 31;
const int Tune1Tempo = 97;
const int Tune1BeatDenom = 1;

const int Tune2Length = 46;
const int Tune2Tempo = 112;
const int Tune2BeatDenom = 1;

const int Tune3Length = 170;
const int Tune3Tempo = 153;
const int Tune3BeatDenom = 1;

  // Slow Part
const unsigned int Tune1[RobotMax][Tune1Length] PROGMEM = {
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}}; // Light at the start of every bar

  //{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0}}; // Light at the start of every other bar
  //{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1} // Light twice every bar

  // Medium Part
const unsigned int Tune2[RobotMax][Tune2Length] PROGMEM = {
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
  {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0}}; // Light at the start of every bar

//{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}}; // Light twice every bar

  // Fast Part
const unsigned int Tune3[RobotMax][Tune3Length] PROGMEM = {
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0}}; 

const int start_delay = 0;

// Create program variables
int On_Signal;    // Used to track conductor
unsigned int Load_Note;
unsigned int Load_Timing;

int BeatCount = 0; // Used to index Tune array
int RobotCount = 0; // Used to index Tune array
int SongCount = 0;

int Pin_Count = 0;
int SR_Count = 0;

// Create array to store information about songs
int Tune_Info[MaxNumSongs][4];

// define I/O pins
const int ledpin = 13; // flash led
const int SR_Latch_Pin = 9; // latch shift register (Yellow Wire)
const int SR_Reset_Pin = 8; // reset shift register (Purple Wire)
//For SPI, MOSI - 11 (Blue Wire) and SCK - 13 (Green Wire)
const int On_Button = 4;          // signal from graphine conductor, set low with output pin (White Wire)
//const int On_Button_Light = 2;  // Turn on light in switch when the conductor is ready to start a song (Orange Wire)

// define Shift Register Length
const int SR_Length = RobotMax; // Adjust to match instrument

// define robot outputs
const int SR_Robot_0 = 4;   // Robot 5, Tram Light
const int SR_Robot_1 = 3;   // Robot 4, Mortimer
const int SR_Robot_2 = 2;   // Robot 3, Raspberry Pi wav player
const int SR_Robot_3 = 1;   // Robot 2, Floppy Drives
const int SR_Robot_4 = 0;   // Robot 1, Glockobot

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

// Shift Register Output patterns

byte      Robot_ON = B00000010;
byte      LED_ON = B00000100;
byte      Robot_OFF = B00000000;
byte      LED_OFF = B00000000;
byte      All_OFF = B00000000;
byte      SR_Note_Data[SR_Length];
byte      SR_LED_Data[SR_Length]; 

unsigned char Load_Robot;


volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


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
    
    // configure I/O pins
    pinMode(ledpin, OUTPUT);
    pinMode(SR_Latch_Pin, OUTPUT);
    pinMode(SR_Reset_Pin, OUTPUT);
    pinMode(On_Button, INPUT_PULLUP);
   
    digitalWrite(ledpin, LOW);
    digitalWrite(SR_Latch_Pin, LOW);
    digitalWrite(SR_Reset_Pin, LOW);
    digitalWrite(On_Button, HIGH);
  
    // Start USB Serial for monitoring
    Serial.begin(9600);   
    Serial.println("USB Working!");
    
    // start the SPI library:
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
    Clear_SR_Note_Data();
    Clear_SR_LED_Data();
    Reset_SR();

    Serial.print("SR_Note_Data: ");
    Serial.print(SR_Note_Data[0]);
    Serial.print(", ");
    Serial.print(SR_Note_Data[1]);
    Serial.print(", ");
    Serial.print(SR_Note_Data[2]);
    Serial.print(", ");
    Serial.println(SR_Note_Data[3]);  
    
    //Beat_Time = BeatTime_Part1;
    Start_Beat_Timer(); // Start Timmer 1 with correct Tempo ADDED FIXED First Time THROUGH ISSUES !!!
    while (Next_Beat < 1)
    {
        // Waitfor Beat Timer 
    }
        
}


// --------------------------------------------------------------------------------------

void loop() 
{
    for(SongCount = 0; SongCount < NumSongs; SongCount++)
    {   
          Serial.print("Number of Notes: ");
          Serial.println(Tune_Info[SongCount][0]);
          Serial.print("Tempo(Bpm): ");
          Serial.println(Tune_Info[SongCount][1]);
          Serial.print("Beat Denomination: ");
          Serial.println(Tune_Info[SongCount][2]);
          
          Serial.println("Ready to play, waiting for On Signal");

          On_Signal = 1;
          while (On_Signal > 0)
          {
              On_Signal = digitalRead(On_Button); // Wait for Graphene ON (LOW)
          }

          part_start_time = micros();
          delay(start_delay);
          Serial.println("Song Start");

          Beat_Time = (1/(Tune_Info[SongCount][1]/60.0))/Tune_Info[SongCount][2]*1000000.0;
          Serial.print("Beat Time (s): ");
          Serial.println(Beat_Time); ///1000000.0);
          Serial.println();

          //Beat_Time = 1000000;
          Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timer 1

          for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
          {
                Serial.print("Beat: ");
                Serial.println(BeatCount);

                for (RobotCount=0; RobotCount < RobotMax; RobotCount++)
                {  
                      Serial.print("Robot: ");
                      Serial.println(RobotCount);

                      if(SongCount == 0)
                      {
                          Load_Robot = pgm_read_byte(&Tune1[RobotCount][BeatCount]);
                      }
                      else if(SongCount == 1)
                      {
                          Load_Robot = pgm_read_byte(&Tune2[RobotCount][BeatCount]);
                      }
                      else if(SongCount == 2)
                      {
                          Load_Robot = pgm_read_byte(&Tune3[RobotCount][BeatCount]);
                      }
                      else
                      {
                        
                      }

                      Load_Beat(RobotCount,Load_Robot);
                      Serial.print("Robot ");
                      Serial.print(RobotCount);
                      Serial.print(": ");
                      Serial.print(Load_Robot);
                      Serial.println(", ");  
                }
                
                Play_Beat();
                Serial.println();

                while (Next_Beat < 1)
                {
                  // Waitfor Beat Timer 
                }
          
                // Turn OFF LEDs
                Reset_SR();
                Next_Beat = 0;
          }

          while (On_Signal < 1)
          {
              On_Signal = digitalRead(On_Button); //  Wait for Graphene signal OFF (HIGH)
          }
          
          digitalWrite(ledpin,LOW); 
          part_stop_time = micros();
        
    
          //-----------------
          // calculate tempo
              
              
          part_time = (part_stop_time-part_start_time)/1000000.0; 
          part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][3])/part_time)*60.0;
    
          // display results   
          Serial.print("Part Time (s): ");
          Serial.println(part_time);
          Serial.print("Part Tempo (bpm): ");
          Serial.println(part_tempo);
          
          Serial.print("Shift Register Load Time: ");  
          Serial.println(sr_stop_time-sr_start_time);
          
          Serial.println("------------------------------------------------");
          Serial.println();

    }
      
      Serial.println("-----------------------------------------------------------------");
   
             
}

// --------------------------------------------------------------------------------------

// Load note functions

void Load_Beat(unsigned char RobotNum, unsigned char Play) 
{
    switch(RobotNum)
    {
        case 0:
          if (Play == 1)
          {
              SR_Note_Data[SR_Robot_0] = Robot_ON;
              SR_LED_Data[SR_Robot_0] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_0] = Robot_OFF;
              SR_LED_Data[SR_Robot_0] = LED_OFF;
          }
          break;

        case 1:
          if (Play == 1)
          {
              SR_Note_Data[SR_Robot_1] = Robot_ON;
              SR_LED_Data[SR_Robot_1] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_1] = Robot_OFF;
              SR_LED_Data[SR_Robot_1] = LED_OFF;
          }
          break;

        case 2:
          if (Play == 1)
          {
              SR_Note_Data[SR_Robot_2] = Robot_ON;
              SR_LED_Data[SR_Robot_2] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_2] = Robot_OFF;
              SR_LED_Data[SR_Robot_2] = LED_OFF;
          }
          break;

        case 3:
          if (Play == 1)
          {
              SR_Note_Data[SR_Robot_3] = Robot_ON;
              SR_LED_Data[SR_Robot_3] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_3] = Robot_OFF;
              SR_LED_Data[SR_Robot_3] = LED_OFF;
          }
          break;

        case 4:
          if (Play == 1)
          {
              SR_Note_Data[SR_Robot_4] = Robot_ON;
              SR_LED_Data[SR_Robot_4] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_4] = Robot_OFF;
              SR_LED_Data[SR_Robot_4] = LED_OFF;
          }
          break;    
    }
}

// Shift Register Functions

void Clear_SR_Note_Data()
{
  for ( int i=0; i < SR_Length; i++)
  {
      SR_Note_Data[i] = All_OFF;    // clear all bits
  }
}
  
void Clear_SR_LED_Data() 
{
  for ( int i=0; i < SR_Length; i++)
  {
      SR_LED_Data[i] = All_OFF;   // clear all bits
  }
}

void Flash_LED_ON() 
{
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_LED_SR();
    //Clear_SR_LED_Data();
}


void Load_LED_SR() 
{
    digitalWrite(SR_Latch_Pin, LOW);
    Serial.print("SR_LED_Data: ");
    
    for ( int i=0; i < SR_Length; i++)
    {
        SPI.transfer(SR_LED_Data[i]);   // clear all bits
        Serial.print(SR_LED_Data[i]); 
        Serial.print(", "); 
    }
    Set_SR();
}

void Play_Beat() 
{
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_Notes_SR();
    Load_LED_SR(); 
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
  

void Load_Notes_SR() 
{
  sr_start_time=micros();
  digitalWrite(SR_Latch_Pin, LOW);
  Serial.print("SR_Note_Data: ");
  for ( int i=0; i < SR_Length; i++)
  {
      SPI.transfer(SR_Note_Data[i]); 
      Serial.print(SR_Note_Data[i]); 
      Serial.print(", "); 
  }
  Set_SR();
  sr_stop_time=micros();
}

// Functions for interrupt timer

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

  
