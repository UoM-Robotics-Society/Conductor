#include <SoftwareSerial.h>


// calibration done at 6V and T2 800, notes just striking
// All 30 notes now connected and working 22/06/2016
// Added volume 14/06/2016
// Split into 18 parts 23/07/2016


// #define Tune_Length for each part

//const int Tune1_Length 7 
const int Tune1_Length = 677;
const long Part1_Bars = 43.5; 

const int Note_Max = 2; // Max number of notes struck per beat = 4

const long int BeatTime_Part1 = 90909; // 1/16th beat time in uSec( 165bpm )
//const long int BeatTime_Part1 = 161290; // 1/16th beat time in uSec( 93bpm )

long int Beat_Time;

const int start_delay = 0;


//const unsigned char Tune1[Note_Max][Tune1_Length] PROGMEM = {{95,90,83,0,0,0,90}};
const unsigned char Tune1[Note_Max][Tune1_Length] PROGMEM = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,81,0,0,0,47,0,0,0,45,0,0,0,43,0,0,0,42,0,0,0,40,0,0,0,38,0,0,0,37,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,38,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,38,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,39,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,39,0,0,0,58,0,0,0,42,0,0,0,58,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,38,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,54,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,42,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,43,0,0,0,0,0,0,0,42,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,50,0,0,0,50,0,0,0,50,0,0,0,50,0,0,0,50,0,0,0,50,0,0,0,50,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,50},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,81,0,0,0,59,0,0,0,57,0,0,0,55,0,0,0,54,0,0,0,52,0,0,0,50,0,0,0,49,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,65,0,0,0,47,0,0,0,64,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,65,0,0,0,47,0,0,0,64,0,0,0,47,0,0,0,62,0,0,0,47,0,0,0,62,0,0,0,50,0,0,0,62,0,0,0,50,0,0,0,62,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,51,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,51,0,0,0,66,0,0,0,54,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,65,0,0,0,47,0,0,0,64,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,50,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,66,0,0,0,47,0,0,0,65,0,0,0,47,0,0,0,64,0,0,0,47,0,0,0,62,0,0,0,47,0,0,0,62,0,0,0,47,0,0,0,62,0,0,0,47,0,0,0,62,0,0,0,35,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,59,0,0,0,0,0,0,0,0,0,0,0,55,0,0,0,55,0,0,0,54,0,0,0,54,0,0,0,0,0,0,0,54,0,0,0,0,0,0,0,54,0,0,0,35,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,59,0,0,0,0,0,0,0,0,0,0,0,55,0,0,0,55,0,0,0,54,0,0,0,54,0,0,0,0,0,0,0,54,0,0,0,0,0,0,0,54,0,0,0,35,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,56,0,0,0,56,0,0,0,56,0,0,0,56,0,0,0,56,0,0,0,56,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,47,0,0,0,59}};
 

int Beat_Count = 0; // Used to index Tune array
int Note_Count = 0; // Used to index Tune array
int Graphene_Signal = 0; // Used to track conductor


// define I/O pins
const int ledpin = 13; // flash led
const int Graphene_Sen_P = 8; // singnal from graphine conductor, read for status low indicates start, used for tests on Uno

unsigned long min_us= 240000000;

unsigned long part1_start_time = 0;
unsigned long part1_tempo = 0;
unsigned long part1_stop_time = 0;

unsigned long parttempo1_beats = 0;

float part1_time = 0;

unsigned char Load_Note[Note_Max];

volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt CHANGED

SoftwareSerial midiSerial(3,2); // Rx, Tx

void setup() {
  
  // configure I/O pins
  pinMode(ledpin, OUTPUT);
  pinMode(Graphene_Sen_P, INPUT_PULLUP);
    
  digitalWrite(ledpin, LOW);
  digitalWrite(Graphene_Sen_P, HIGH);
  
  Serial.begin(9600);
  midiSerial.begin(31250);

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
    Graphene_Signal = 1;
    
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
    Beat_Time = BeatTime_Part1;
    Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
        
    for (int Beat_Count=0; Beat_Count < Tune1_Length; Beat_Count++)
    {
          Serial.print("Beat: ");
          Serial.println(Beat_Count);
          digitalWrite(ledpin,HIGH); 
          
          for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
          {
                
                Load_Note[Note_Count] = pgm_read_byte(&Tune1[Note_Count][Beat_Count]);
                Play_Beat(Load_Note[Note_Count]);
          }
          Serial.println();
          
          while (Next_Beat < 1)
          {
        //           Waitfor Beat Timer 
          }

          for (int Note_Count=0; Note_Count < Note_Max; Note_Count++)
          {
                
                Load_Note[Note_Count] = pgm_read_byte(&Tune1[Note_Count][Beat_Count]);
                Stop_Beat(Load_Note[Note_Count]);
          }
          Serial.println();
                 
          Next_Beat = 0;
          digitalWrite(ledpin,LOW); 
         
      }
        
      digitalWrite(ledpin,HIGH); 
      
      while (Graphene_Signal < 1)
      {
          Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
      }
    
      part1_stop_time = micros(); 
  
  //-----------------
   
  // calculate tempo's - use this with graphene
  //   part1_tempo = ((min_us*Part1_Bars)/(part2_start_time-part1_start_time));  
      
      
  // calculate tempo's - use this for code check
     part1_tempo = ((min_us*Part1_Bars)/(part1_stop_time-part1_start_time));
     part1_time = (part1_stop_time-part1_start_time)/1000000.0; 
     parttempo1_beats = (Tune1_Length/4)/part1_time*60;    
  
  // display results   
    Serial.print("Part 1 Time (S): ");
    Serial.println(part1_time);
    Serial.print("Part 1 Tempo (Bars): ");
    Serial.println(part1_tempo);
    Serial.print("Part 1 Tempo (Beats): ");
    Serial.println(parttempo1_beats);
    Serial.print("   Dwell: ");  
  //  Serial.println((part2_start_time-part1_stop_time)/1000);
    Serial.println();
  
    Serial.println("-----------------------------------------------------------------");
}


// --------------------------------------------------------------------------------------

void Play_Beat(int Note)
{
    int cmd = 144;
    int velocity = 127;
    
    midiSerial.write(cmd); 
    midiSerial.write(Note);
    midiSerial.write(velocity);

    Serial.print("Note On: ");
    Serial.println(Note);
    
}

void Stop_Beat(int Note)
{
    int cmd = 128;
    int velocity = 127;
    
    midiSerial.write(cmd); 
    midiSerial.write(Note);
    midiSerial.write(velocity);

    Serial.print("Note Off: ");
    Serial.println(Note);
    
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

