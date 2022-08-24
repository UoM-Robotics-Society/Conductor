#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2,3);  // Rx, Tx

const int Chord_Notes = 4;  // Number of notes to be played in each chord
const int Number_Chords = 4; // Number of different chords to play

const int Number_Parts = 3; // Number of different parts in the piece
const int Loop_Length[Number_Parts] = {2,2,2}; // Chorus, Verse2, Chorus  

const int Notes[Number_Chords][Chord_Notes] = {{53,57,60,64},{53,56,59,62},{52,55,59,62},{52,55,58,61}};   // Midi notes to be played in each chord, {{chord1},{chord2},{chord3},{chord4}}

const int LastChord_Time = 660;  // Amount of time the last Chord of each part is played for, in mS

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
          
          for (int i=0; i < Number_Chords; i++) 
          {
                
              while (digitalRead(Graphene_Pin) > 0)
              {
                ;
              }

              if (NoteOn_Flag == 1)
              {
                  for (int h=0; h < Chord_Notes; h++)
                  {
                      noteOn(128,Notes[i-1][h],127);
                      NoteOn_Flag = 0;
    
                      Serial.print("Note Off: ");
                      Serial.println(Notes[i-1][h]);
                  }
              }

              Serial.print("Chord: ");
              Serial.println(i+1);
              
              for (int h=0; h < Chord_Notes; h++)
              {
                  noteOn(144,Notes[i][h],127);
                  NoteOn_Flag = 1;        
              
                  Serial.print("Note On: ");
                  Serial.println(Notes[i][h]);
              }
              while (digitalRead(Graphene_Pin) == 0)
              {
                ;
              }
              
              delay(100);
              
              if (i == Number_Chords-1)
              {
                  delay(LastChord_Time);
                  Serial.println("Last Chord Part");
                  
                  for (int h=0; h < Chord_Notes; h++)
                  {
                      noteOn(128,Notes[i][h],127);
                      NoteOn_Flag = 0;
        
                      Serial.print("Note Off: ");
                      Serial.println(Notes[i][h]);
                  }
              }
          

//              if (i==Number_Chords-1 & j == Loop_Length[k]-1)
//              {
//                  delay(LastChord_Time);
//                  Serial.println("Last Chord Part");
//                      
//                  for (int h=0; h < Chord_Notes; h++)
//                  {
//                      noteOn(128,Notes[i][h],127);
//                      NoteOn_Flag = 0;
//        
//                      Serial.print("Note Off: ");
//                      Serial.println(Notes[i][h]);
//                  }
//              }

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

