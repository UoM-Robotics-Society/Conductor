#include <SoftwareSerial.h>

// #define Tune_Length for each part

const int Number_Parts = 2; // Number of different parts within the Piece 

//const int Part_Lengths[Number_Parts] = {5,5};  // Length of Parts in Beats
const int Part1_Length = 5; 
const int Part2_Length = 5; 

const int Part_Lengths[Number_Parts] = {Part1_Length,Part2_Length};

const int Part_Bars[Number_Parts] = {1,1}; // Length of Parts in Bars

#define Tempo 144 // Beats per minute

//const long Beat_Time = (60/Tempo)/8;
const long Beat_Time = 1000000; // 1 Sec

const int start_delay = 0;  // Delay before each note it played 

const unsigned char Tune1[Part1_Length] PROGMEM = {50,50,52,53,0};
const unsigned char Tune2[Part2_Length] PROGMEM = {40,40,42,43,0};
  
int Beat_Count = 0; // Used to index Tune array
int Note_Count = 0; // Used to index Tune array
int Graphene_Signal = 0; // Used to track conductor
int Part_Count = 0;  // Used to count through the different parts of the piece

// define I/O pins
const int ledpin = 13; // flash led
const int Graphene_Sen_P = 8; // singnal from graphine conductor, read for status low indicates star
const int Midi_In = 2;  // Software Serial Rx pin
const int Midi_Out = 3; // Software Serial Tx pin


// Timing check variables

unsigned long sr_start_time= 0;
unsigned long sr_stop_time= 0;

unsigned long min_us= 240000000;

unsigned long part_start_time= 0;
unsigned long part_tempo= 0;
unsigned long part_stop_time= 0;

unsigned char Load_Note;
unsigned char Prev_Note;


volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt CHANGED

SoftwareSerial midiSerial(2,3);

void setup() 
{
  
  // configure I/O pins
  pinMode(ledpin, OUTPUT);
  pinMode(Graphene_Sen_P, INPUT_PULLUP);
  digitalWrite(ledpin, LOW);
  digitalWrite(Graphene_Sen_P, HIGH);

  //Start Serial
   midiSerial.begin(31250);
  Serial.begin(9600);
  Serial.println("USB Serial Working!");

  Serial.print("Beat Time: ");
  Serial.println(Beat_Time);
  
  
  Start_Beat_Timer(); // Start Timer 1 with correct Tempo ADDED FIXED First Time THROUGH ISSUES !!!
  while (Next_Beat < 1)
        {
      //           Waitfor Beat Timer 
        }        
}


// --------------------------------------------------------------------------------------

void loop() 
{
// Part 1
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
      Part_Count = 0;
      Serial.print("Part_Count: ");
      Serial.println(Part_Count);
      
      digitalWrite(ledpin,HIGH); 
      Graphene_Signal = 1;
    
//      while (Graphene_Signal > 0)
//            {
//          Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
//            }
//      Graphene_Signal = 1; // debounce 1msec
      part_start_time = micros();
//      digitalWrite(ledpin, LOW);
      delayMicroseconds(1000);
//      while (Graphene_Signal > 0)
//            {
//          Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
//            }
      delay(start_delay);      
      Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
      Start_Beat_Timer(); // Start Timmer 1 with correct Tempo

      Serial.print("Notes: ");
      for (int Beat_Count=0; Beat_Count < Part_Lengths[Part_Count]; Beat_Count++)
      {   
          Load_Note = pgm_read_byte(&Tune1[Beat_Count]);
          Serial.print(Load_Note);
          Serial.print(", ");
          if (Beat_Count > 0)
          {
            Prev_Note = pgm_read_byte(&Tune1[Beat_Count-1]);
            if (Load_Note != Prev_Note)
            {
              Play_Note(128,Prev_Note,127); // Turn off previous note
//              Serial.print("Note Off: ");
//              Serial.println(Prev_Note);
            }
          }


          if (Load_Note > 0)
          {
            if (Load_Note != Prev_Note)
            {
              Play_Note(144,Load_Note,127); // Turn on note
//              Serial.print("Note On: ");
//              Serial.println(Load_Note);  
            } 
          }

          while (Next_Beat < 1)
          {
          // Waitfor Beat Timer 
          }

          Next_Beat = 0;
      }
          
      digitalWrite(ledpin,HIGH); 
      
      part_stop_time = micros();
      part_tempo = ((min_us*Part_Bars[Part_Count])/(part_stop_time-part_start_time));
      Serial.println();  
      Serial.print("Part Tempo: ");
      Serial.println(part_tempo);  
      while (Graphene_Signal < 1)
      
      {
        Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
      }
      

//  }

// Part 2
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
      Part_Count = 1;
      Serial.print("Part_Count: ");
      Serial.println(Part_Count);
      
      digitalWrite(ledpin,HIGH); 
      Graphene_Signal = 1;
    
//      while (Graphene_Signal > 0)
//            {
//          Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
//            }
//      Graphene_Signal = 1; // debounce 1msec
      part_start_time = micros();
//      digitalWrite(ledpin, LOW);
      delayMicroseconds(1000);
//      while (Graphene_Signal > 0)
//            {
//          Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
//            }
      delay(start_delay);      
      Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
      Start_Beat_Timer(); // Start Timmer 1 with correct Tempo

      Serial.print("Notes: ");
      for (int Beat_Count=0; Beat_Count < Part_Lengths[Part_Count]; Beat_Count++)
      {   
          Load_Note = pgm_read_byte(&Tune2[Beat_Count]);
          Serial.print(Load_Note);
          Serial.print(", ");
          if (Beat_Count > 0)
          {
            Prev_Note = pgm_read_byte(&Tune2[Beat_Count-1]);
            if (Load_Note != Prev_Note)
            {
              Play_Note(128,Prev_Note,127); // Turn off previous note
//              Serial.print("Note Off: ");
//              Serial.println(Prev_Note);
            }
          }


          if (Load_Note > 0)
          {
            if (Load_Note != Prev_Note)
            {
              Play_Note(144,Load_Note,127); // Turn on note
//              Serial.print("Note On: ");
//              Serial.println(Load_Note);  
            } 
          }

          while (Next_Beat < 1)
          {
          // Waitfor Beat Timer 
          }

          Next_Beat = 0;
      }
          
      digitalWrite(ledpin,HIGH); 
      
      part_stop_time = micros();
      part_tempo = ((min_us*Part_Bars[Part_Count])/(part_stop_time-part_start_time));
      Serial.println();  
      Serial.print("Part Tempo: ");
      Serial.println(part_tempo);  
      while (Graphene_Signal < 1)
      
      {
        Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene signal OFF (HIGH)
      }
      

//  }

        
  Serial.println("-----------------------------------------------------------------");
}


// --------------------------------------------------------------------------------------

void Play_Note(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd); 
  midiSerial.write(pitch);
  midiSerial.write(velocity);
}

void Start_Beat_Timer() {

//  Serial.println("StartBeatTimer"); 
//  Serial.println(Next_Beat); 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  TCNT1 = Timer1_Beat_Count;   // preload timer
  TCCR1B |= (1 << CS12);    // Sets 256 prescaler 16 uSec counts
  Timer1_Beat_Count = (65536 -(Beat_Time/16));   // preload timer 65536-(416666/16) = 39494
  interrupts();             // enable all interrupts
//  Serial.println(Next_Beat);

}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
//  Serial.println("ISR");
//  Serial.println(Next_Beat);
  TCNT1 = Timer1_Beat_Count;   // Reload timer1 with beacount
  Next_Beat= 1;
//  Serial.println(Next_Beat);
}

