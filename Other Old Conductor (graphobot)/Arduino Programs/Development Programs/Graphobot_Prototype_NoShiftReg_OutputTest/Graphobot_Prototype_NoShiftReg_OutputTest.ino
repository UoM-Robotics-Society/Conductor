#include <SPI.h>

// #define Tune_Length for each part

const int Tune_Length = 1; 
const int Part_Bars = 1;

const int Robot_Max = 1; // Max number of robots playing at the same time
const int Pin_RobotNum = 1; // Number of robots on pins

const int Tempo = 140; // Beats per minute

const long int BeatTime_Part1 = 5000000; // 5 Seconds

long int Beat_Time; 

const int start_delay = 0;  // in uS, Time delay before note is played

const unsigned char Tune[Robot_Max][Tune_Length] PROGMEM = {{1}}; //{{Robot1}}
  
int Beat_Count = 0; // Used to index Tune array
int Robot_Count = 0; // Used to index Tune array
int On_Signal = 0; // Used to track conductor

int Pin_Count = 0;


// define I/O pins
const int ledpin = 13; // flash led
const int On_Button = 10; // singnal from graphine conductor, set low with output pin


// define robot outputs

const int Pin_Robot_0 = 7;  // Robot 1, Glockobot
const int Pin_Robots[Pin_RobotNum] = {Pin_Robot_0};

// Timing check variables

unsigned long min_us= 240000000;

unsigned long part_start_time= 0;
unsigned long part_tempo= 0;
unsigned long part_stop_time= 0;

int Pin_Robot_Data[Pin_RobotNum];

unsigned char Load_Robot;


volatile unsigned int Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


void setup() 
{
  
    // configure I/O pins
    pinMode(ledpin, OUTPUT);
    pinMode(On_Button, INPUT_PULLUP);

    pinMode(Pin_Robot_0, OUTPUT);
    
    digitalWrite(ledpin, LOW);
    digitalWrite(On_Button, HIGH);

    digitalWrite(Pin_Robot_0, LOW);
      
    // Start USB Serial for monitoring
    Serial.begin(9600);   
    Serial.println("USB Working!");
   
    Clear_Pin_Robot_Data();

    Serial.print("Pin_Robot_Data: ");
    Serial.print(Pin_Robot_Data[0]);
    Serial.print(", ");
    Serial.print(Pin_Robot_Data[1]);
    Serial.print(", ");
    Serial.print(Pin_Robot_Data[2]);
    Serial.println(", ");
    
    Beat_Time = BeatTime_Part1;
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
      Beat_Time = BeatTime_Part1;
      Start_Beat_Timer(); // Start Timer 1 with correct Tempo
          
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

          Play_Beat();
          Serial.println();
         
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
    
    
    
    
    // calculate tempo's - use this for code check
       part_tempo = ((min_us*Part_Bars)/(part_stop_time-part_start_time));  
             
    // display results   
      Serial.print("Part 1 Tempo: ");
      Serial.print(part_tempo);
    //  Serial.print("   Dwell: ");  
    //  Serial.println((part2_start_time-part1_stop_time)/1000);
             
      Serial.println("-----------------------------------------------------------------");
  
  //-----------------
}


// --------------------------------------------------------------------------------------


void Clear_Pin_Robot_Data()
{
  for (int i=0; i < Pin_RobotNum; i++)
  {
      Pin_Robot_Data[i] = 0;    // clear all bits
  }
}


void Load_Beat(unsigned char RobotNum, unsigned char Play) 
{
        if (Play == 1)
        {
            Pin_Robot_Data[RobotNum] = 1;
        }
        else
        {
            Pin_Robot_Data[RobotNum] = 0;
        }  
}


void Play_Beat() 
{
    Load_Notes_Pin(); // Load notes onto pins
}

void Load_Notes_Pin()
{
    Serial.print("Pin_Robot_Data: ");
    for (int i=0; i < Pin_RobotNum; i++)
    {
        if(Pin_Robot_Data[i] == 1)
        {
            digitalWrite(Pin_Robots[i], HIGH);
            Serial.print("On: ");
            Serial.print(Pin_Robot_Data[i]); 
        }
        else
        {
            digitalWrite(Pin_Robots[i], LOW);
            Serial.print("Off: ");
            Serial.print(Pin_Robot_Data[i]); 
        }
       
       Serial.print(", ");
    }    
}

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

