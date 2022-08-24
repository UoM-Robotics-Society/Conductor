#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2,3);

#define NumberofTunes 1
#define Tune1_Length 37 
#define Tune2_Length 54

const unsigned char Tune1[Tune1_Length] PROGMEM = {52,50,52,59,60,52,50,52,59,60,52,50,52,59,60,52,50,52,52,52,50,52,52,52,50,52,59,60,52,50,52,52,52,50,52,52,52};

const unsigned char Tune2[Tune2_Length] PROGMEM = {52,50,52,59,60,52,50,52,59,60,52,50,52,59,60,52,50,52,52,52,50,52,52,52,50,52,59,60,52,50,52,52,52,50,52,52,52,50,52,59,52,50,52,52,52,50,52,52,50,52,50,52,52,52};

const int Graphen_Pin = 5;  // Input from graphene


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  midiSerial.begin(31250);

  while (!Serial){
    ;
  }

  Serial.println("USB Working!");
  
  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

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
 
 Serial.println("Tune 2");
 for (int i=0; i < Tune2_Length; i++) {
    //noteOn(144,Notes[i],127);
    Serial.print(Tune2[i]);
    Serial.print(", ");
    //delay(500);
    //noteOn(128,Notes[i],0);
    //Serial.println(Notes[i]);
    //delay(500);
  }
  Serial.println("End");
}

void noteOn(int cmd, int pitch, int velocity) {
  midiSerial.write(cmd); 
  midiSerial.write(pitch);
  midiSerial.write(velocity);
}

