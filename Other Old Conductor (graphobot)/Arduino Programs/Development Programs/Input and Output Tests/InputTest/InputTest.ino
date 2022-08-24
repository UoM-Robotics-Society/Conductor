
const int InputPin = 8;

void setup()
{
    
    pinMode(InputPin, INPUT);
    digitalWrite(InputPin, HIGH);
    
    Serial.begin(9600);   
    Serial.println("USB Working!");

}

void loop() 
{
    if (digitalRead(InputPin) == 0)
    {
        Serial.println("Input Low");
    }
    
    if (digitalRead(InputPin) == 1)
    {
        Serial.println("Input High");
    }
    
    delay(1000);
}
