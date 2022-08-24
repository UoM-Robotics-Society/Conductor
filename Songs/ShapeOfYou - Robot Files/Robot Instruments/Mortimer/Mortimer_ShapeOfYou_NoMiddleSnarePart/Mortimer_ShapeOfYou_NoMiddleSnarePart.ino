#include <SPI.h>
#include <SD.h>


// Information about songs for loading
const int MaxNumSongs = 1;  // Number of songs to be loaded
const int NumSongs = 1;     // Number of songs to be loaded
const int DrumMax = 2;      // Max number of robots used

const int Tune1Length = 63;
const int Tune1Tempo = 97;
const int Tune1BeatDenom = 4;

  // 1st line - snare, 2nd line - cymbal, 3rd line - bass 
  // Main Pattern
const unsigned int Tune1[DrumMax][Tune1Length] PROGMEM = {
  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1},
  {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0}};
  //{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; 

const int DrumTime = 50;  // Amount of time the between the drum stick going down and coming back up, in mS

const int start_delay = 0;

// Create program variables
int On_Signal;    // Used to track conductor
unsigned int Load_Drum[DrumMax];
unsigned int Load_Timing;

int BeatCount = 0; // Used to index Tune array
int DrumCount = 0; // Used to index Tune array
int SongCount = 0;

int SR_Count = 0;

// Create array to store information about songs
int Tune_Info[MaxNumSongs][4];

// define I/O pins
const int ledpin = 13; // flash led
const int On_Button = 8;          // signal from graphine conductor, set low with output pin (White Wire)

const int SnarePin = 33;
const int BassPin = 35;
const int CymbalPin = 31;

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

volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt


void setup() 
{
    // Populate array to store song information
    Tune_Info[0][0] =  Tune1Length;
    Tune_Info[0][1] =  Tune1Tempo;
    Tune_Info[0][2] =  Tune1BeatDenom;
        
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
    
    // Start USB Serial for monitoring
    Serial.begin(9600);   
    Serial.println("USB Working!");
}


// --------------------------------------------------------------------------------------

void loop() 
{
    for(SongCount = 0; SongCount < NumSongs; SongCount++)
    {   
//          Serial.print("SongCount, Song Number, : ");
//          Serial.print(SongCount);
//          Serial.print(", ");
//          Serial.println(SongCount);
//          Serial.print("Number of Notes: ");
//          Serial.println(Tune_Info[SongCount][0]);
//          Serial.print("Tempo(Bpm): ");
//          Serial.println(Tune_Info[SongCount][1]);
//          Serial.print("Beat Denomination: ");
//          Serial.println(Tune_Info[SongCount][2]);
          
//          Serial.println("Ready to play, waiting for On Signal");

          On_Signal = 1;
          while (On_Signal > 0)
          {
              On_Signal = digitalRead(On_Button); // Wait for Graphene ON (LOW)
          }

          part_start_time = micros();
          delay(start_delay);
//          Serial.println("Song Start");

          Beat_Time = (1/(Tune_Info[SongCount][1]/60.0))/Tune_Info[SongCount][2]*1000000.0;
//          Serial.print("Beat Time (s): ");
//          Serial.println(Beat_Time/1000000.0);
//          Serial.println();

          //Beat_Time = 1000000;
          Next_Beat = 0;      // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timer 1

          for (BeatCount=0; BeatCount < Tune_Info[SongCount][0]; BeatCount++)
          {
                //Serial.print("Beat: ");
                //Serial.println(BeatCount);

                for (DrumCount=0; DrumCount < DrumMax; DrumCount++)
                {  
                      //Serial.print("Drum: ");
                      //Serial.println(DrumCount);

//                      if(SongCount == 0)
//                      {
                          Load_Drum[DrumCount] = pgm_read_byte(&Tune1[DrumCount][BeatCount]);
//                      }
//                      if(SongCount == 1)
//                      {
//                          Load_Drum[DrumCount] = pgm_read_byte(&Tune2[DrumCount][BeatCount]);
//                      }
                      
                      
                      //Serial.print("Drum ");
                      //Serial.print(DrumCount);
                      //Serial.print(": ");
                      //Serial.print(Load_Drum[DrumCount]);
                      //Serial.println(", ");  
                }

                Play_Beat();
                //Serial.println();

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
        
    
          //-----------------
          // calculate tempo
              
              
          part_time = (part_stop_time-part_start_time)/1000000.0; 
          part_tempo = ((Tune_Info[SongCount][0]/Tune_Info[SongCount][2])/part_time)*60.0;
    
          // display results   
          Serial.print("Part Time (s): ");
          Serial.println(part_time);
          Serial.print("Part Tempo (bpm): ");
          Serial.println(part_tempo);
          
          Serial.println("------------------------------------------------");
          Serial.println();

    }
      
      Serial.println("-----------------------------------------------------------------");
   
             
}

// --------------------------------------------------------------------------------------

// Play drums functions

void Play_Beat() 
{
      if(Load_Drum[0] == 1)
      {
          digitalWrite(SnarePin,HIGH);
      }
      if(Load_Drum[1] == 1)
      {
          digitalWrite(CymbalPin,HIGH);
      }
      if(Load_Drum[2] == 1)
      {
          digitalWrite(BassPin,HIGH);
      }
      
      delay(DrumTime);

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
          digitalWrite(BassPin,LOW);
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

  
