#include <SPI.h>
#include <SD.h>


// Information about songs for loading
const int MaxNumSongs = 1;  // Number of songs to be loaded
const int NumSongs = 1;     // Number of songs to be loaded

const int Tune1Length = 7;
const int Tune1RobotMax = 5;
const int Tune1Tempo = 30;
const int Tune1BeatDenom = 1;

  // Test Notes
const unsigned int Tune1[Tune1RobotMax][Tune1Length] PROGMEM = {{1,0,0,0,0,1,1},{0,1,0,0,0,1,1},{0,0,1,0,0,1,1},{0,0,0,1,0,1,1},{0,0,0,0,1,1,1}}; //{{Robot1},{Robot2},{Robot3},{Robot4},{Robot5}}
const int start_delay = 0;

// Create program variables
int On_Signal;    // Used to track conductor
unsigned int Load_Note;

int RobotCount;
int BeatCount;
int SongCount;

// Create array to store information about songs
int Tune_Info[MaxNumSongs][4];

// Define I/O pins
const int Conductor_Pin = 5;  // Pin number for connecting conductor or button, Arduino Uno
const int SR_Latch_Pin = 9; // latch shift register
const int SR_Reset_Pin = 8; // reset shift register
  // SD Card Reader - MOSI-11, MISO-12, SCK-13, CS-8

// Define Shift Register Length
const int SR_Length = 5; // Adjust to match instrument

// Define key positions in shift register
const int SR_Robot_0 = 4; // Midi note 79
const int SR_Robot_1 = 3; // Midi note 81
const int SR_Robot_2 = 2; // Midi note 83
const int SR_Robot_3 = 1; // Midi note 84
const int SR_Robot_4 = 0; // Midi note 86


// Shift Register Output patterns
byte      Robot_ON = B00000010;
byte      LED_ON = B00000100;
byte      ALL_ON = B00000110;
byte      All_OFF = B00000000;
byte      SR_Note_Data[SR_Length];
byte      SR_LED_Data[SR_Length]; 

// Variable for measuring time of part and calculating tempo
unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;
long int Beat_Time;

unsigned long part_start_time = 0;
unsigned long part_stop_time = 0;
float part_time = 0;
int part_tempo = 0;

// Set time delay for length of pulse sent to the robots
const int Pulse_On_Time = 1000; // Pulse width in uSec Fixed

volatile unsigned int Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo
volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


void setup() 
{
    // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1RobotMax;
    Tune_Info[0][2] =  Tune1Tempo;
    Tune_Info[0][3] =  Tune1BeatDenom;
   

    // Configure I/O pins
    pinMode(Conductor_Pin, INPUT_PULLUP);
    pinMode(SR_Latch_Pin, OUTPUT);
    pinMode(SR_Reset_Pin, OUTPUT);

    digitalWrite(Conductor_Pin, HIGH);
    digitalWrite(SR_Latch_Pin, LOW);
    digitalWrite(SR_Reset_Pin, LOW);
    
    // Begin USB Serial
    Serial.begin(9600);

    // Begin SD Card Serial
    SD.begin(8);

    // start the SPI library:
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
    Clear_SR_Note_Data();
    Clear_SR_LED_Data();
    Reset_SR();   

    
}  

// --------------------------------------------------------------------------------------

void loop() 
{
    for(SongCount = 0; SongCount < NumSongs; SongCount++)
    {    
          Serial.print("Number of Notes: ");
          Serial.println(Tune_Info[SongCount][0]);
          Serial.print("Max Notes: ");
          Serial.println(Tune_Info[SongCount][1]);
          Serial.print("Tempo(Bpm): ");
          Serial.println(Tune_Info[SongCount][2]);
          Serial.print("Beat Denomination: ");
          Serial.println(Tune_Info[SongCount][3]);
          
          Serial.println("Ready to play, waiting for On Signal");
          
          On_Signal = 1;
          while (On_Signal > 0)
          {
              On_Signal = digitalRead(Conductor_Pin); // Wait for Graphene ON (LOW)
          }
          On_Signal = 1;
          
          part_start_time = micros();
          delay(start_delay);
          Serial.println("Song Start");

          Beat_Time = (1/(Tune_Info[SongCount][2]/60.0))/Tune_Info[SongCount][3]*1000000.0;
          Serial.print("Beat Time (s): ");
          Serial.println(Beat_Time/1000000.0);

          Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timer 1

          for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
          {
                Serial.print("Beat: ");
                Serial.println(BeatCount);
                          
                for (RobotCount=0; RobotCount < Tune_Info[SongCount][1]; RobotCount++)
                { 
                      Load_Note = pgm_read_byte(&Tune1[RobotCount][BeatCount]);
                                           
                      Serial.print("Note: ");
                      Serial.println(Load_Note);
               
                      Load_Beat(RobotCount, Load_Note);
                      Play_Beat();
                }
                Serial.println();
                
                //Flash_LED_ON();   

                Clear_SR_Note_Data();
                
                Next_Beat = 0;                
                while (Next_Beat < 1)
                {
                  // Waitfor Beat Timer 
                }
                Next_Beat = 0;
                Reset_SR();
                  
          }
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
          
          Serial.println("-----------------------------------------------------------------");

    } 
    
      
}
// --------------------------------------------------------------------------------------

