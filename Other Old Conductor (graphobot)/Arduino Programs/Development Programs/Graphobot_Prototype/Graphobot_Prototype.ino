#include <SPI.h>

// #define Tune_Length for each part

const int Tune_Length = 5; 
const int Part_Bars = 1;

const int Robot_Max = 5; // Max number of robots playing at the same time
const int Tempo = 140; // Beats per minute

const long Beat_Time = 1000000; // in uS, 1 beat at 60bpm

const int start_delay = 0;  // in uS, Time delay before note is played

//const unsigned char Tune[Robot_Max][Tune_Length] PROGMEM = {{1,2,3,4,5}};
//const unsigned char Tune[Robot_Max][Tune_Length] PROGMEM = {{1,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1}}; //{{Robot1},{Robot2},{Robot3},{Robot4},{Robot5}}
//const unsigned char Tune[Robot_Max][Tune_Length] PROGMEM = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}}; //{{Robot1},{Robot2},{Robot3},{Robot4},{Robot5}}
const unsigned char Tune[Robot_Max][Tune_Length] PROGMEM = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}}; //{{Robot1},{Robot2},{Robot3},{Robot4},{Robot5}}
  
int Beat_Count = 0; // Used to index Tune array
int Robot_Count = 0; // Used to index Tune array
int On_Signal = 0; // Used to track conductor


// define I/O pins
const int ledpin = 13; // flash led
const int SR_Latch_Pin = 9; // latch shift register
const int SR_Reset_Pin = 8; // reset shift register
  // SPI Coms - MOSI-11, MISO-12, SCK-13
const int On_Button = 5; // singnal from graphine conductor, set low with output pin

// define Shift Register Length
const int SR_Length    = 5; // Adjust to match instrument

// define robot positions in shift register

const int SR_Robot_0   = 4; //Robot 1
const int SR_Robot_1   = 3; //Robot 2
const int SR_Robot_2   = 2; //Robot 3
const int SR_Robot_3   = 1; //Robot 4
const int SR_Robot_4   = 0; //Robot 5

// Timing check variables

unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;

unsigned long part_start_time= 0;
unsigned long part_tempo= 0;
unsigned long part_stop_time= 0;


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
    
    Start_Beat_Timer(); // Start Timmer 1 with correct Tempo ADDED FIXED First Time THROUGH ISSUES !!!
    while (Next_Beat < 1)
    {
        // Waitfor Beat Timer 
    }
        
}


// --------------------------------------------------------------------------------------

void loop() 
{   
      digitalWrite(ledpin, LOW); 
      On_Signal = 1;     
      while (On_Signal > 0)
      {
          On_Signal = digitalRead(On_Button); //  Wait for On Button to be pressed 
          
      }
      
      Serial.println("Part Start");
      part_start_time = micros();
      digitalWrite(ledpin, HIGH);
      delay(start_delay);      
      
      Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
      Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
          
      for (int Beat_Count=0; Beat_Count < Tune_Length; Beat_Count++)
      {
          Serial.print("Beat ");
          Serial.println(Beat_Count);
              
          for (int Robot_Count=0; Robot_Count < Robot_Max; Robot_Count++)
          {
                  
              Load_Robot = pgm_read_byte(&Tune[Robot_Count][Beat_Count]);
              Load_Beat(Robot_Count,Load_Robot);
              Serial.print("Robot ");
              Serial.print(Robot_Count);
              Serial.print(": ");
              Serial.print(Load_Robot);
              Serial.println(", ");
          }  
          
         
          Serial.print("Robot Playing: ");
          
          Play_Beat();
          Serial.println();
          delay(5000);
          
          
                
          Flash_LED_ON();   
    
          Clear_SR_Note_Data();
          Clear_SR_LED_Data(); 
          
          while (Next_Beat < 1)
          {
            // Waitfor Beat Timer 
          }
          
          // Turn OFF LEDs
          Reset_SR();
          Next_Beat = 0;
      }
          
      digitalWrite(ledpin,HIGH); 
        
      while (On_Signal < 1)
      {
          On_Signal = digitalRead(On_Button); //  Wait for Graphene signal OFF (HIGH)
      }
      part_stop_time = micros();
    
    
    
    
    // calculate tempo's - use this for code check
       part_tempo = ((min_us*Part_Bars)/(part_stop_time-part_start_time));  
             
    // display results   
      Serial.print("Shift Register Load Time: ");  
      Serial.println(sr_stop_time-sr_start_time);
      
      Serial.print("Part 1 Tempo: ");
      Serial.print(part_tempo);
    //  Serial.print("   Dwell: ");  
    //  Serial.println((part2_start_time-part1_stop_time)/1000);
             
      Serial.println("-----------------------------------------------------------------");
  
  //-----------------
}


// --------------------------------------------------------------------------------------

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

void Load_Beat(unsigned char Count, unsigned char Robot) 
{
    switch (Count) 
    {
       case 0:   // Robot 1
          if (Robot == 1)
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
        
        case 1:   // Robot 2
          if (Robot == 1)
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
        
        case 2:   // Robot 3
          if (Robot == 1)
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
       
        case 3:   // Robot 4
          if (Robot == 1)
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
        
        case 4:   // Robot 5
          if (Robot == 1)
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
      
        default: 
          // if nothing else matches, do the default
          // default is optional
        break;
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
        SPI.transfer(SR_LED_Data[i]);   // clear all bits
    }
    Set_SR();
}

void Play_Beat() 
{
    digitalWrite(SR_Reset_Pin, HIGH);
    Load_Notes_SR();
    //delayMicroseconds(5000);
    //Reset_SR();    
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

