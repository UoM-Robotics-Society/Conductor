#include <SoftwareSerial.h>

// #define Tune_Length for each part

const int Number_Parts = 7; // Number of different parts within the Piece 

//const int Part_Lengths[Number_Parts] = {5,5};  
const unsigned int Part1_Length = 32;  // Length of Parts in Beats
const unsigned int Part1_NumNotes = 2; // Length of Parts in Notes
const unsigned int Part2_Length = 368;  // Length of Parts in Beats
const unsigned int Part2_NumNotes = 92; // Length of Parts in Notes
const unsigned int Part3_Length = 40;  // Length of Parts in Beats
const unsigned int Part3_NumNotes = 10; // Length of Parts in Notes
const unsigned int Part4_Length = 584;  // Length of Parts in Beats
const unsigned int Part4_NumNotes = 146; // Length of Parts in Notes
const unsigned int Part5_Length = 320;  // Length of Parts in Beats
const unsigned int Part5_NumNotes = 80; // Length of Parts in Notes
const unsigned int Part6_Length = 424;  // Length of Parts in Beats
const unsigned int Part6_NumNotes = 58; // Length of Parts in Notes
const unsigned int Part7_Length = 88;  // Length of Parts in Beats
const unsigned int Part7_NumNotes = 8; // Length of Parts in Notes

const int Part_Lengths[Number_Parts] = {Part1_Length,Part2_Length,Part3_Length,Part4_Length,Part5_Length,Part6_Length,Part7_Length};

const int Part_Bars[Number_Parts] = {1,12,1,18,10,13,3}; // Length of Parts in Bars

const unsigned int Tune1_Timing[Part1_NumNotes] PROGMEM = {0,32};
const unsigned int Tune1_Notes[Part1_NumNotes] PROGMEM = {42,0};
const unsigned int Tune2_Timing[Part2_NumNotes] PROGMEM = {0,32,32,40,40,48,48,56,56,68,68,71,72,80,80,88,88,96,96,104,104,116,116,119,120,128,128,136,136,144,144,152,152,160,160,164,164,167,168,171,172,175,176,184,184,192,192,200,200,212,212,215,216,224,224,232,232,240,240,248,248,260,260,263,264,272,272,280,280,283,284,287,288,292,292,295,296,308,308,311,312,320,320,324,324,327,328,336,336,344,344,368};
const unsigned int Tune2_Notes[Part2_NumNotes] PROGMEM = {42,0,48,0,48,0,50,0,47,0,48,0,50,0,52,0,52,0,53,0,52,0,50,0,48,0,50,0,48,0,47,0,48,0,48,0,50,0,52,0,53,0,55,0,55,0,55,0,55,0,53,0,52,0,53,0,53,0,53,0,53,0,52,0,50,0,52,0,53,0,52,0,50,0,48,0,52,0,53,0,55,0,57,0,53,0,52,0,50,0,48,0};

const unsigned int Tune3_Timing[Part3_NumNotes] PROGMEM = {0,8,8,16,16,24,24,32,32,40};
const unsigned int Tune3_Notes[Part3_NumNotes] PROGMEM = {36,0,41,0,38,0,31,0,36,0};

const unsigned int Tune4_Timing[Part4_NumNotes] PROGMEM = {0,8,8,16,16,24,24,32,32,40,40,48,48,56,56,64,64,72,72,80,80,88,88,96,96,104,104,112,112,120,120,128,128,136,136,144,144,152,152,160,160,168,168,176,176,184,184,192,192,200,200,208,208,216,216,224,224,232,232,240,240,248,248,256,256,264,264,272,272,280,280,288,288,296,296,304,304,312,312,320,320,328,328,336,336,344,344,352,352,360,360,368,368,376,376,384,384,392,392,400,400,408,408,416,416,424,424,432,432,440,440,448,448,456,456,464,464,472,472,480,480,488,488,496,496,504,504,512,512,520,520,528,528,536,536,544,544,552,552,560,560,568,568,576,576,584};
const unsigned int Tune4_Notes[Part4_NumNotes] PROGMEM = {52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,52,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,33,0,33,0,33,0,33,0,33,0,33,0,29,0,29,0,31,0,31,0,31,0,36,0,36,0,36,0,36,0,36,0,33,0,33,0,33,0,33,0,33,0,33,0,29,0,29,0,38,0,38,0,38,0,38,0,43,0,43,0,43,0,43,0,36,0,36,0,36,0,36,0,33,0,33,0,33,0,33,0,29,0,29,0,41,0,41,0,43,0,43,0,31,0,43,0,36,0};

