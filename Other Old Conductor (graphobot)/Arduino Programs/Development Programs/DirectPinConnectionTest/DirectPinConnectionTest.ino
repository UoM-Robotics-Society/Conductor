const int On_Button = 5; // singnal from graphine conductor, set low with output pin
const int Instrument = 8; // singnal from graphine conductor, set low with output pin
int On_Signal;


void setup() {
  // put your setup code here, to run once:
  pinMode(On_Button, INPUT_PULLUP);
  pinMode(Instrument, OUTPUT);

  digitalWrite(On_Button, HIGH);
  digitalWrite(Instrument, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly:
    On_Signal = 1;
    while (On_Signal > 0)
    {
        On_Signal = digitalRead(On_Button); //  Wait for On Button to be pressed    
    }
    digitalWrite(Instrument, HIGH);
    delay(5000);
    digitalWrite(Instrument, LOW);

}
