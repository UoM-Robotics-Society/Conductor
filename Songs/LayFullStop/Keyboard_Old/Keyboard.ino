#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2,3);

#define Tune_Length 4

#define Loop1_Length 2  // Chorus
#define Loop2_Length 2  // Verse2
#define Loop3_Length 2  // Chorus

const int Note1[Tune_Length] = {53,53,52,52};
const int Note2[Tune_Length] = {57,56,55,55};
const int Note3[Tune_Length] = {60,59,59,58};
const int Note4[Tune_Length] = {64,62,62,61};


const int Graphen_Pin = 8;  // Input from graphene


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  midiSerial.begin(31250);

  while (!Serial){
    ;
  }

  Serial.println("USB Working!");
  pinMode(Graphen_Pin, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop Function Start");
  //while (digitalRead(Graphen_Pin) < 1){
    //;
  //}
  
    
  Serial.println("Tune 1");
  for (int j=0; j < Loop1_Length; j++) {
    for (int i=0; i < Tune_Length; i++) {
      while (digitalRead(Graphen_Pin) == 0){
        ;
      }
    
      //noteOn(144,Note1[i],127);
      //noteOn(144,Note2[i],127);
      //noteOn(144,Note3[i],127);
      //noteOn(144,Note4[i],127);
  
      noteOn(144,Note1[1],127);
      noteOn(144,Note2[1],127);
      noteOn(144,Note3[1],127);
      noteOn(144,Note4[1],127);
      
      Serial.print((Note1[i]));
      Serial.print(", ");
      Serial.print((Note2[i]));
      Serial.print(", ");
      Serial.print((Note3[i]));
      Serial.print(", ");
      Serial.print((Note4[i]));
      Serial.print(", ");
      delay(500);
  
      if (j == Loop1_Length){
        delay (6000);
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }
      else {      
        while (digitalRead(Graphen_Pin) < 1){
          ;
        }
        
        //noteOn(128,Note1[i],127);
        //noteOn(128,Note2[i],127);
        //noteOn(128,Note3[i],127);
        //noteOn(128,Note4[i],127);
    
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }
    }
  }
 
Serial.println("Tune 2");
  for (int j=0; j < Loop2_Length; j++) {
    for (int i=0; i < Tune_Length; i++) {
      while (digitalRead(Graphen_Pin) == 0){
        ;
      }
    
      //noteOn(144,Note1[i],127);
      //noteOn(144,Note2[i],127);
      //noteOn(144,Note3[i],127);
      //noteOn(144,Note4[i],127);
  
      noteOn(144,Note1[1],127);
      noteOn(144,Note2[1],127);
      noteOn(144,Note3[1],127);
      noteOn(144,Note4[1],127);
      
      Serial.print((Note1[i]));
      Serial.print(", ");
      Serial.print((Note2[i]));
      Serial.print(", ");
      Serial.print((Note3[i]));
      Serial.print(", ");
      Serial.print((Note4[i]));
      Serial.print(", ");
      delay(500);

      if (j == Loop2_Length){
        delay (6000);
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }
      
      else {      
        while (digitalRead(Graphen_Pin) < 1){
          ;
        }
        
        //noteOn(128,Note1[i],127);
        //noteOn(128,Note2[i],127);
        //noteOn(128,Note3[i],127);
        //noteOn(128,Note4[i],127);
    
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }  
    }
  }

  Serial.println("Tune 3");
  for (int j=0; j < Loop3_Length; j++) {
    for (int i=0; i < Tune_Length; i++) {
      while (digitalRead(Graphen_Pin) == 0){
        ;
      }
    
      //noteOn(144,Note1[i],127);
      //noteOn(144,Note2[i],127);
      //noteOn(144,Note3[i],127);
      //noteOn(144,Note4[i],127);
  
      noteOn(144,Note1[1],127);
      noteOn(144,Note2[1],127);
      noteOn(144,Note3[1],127);
      noteOn(144,Note4[1],127);
      
      Serial.print((Note1[i]));
      Serial.print(", ");
      Serial.print((Note2[i]));
      Serial.print(", ");
      Serial.print((Note3[i]));
      Serial.print(", ");
      Serial.print((Note4[i]));
      Serial.print(", ");
      delay(500);

      if (j == Loop3_Length){
        delay (6000);
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }
      else {      
        while (digitalRead(Graphen_Pin) < 1){
          ;
        }
        
        //noteOn(128,Note1[i],127);
        //noteOn(128,Note2[i],127);
        //noteOn(128,Note3[i],127);
        //noteOn(128,Note4[i],127);
    
        noteOn(128,Note1[1],127);
        noteOn(128,Note2[1],127);
        noteOn(128,Note3[1],127);
        noteOn(128,Note4[1],127);
      }
    }
  }
 
 Serial.println("End");
  
}

void noteOn(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd); 
  midiSerial.write(pitch);
  midiSerial.write(velocity);
}