const unsigned int Tune5_Timing[Part5_NumNotes] PROGMEM = {0,8,8,16,16,24,24,32,32,40,40,48,48,56,56,64,64,72,72,80,80,88,88,96,96,104,104,112,112,120,120,128,128,136,136,144,144,152,152,160,160,168,168,176,176,184,184,192,192,200,200,208,208,216,216,224,224,232,232,240,240,248,248,256,256,264,264,272,272,280,280,288,288,296,296,304,304,312,312,320};
const unsigned int Tune5_Notes[Part5_NumNotes] PROGMEM = {36,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,43,0,43,0,43,0,43,0,43,0,43,0,43,0,43,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,43,0,43,0,43,0,43,0,43,0,43,0,43,0,43,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0,36,0};

const unsigned int Tune6_Timing[Part6_NumNotes] PROGMEM = {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,248,256,264,272,280,288,296,304,312,320,328,336,344,352,360,368,376,384,392,392,400,400,408,408,416,416,424};
const unsigned int Tune6_Notes[Part6_NumNotes] PROGMEM = {38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,38,0,50,0,43,0,43,0,31,0,43,0,36,0};

const unsigned int Tune7_Timing[Part7_NumNotes] PROGMEM = {0,8,8,16,16,22,40,88};
const unsigned int Tune7_Notes[Part7_NumNotes] PROGMEM = {41,0,38,0,31,0,36,0};


#define Tempo 144 // Beats per minute

//const long Beat_Time = (60/Tempo)/8;
//const long Beat_Time = 500000; // 0.5 Sec
//const long Beat_Time = 10000; // 10mS
//const long Beat_Time = 1000; // 1ms
//const long Beat_Time = 52083; //
const long Beat_Time = 13204; // 32nd of a note at 142bpm

const int start_delay = 0;  // Delay before each note it played 


  
int Beat_Count = 0; // Used to index Tune array
int Array_Count = 0;  // Used to count through arrays of notes
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

unsigned int Load_Note;
unsigned int Loaded_Note;
unsigned int Load_Timing;
unsigned int Load_NextTiming;


volatile unsigned int Timer1_Beat_Count =0; // Used to set Timer 1 to correct tempo

volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt CHANGED

