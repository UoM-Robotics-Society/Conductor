#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2,3);

const int Tune_Length = 4;
const int Number_Parts = 4;

const int Loop_Length[Number_Parts] = {4,2,2,2}; // Verse1, Chorus, Verse2, Chorus  


//const int Notes[Tune_Length] = {16,17,14,13}; // Notes for BassGenerator
const int Notes[Tune_Length] = {40,41,38,37};   // Test Notes for Keyboard

const int LastNoteLength = 1500; // Length of last note in each loop, in mS

const int Graphene_Pin = 8;  // Input from graphene
int NoteOn_Flag = 0;   // Keep track of if there is a note playing


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  midiSerial.begin(31250);

  while (!Serial){
    ;
  }

  Serial.println("USB Working!");
  pinMode(Graphene_Pin, INPUT_PULLUP);
  digitalWrite(Graphene_Pin, HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop Function Start");

  for (int k=0; k < Number_Parts; k++)
  {    
      
      for (int j=0; j < Loop_Length[k]; j++) 
      {
          Serial.println();
          Serial.print("Part ");
          Serial.print(k+1);
          Serial.print(", Loop ");
          Serial.println(j+1);
          for (int i=0; i < Tune_Length; i++) 
          {
                
              while (digitalRead(Graphene_Pin) > 0)
              {
                ;
              }
              if (NoteOn_Flag == 1)
              {
                  noteOn(128,Notes[i-1],127);
                  NoteOn_Flag = 0;
    
                  Serial.print("Note Off: ");
                  Serial.println(Notes[i-1]);
              }
          
              noteOn(144,Notes[i],127);
              NoteOn_Flag = 1;        
              
              Serial.print("Note On: ");
              Serial.println(Notes[i]);
              while (digitalRead(Graphene_Pin) == 0)
              {
                ;
              }
              delay(100);
              
              if (i == Tune_Length-1)
              {
                  if (NoteOn_Flag == 1)
                  {
                      delay(LastNoteLength);
                      noteOn(128,Notes[i],127);
                      NoteOn_Flag = 0;
            
                      Serial.print("Note Off: ");
                      Serial.println(Notes[i]);
                  }
              }
          }
      }
      Serial.println();

  }
  Serial.println("End");
  
}

void noteOn(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd); 
  midiSerial.write(pitch);
  midiSerial.write(velocity);
}

