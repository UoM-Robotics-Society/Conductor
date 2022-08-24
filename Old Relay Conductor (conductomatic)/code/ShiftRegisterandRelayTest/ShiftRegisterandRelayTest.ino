#include <SPI.h>

const int MaxNumSongs = 1;  // Number of songs to be loaded
const int NumSongs = 1;     // Number of songs to be loaded
const int RobotMax = 8;     // Max number of robots used

const int Tune1Length = 8;
//const int Tune1Length = 256;
const int Tune1Tempo = 60;
const int Tune1BeatDenom = 2;

  // Part 1
const unsigned int Tune1[RobotMax][Tune1Length] PROGMEM = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1}};
//  {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
//  {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},
//  {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},
//  {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
//  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

// Create array to store information about songs
int Tune_Info[MaxNumSongs][3];

// Create program variables
int On_Signal;    // Used to track conductor
unsigned int Load_Robot;

int BeatCount = 0; // Used to index Tune array
int RobotCount = 0; // Used to index Tune array
int SongCount = 0;

const int start_delay = 0;

const int Robot_On = 1;
const int Robot_Off = 0;


// define I/O pins  
const int SR_Latch_Pin = 9; // latch shift register ( Wire)
const int SR_Reset_Pin = 8; // reset shift register ( Wire)
//For SPI on UNO, MOSI - 11 ( Wire) and SCK - 13 ( Wire)

const int SR_LClK_Pin = 7;

const int On_Button = 4;          // signal from graphine conductor, set low with output pin ( Wire)
//const int On_Button_Light = 2;  // Turn on light in switch when the conductor is ready to start a song ( Wire)



// define Shift Register Length
const int SR_Length = 1; // Adjust to match instrument

// define robot output number
// Output Number = Robot Number 
int SR_Output[SR_Length*8] = {0,1,2,3,4,5,6,7};

int Robot_Data[SR_Length];
byte SR_Note_Data[SR_Length];


// Shift Register Output patterns, Relay is activated by low signal
byte      All_OFF = B11111111;
byte      All_ON = B00000000;
byte      On_1 = B11110110;


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

  // Timing Variables
volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo
volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt



void setup() 
{
     // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1Tempo;
    Tune_Info[0][2] =  Tune1BeatDenom;

    pinMode(SR_Latch_Pin, OUTPUT);
    pinMode(SR_Reset_Pin, OUTPUT);
    pinMode(SR_LClK_Pin, OUTPUT);
    pinMode(On_Button, INPUT_PULLUP);
    
    digitalWrite(SR_Latch_Pin, LOW);
    digitalWrite(SR_Reset_Pin, HIGH);
    digitalWrite(SR_LClK_Pin, LOW);
    digitalWrite(On_Button, HIGH);

    // Start USB Serial for monitoring
    Serial.begin(9600);   
    Serial.println("USB Working!");
    
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
    
    Reset_SR(); 
}

void loop() 
{
    Serial.print("Number of Notes: ");
    Serial.println(Tune_Info[0][0]);     
    Serial.print("Tempo(Bpm): ");
    Serial.println(Tune_Info[0][1]);        
    Serial.print("Beat Denomination: ");
    Serial.println(Tune_Info[0][2]);

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
    Serial.println(Beat_Time/1000000.0);
    Serial.println();

    Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
    Start_Beat_Timer(); // Start Timer 1

    for(SongCount = 0; SongCount < NumSongs; SongCount++)
    {   
          //Serial.print("Song: ");
          //Serial.println(SongCount);

          for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
          {
                //Serial.print("Beat: ");
                //Serial.println(BeatCount);

                for (RobotCount=0; RobotCount < RobotMax; RobotCount++)
                {  
                      //Serial.print("Robot: ");
                      //Serial.println(RobotCount);

                      Load_Robot = pgm_read_byte(&Tune1[RobotCount][BeatCount]);                     
                      //Serial.print("Load_Robot: ");
                      //Serial.println(Load_Robot);
                      
                      Load_Beat(RobotCount,Load_Robot);   
                      //Serial.print("Note_Data: ");
                      //Serial.println(SR_Note_Data[0]);
                }

                Play_Beat();
                //Serial.print("Note_Data: ");
                //Serial.println(SR_Note_Data[0]);
                
                //Serial.println();

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

          part_stop_time = micros();
        
    
          //-----------------
          // calculate tempo
              
              
          part_time = (part_stop_time-part_start_time)/1000000.0; 
          part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][2])/part_time)*60.0;
    
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
    for(int i = 0; i < (SR_Length*8); i++)
    {
        if(SR_Output[i] == RobotNum)
        {
            if(Play == 1)
            { 
                SR_Note_Data[0] = SR_Note_Data[0] - (1<<i);
            }
        }
    }
}


void Play_Beat() 
{
    sr_start_time=micros();

    Load_Notes_SR();
    Set_SR();
    Clear_SR_Note_Data();
    
    sr_stop_time=micros();
}

void Load_Notes_SR() 
{
  //digitalWrite(SR_Latch_Pin, LOW);
  for(int i=0; i < SR_Length; i++)
  {
      SPI.transfer(SR_Note_Data[i]);  
  }
}

void Set_SR() 
{
    digitalWrite(SR_LClK_Pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(SR_LClK_Pin, LOW);
}

void Reset_SR() 
{
    digitalWrite(SR_Reset_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(SR_Reset_Pin, HIGH);

    Clear_SR_Note_Data();
    Load_Notes_SR();
    Set_SR();
}

void Clear_SR_Note_Data()
{
  for ( int i=0; i < SR_Length; i++)
  {
      SR_Note_Data[i] = All_OFF;    // clear all bits
  }
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
