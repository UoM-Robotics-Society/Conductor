#include <SPI.h>


// define I/O pins  
const int SR_Latch_Pin = 9; // latch shift register ( Wire)
const int SR_Reset_Pin = 8; // reset shift register ( Wire)
//For SPI on UNO, MOSI - 11 ( Wire) and SCK - 13 ( Wire)

const int SR_LClK_Pin = 7;

const int SR_Length = 1;
byte SR_Note_Data[SR_Length];

// Shift Register Output patterns, Relay is activated by low signal
byte      All_OFF = B11111111;
byte      All_ON = B00000000;
byte      On_1 = B11110110;

void setup() 
{
    pinMode(SR_Latch_Pin, OUTPUT);
    pinMode(SR_Reset_Pin, OUTPUT);
    pinMode(SR_LClK_Pin, OUTPUT);
    digitalWrite(SR_Latch_Pin, LOW);
    digitalWrite(SR_Reset_Pin, HIGH);
    digitalWrite(SR_LClK_Pin, LOW);

    // Start USB Serial for monitoring
    Serial.begin(9600);   
    Serial.println("USB Working!");
    
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0)); // 100kHz Shift Clock
    
    Reset_SR(); 
    
}

void loop()
{
      //SR_Note_Data[0] = On_1;
      //SR_Note_Data[0] = All_OFF;
      //SR_Note_Data[0] = All_ON;
      //SR_Note_Data[0] = 250;


      SR_Note_Data[0] = 255;

      Serial.println(255 - SR_Note_Data[0]);
      Play_Beat();

    //delay(1000);

    //Reset_SR(); 

    //delay(1000);
    
}

// --------------------------------------------------------------------------------------


void Play_Beat() 
{
    //sr_start_time=micros();

    Load_Notes_SR();
    Set_SR();
    //sr_stop_time=micros();
    //delay(1000);
}

void Load_Notes_SR() 
{
  //digitalWrite(SR_Latch_Pin, LOW);
  for(int i=0; i < SR_Length; i++)
  {
      SPI.transfer(SR_Note_Data[i]);  
  }
}

void Set_SR() 
{
    digitalWrite(SR_LClK_Pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(SR_LClK_Pin, LOW);
}

void Reset_SR() 
{
    digitalWrite(SR_Reset_Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(SR_Reset_Pin, HIGH);

    Clear_SR_Note_Data();
    Load_Notes_SR();
    Set_SR();
}

void Clear_SR_Note_Data()
{
  for ( int i=0; i < SR_Length; i++)
  {
      SR_Note_Data[i] = All_OFF;    // clear all bits
  }
}

