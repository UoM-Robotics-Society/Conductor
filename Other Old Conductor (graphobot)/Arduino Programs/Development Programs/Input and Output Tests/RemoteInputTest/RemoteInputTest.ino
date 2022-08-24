
const int InputPin = 13;

void setup()
{
    Serial.begin(9600);   
    Serial.println("USB Working!");
    
    pinMode(InputPin, INPUT);
    //digitalWrite(OuputPin, LOW);
    //Serial.println("Output Low");
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
}
