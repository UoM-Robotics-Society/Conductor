#include <SPI.h>


// define I/O pins  
const int SR_Latch_Pin = 49; // latch shift register ( Wire)
const int SR_Reset_Pin = 47; // reset shift register ( Wire)
const int SR_LClK_Pin = 48;

//For SPI on UNO, Reset - 8, Latch - 9, MOSI - 11 and SCK - 13 and LClk - 7
//For SPI on MEGA, Reset - 47, Latch - 49, MOSI - 51 and SCK - 52 and LClk - 48

// define Shift Register Length
const int SR_Number = 2;  // Number of shift register boards
const int SR_Length = 8;  // Length of each shift register 

byte SR_Note_Data[SR_Number];

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


      SR_Note_Data[0] = 253;
      SR_Note_Data[1] = 251;
      
      Serial.println(255 - SR_Note_Data[0]);
      
      Play_Beat();

    //delay(1000);

    //Reset_SR(); 

    //delay(1000);
    
}

// --------------------------------------------------------------------------------------


void Play_Beat() 
{
    Load_Notes_SR();
    Set_SR();
    Clear_SR_Note_Data();
}

void Load_Notes_SR() 
{
  for(int i=0; i < SR_Number; i++)
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
  for ( int i=0; i < SR_Number; i++)
  {
      SR_Note_Data[i] = All_OFF;    // clear all bits
  }
}

