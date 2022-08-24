#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2,3);

#define Tune1_Length 10

const unsigned char Tune1[Tune1_Length] PROGMEM = {50,50,50,50,50,50,50,50,50,50};

const int Graphen_Pin = 5;  // Input from graphene


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

  while (digitalRead(Graphen_Pin) < 1){
    ;
  }
    
  Serial.println("Tune 1");
  for (int i=0; i < Tune1_Length; i++) {
    //noteOn(144,Notes[i],127);
    Serial.print(Tune1[i]);
    Serial.print(", ");
    //delay(500);
    //noteOn(128,Notes[i],0);
    //Serial.println(Notes[i]);
    //delay(500);
  }
 Serial.println("End");

 while (digitalRead(Graphen_Pin) < 1){
    ;
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd); 
  midiSerial.write(pitch);
  midiSerial.write(velocity);
}