// Load note functions
void Load_Beat(unsigned char RobotNumber, unsigned char PlayFlag) 
{
// Load note and LED arrays ready for shift register
    Serial.print("RobotNumber: ");
    Serial.println(RobotNumber);
    Serial.print("PlayFlag: ");
    Serial.println(PlayFlag);
    
    switch (RobotNumber) 
    {
        case 0:
          if (PlayFlag == 1)
          {
              //SR_Note_Data[SR_Robot_0] = Robot_ON;
              SR_Note_Data[SR_Robot_0] = ALL_ON;
              SR_LED_Data[SR_Robot_0] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_0] = All_OFF;
              SR_LED_Data[SR_Robot_0] = All_OFF;
          }
          break;
        case 1:
          if (PlayFlag == 1)
          {
              //SR_Note_Data[SR_Robot_1] = Robot_ON;
              SR_Note_Data[SR_Robot_1] = ALL_ON;
              SR_LED_Data[SR_Robot_1] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_1] = All_OFF;
              SR_LED_Data[SR_Robot_1] = All_OFF;
          }
          break;
        case 2:
          if (PlayFlag == 1)
          {
              //SR_Note_Data[SR_Robot_2] = Robot_ON;
              SR_Note_Data[SR_Robot_2] = ALL_ON;
              SR_LED_Data[SR_Robot_2] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_2] = All_OFF;
              SR_LED_Data[SR_Robot_2] = All_OFF;
          }
          break;
        case 3:
          if (PlayFlag == 1)
          {
              //SR_Note_Data[SR_Robot_3] = Robot_ON;
              SR_Note_Data[SR_Robot_3] = ALL_ON;
              SR_LED_Data[SR_Robot_3] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_3] = All_OFF;
              SR_LED_Data[SR_Robot_3] = All_OFF;
          }
          break;
        case 4:
          if (PlayFlag == 1)
          {
              //SR_Note_Data[SR_Robot_4] = Robot_ON;
              SR_Note_Data[SR_Robot_4] = ALL_ON;
              SR_LED_Data[SR_Robot_4] = LED_ON;
          }
          else
          {
              SR_Note_Data[SR_Robot_4] = All_OFF;
              SR_LED_Data[SR_Robot_4] = All_OFF;
          }
          break;
        default: 
          // if nothing else matches, do the default
          // default is optional
        break;
      }
}

// Shift Register Functions
void Clear_SR_Note_Data() 
{
    for ( int i=0; i < SR_Length; i++)
    {
        SR_Note_Data[i] = All_OFF;                  // clear all bits
    }
}
  
void Clear_SR_LED_Data() 
{
    for ( int i=0; i < SR_Length; i++)
    {
        SR_LED_Data[i] = All_OFF;                  // clear all bits
    }
}

void Flash_LED_ON() 
{
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_LED_SR();
    Clear_SR_LED_Data();
}


void Load_LED_SR() 
{
    digitalWrite(SR_Latch_Pin, LOW);
    for ( int i=0; i < SR_Length; i++)
    {
        SPI.transfer(SR_LED_Data[i]);                  // clear all bits
    }
    Set_SR();
}

void Play_Beat() 
{
// sends a timed pulse to the selected robots
    //First Pulse
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_Notes_SR();
    //delayMicroseconds(Pulse_On_Time);
    //Reset_SR();
    
    //Clear_SR_Note_Data();
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
    for ( int i=0; i < SR_Length; i++)
    {
      SPI.transfer(SR_Note_Data[i]);           
    }
    Set_SR();
    sr_stop_time=micros();
}


// Functions for interrupt timer

void Start_Beat_Timer() 
{
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
  