SoftwareSerial midiSerial(2,3); // Rx, Tx

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

  Serial.println("Part 1 Notes");
  for (int i=0; i<Part1_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune1_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune1_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 2 Notes");
  for (int i=0; i<Part2_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune2_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune2_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 3 Notes");
  for (int i=0; i<Part3_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune3_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune3_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 4 Notes");
  for (int i=0; i<Part4_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune4_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune4_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 5 Notes");
  for (int i=0; i<Part5_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune5_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune5_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 6 Notes");
  for (int i=0; i<Part6_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune6_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune6_Notes[i]));
    Serial.println();
  }
  Serial.println();

  Serial.println("Part 7 Notes");
  for (int i=0; i<Part7_NumNotes;i++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pgm_read_word(&Tune7_Timing[i]));
    Serial.print(", ");
    Serial.print(pgm_read_word(&Tune7_Notes[i]));
    Serial.println();
  }
  Serial.println();

 
  
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
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune1_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune1_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune1_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Load_Note = pgm_read_word(&Tune1_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    
    

// Part 2
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 1;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune2_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune2_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune2_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune2_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

// Part 3
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 2;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune3_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune3_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune3_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune3_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

// Part 4
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 3;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune4_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune4_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune4_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune4_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

// Part 5
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 4;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune5_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune5_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune5_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune5_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

// Part 6
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 5;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune6_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune6_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune6_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune6_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

// Part 7
//    for (int Part_Count; Part_Count < Number_Parts; Part_Count++)
//    {
          Part_Count = 6;
          Serial.print("Part_Count: ");
          Serial.println(Part_Count+1);
          
          digitalWrite(ledpin,HIGH); 
          Graphene_Signal = 1;
        
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON (LOW)
          }
          Graphene_Signal = 1; // debounce 1msec
          part_start_time = micros();
          digitalWrite(ledpin, LOW);
          delayMicroseconds(1000);
          while (Graphene_Signal > 0)
          {
              Graphene_Signal = digitalRead(Graphene_Sen_P); //  Wait for Graphene  ON
          }
          delay(start_delay);      
          Next_Beat = 0; // Reset Flag ADDED keep here as interupt can change it
          Start_Beat_Timer(); // Start Timmer 1 with correct Tempo
    
          Array_Count=0;
//           Serial.print("Notes: ");
          for (int Beat_Count=0; Beat_Count <= Part_Lengths[Part_Count]; Beat_Count++)
          {       
              Serial.print("Beat_Count: ");
              Serial.print(Beat_Count);
              Serial.print(", Array_Count: ");
              Serial.print(Array_Count);
    
              Load_Timing = pgm_read_word(&Tune7_Timing[Array_Count]);
              Serial.print(", Load_Timing: ");
              Serial.print(Load_Timing);
             
              if (Load_Timing == Beat_Count)
              {
                  Load_Note = pgm_read_word(&Tune7_Notes[Array_Count]);
                  Serial.print(", Load_Notes: ");
                  Serial.print(Load_Note);
    //              Serial.print(", ");
    
                  if (Load_Note == 0)
                  {
                      Play_Note(128,Loaded_Note,127); // Turn off note
                      Serial.print(", Note Off: ");
                      Serial.print(Loaded_Note);
          
                      Load_NextTiming = pgm_read_word(&Tune7_Timing[Array_Count+1]);
                      Serial.print(", Load_NextTiming: ");
                      Serial.print(Load_NextTiming);
                      if (Load_Timing = Load_NextTiming)
                      {
                          Array_Count+=1;
                          Serial.print(", Array_Count: ");
                          Serial.print(Array_Count);
                          Load_Note = pgm_read_word(&Tune7_Notes[Array_Count]);
                          Loaded_Note = Load_Note;
                          Serial.print(", Load_Notes: ");
                          Serial.print(Load_Note);
                          Play_Note(144,Loaded_Note,127); // Turn on note
                          Serial.print(", Note On: ");
                          Serial.println(Loaded_Note);
                          Array_Count+=1;
                      }
                  }
                  else
                  {
                      Loaded_Note = Load_Note;
                      Serial.print(", Load_Notes: ");
                      Serial.print(Load_Note);
                      Play_Note(144,Loaded_Note,127); // Turn on note
                      Serial.print(", Note On: ");
                      Serial.println(Loaded_Note);
                      Array_Count+=1;
                  }            
              }
              
              while (Next_Beat < 1)
              {
                // Waitfor Beat Timer 
              }
    
              Next_Beat = 0;
              Serial.println();
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
          
          Serial.println("-----------------------------------------------------------------");
//    {    

    
        
  Serial.println("-----------------------------------------------------------------");
}


// --------------------------------------------------------------------------------------

void Play_Note(int cmd, int pitch, int velocity) {

  int temp_pitch;
  int transpose = 0;
  
  switch(pitch)
  {
    case 29:
      temp_pitch = pitch - transpose;
      break;
    case 31:
      temp_pitch = pitch - transpose;
      break;
    case 33:
      temp_pitch = pitch - transpose;
      break;
    case 36:
      temp_pitch = pitch - transpose;
      break;
    case 38:
      temp_pitch = pitch - transpose;
      break;
    case 41:
      temp_pitch = pitch - transpose;
      break;
    case 42:
      temp_pitch = pitch - transpose;
      break;
    case 43:
      temp_pitch = pitch - transpose;
      break;
    case 47:
      temp_pitch = pitch - transpose;
      break;
    case 48:
      temp_pitch = pitch - transpose;
      break;
    case 50:
      temp_pitch = pitch - transpose;
      break;
    case 52:
      temp_pitch = pitch - transpose;
      break;
    case 53:
      temp_pitch = pitch - transpose;
      break;
    case 55:
      temp_pitch = pitch - transpose;
      break;
    case 57:
      temp_pitch = pitch - transpose;
      break;
  }
  
  midiSerial.write(cmd); 
//  midiSerial.write(pitch);
  midiSerial.write(temp_pitch);
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

