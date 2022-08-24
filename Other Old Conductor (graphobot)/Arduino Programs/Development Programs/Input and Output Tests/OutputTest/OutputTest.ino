
const int OuputPin = 5;

void setup()
{
    Serial.begin(9600);   
    Serial.println("USB Working!");
    
    pinMode(OuputPin, OUTPUT);
    digitalWrite(OuputPin, LOW);
    Serial.println("Output Low");
}

void loop() 
{
    digitalWrite(OuputPin, HIGH);
    Serial.println("Output High");
    delay(5000);
    
    digitalWrite(OuputPin, LOW);
    Serial.println("Output Low");
    delay(5000);
}
