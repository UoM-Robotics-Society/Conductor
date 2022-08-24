/*
   violinobot code - version Graphene_controls_sequences.0.2

   8 fans play the two outer strings on 4 violins
   8 fans are on Arduino outputs D6 to D13


   sequences of notes ('Tune_') are stored in arrays, along with the length of each
   Tune_ array, the number of times to repeat the Tune_, and the tempo

   for each beat, any number of notes can be played, i.e. any number of fans can
   be switched on

   the fans are switched on for the duration of one beat


   a switch signel, active LOW, is connected to pin D2 - a mechanical
   push switch for testing (internal pull-up is used, no external resistor needed),
   a relay steered by a control computer called Graphene for operation -
   and this triggers playing an entire sequence = Tune_


   a beat timer / counter (timer 1) keeps accurate timing, and
   beat / note playing is synchronised to this timer


   Noisy Toys, teddytronix, 2016
   based on glockobot sample code, 2016
   creative-commons share-alike license
*/

// debugging switch - comment out for operation
//#define DEBUG

// debugging macros - will be ignored by compiler when previous line is commented out
#ifdef DEBUG
#define DEBUG_P(x)     Serial.print(x)          // print, no newline
#define DEBUG_PN(x)    Serial.println(x, DEC)   // print number with newline - use for values
#define DEBUG_PL(x)    Serial.println(x)        // print line with newline
#else
#define DEBUG_P(x)
#define DEBUG_PN(x)
#define DEBUG_PL(x)
#endif


// timer
//
// can change the speed by preloading timer1 with different values
// lower value for faster tempo as irq's occur faster
//
// TODO where is the limit??
//
unsigned long Tempo1 = 96;
unsigned long Beat_Time =  60000000ul / Tempo1;
//
// counters thru the tunes
volatile unsigned long Timer1_Beat_Count = 0; // Used to set Timer 1 to correct tempo
// flag sync'ing us to timer 1
volatile unsigned int Next_Beat = 0; // Flag to move to next beat, set by Timer 1 Interrupt CHANGED


// tunes
//
// arrays with note data i.e. which fans to switch on next
// the sequences are triggered by Graphene controller
//
// Fan7-128, Fan6-64, Fan5-32, Fan4-16, Fan3-8, Fan2-4, Fan1-2, Fan0-1 

// length of tune
#define Tune1_Length 24

const unsigned char Tune1[Tune1_Length] PROGMEM = 
  //{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,8,8,8,8};
  //{1,2,4,8,16,32,64,128};
  //{1,1,2,2,2,2,2,2,2,2,4,8};
  {3,3,12,12,12,12,12,12,12,12,48,192,3,3,12,12,12,12,12,12,12,12,48,192};
  
// repeats this many times
const int Tune1_Repeats = 1;

#define Tune2_Length 8
unsigned long Tempo2 = 96;
const unsigned char Tune2[Tune2_Length] PROGMEM = 
  {1,1,2,2,2,2,4,8};
const int Tune2_Repeats = 1;

#define Tune3_Length 189   // was Tune1 in sample code
unsigned long Tempo3 = 300;
const unsigned char Tune3[Tune3_Length] PROGMEM = {154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 154, 0, 0, 0, 161, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int Tune3_Repeats = 1;

// this many tunes
const int tunes_max = 1;

// tune variables
//int Step_Count = 0;                       // used to index Tune array
int tune = 1;                               // counter - which tune?
const unsigned char *Tune_Pointer = Tune1;  // pointer to current array of notes
int Tune_Length = Tune1_Length;                        // length of tune = length of array
int Repeats_This_Tune = Tune1_Repeats;      // repeat tune?

// inputs
//
// Graphene
//
const int Graphene_Sense_Pin = 2;   // Graphene conductor signal sense, active LOW
int Graphene_Signal = 1;        // used to track conductor
//
// momentary switches - tune the fiddles using these
//
const int momentarySwitchPin[8] = { 19, 18, 17, 16 , 15, 14, 5, 4 };
int momentarySwitch[8] = { };
//
// two positon switch - selector
// switches on and off the tuning switches
//
const int selectSwitchPin = 3;


// outputs
//
// fans
//
// make fan status more readable
#define ON  HIGH
#define OFF LOW
//
// 8 notes from 8 fans on eight outputs
const int fanPin[8] = { 6, 7, 8, 9, 10, 11, 12, 13 };
int fan[8] = { OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF };
//
// which note to play = combination of fans
unsigned char Load_Note;



void setup()
{
  // debug
#ifdef DEBUG
  Serial.begin(38400);
  Serial.println("teddytronix");
  delay(2);
#endif

  // configure I/O pins
  pinMode(Graphene_Sense_Pin, INPUT_PULLUP);
  pinMode(selectSwitchPin, INPUT_PULLUP);
  for (int i = 0; i < 8; i++ )
  {
    pinMode(momentarySwitchPin[i], INPUT_PULLUP);
    momentarySwitch[i] = digitalRead(momentarySwitchPin[i]);
  }
  
  // eight fans, switch them off
  for (int i = 0; i < 8; i++ )
  {
    pinMode(fanPin[i], OUTPUT);
    digitalWrite(fanPin[i], fan[i]);
  }

  // start Timer 1
  Start_Beat_Timer();

  // it is the Next_beat variable that gets set in the irq
  // service routine
  // i.e. this is what synchronises us to Timer1
  while (Next_Beat < 1)
  {
    ;// Wait for Beat Timer
    DEBUG_P(".");
  }

  DEBUG_PL();
  DEBUG_PL("setup DONE");
}

void loop()
{
  // ensure signal is in 'reset' state
  Graphene_Signal = 1;


  // set up playing tune by setting tune variables
  if ( tune == 1 )
  {
    // use a pointer to address the array
    Tune_Pointer = Tune1;
    // length to control loop
    Tune_Length = Tune1_Length;
    // repeats for repeat loop
    Repeats_This_Tune = Tune1_Repeats;
    // set tempo by adjusting timer1 preload value
    Beat_Time =  60000000ul / Tempo1;
    // debug info
    DEBUG_PL("tune 1");
  }
  else if ( tune == 2 )
  {
    Tune_Pointer = Tune2;
    Tune_Length = Tune2_Length;
    Repeats_This_Tune = Tune2_Repeats;
    Beat_Time =  60000000ul / Tempo2;
    DEBUG_PL("tune 2");
  }
  else if ( tune == 3 )
  {
    Tune_Pointer = Tune3;
    Tune_Length = Tune3_Length;
    Repeats_This_Tune = Tune3_Repeats;
    Beat_Time =  60000000ul / Tempo3;
    DEBUG_PL("tune 3");
  }
  else
  {
    ;// error: should never be here
    DEBUG_P("error: 'tune' select out-of-range");
    // TODO handle error
    //                  while(1) ? reset tune??
  }


  // wait until graphene signal is 'set' = active
  while (Graphene_Signal > 0)
  {
    Graphene_Signal = digitalRead(Graphene_Sense_Pin); //  wait for Graphene ON (active LOW)


    // check to see if we are tuning - rem. is active LOW
    if ( digitalRead(selectSwitchPin) < 1 )
    {
      // read the switches
      for (int i = 0; i < 8; i++ )
      {
        // store switch state
        momentarySwitch[i] = digitalRead(momentarySwitchPin[i]);
        // switches are negative logic (active LOW) so:
        // invert then store in fan array
        fan[i] = !momentarySwitch[i];
        // and activate
        digitalWrite(fanPin[i], fan[i]);
#ifdef DEBUG
        // feedback while debugging
        if (i < 1) DEBUG_PL("select");
        delay(2);
#endif
      }
    }
  }
    Graphene_Signal = 1;   // debounce 1msec
  delayMicroseconds(1000);
  while (Graphene_Signal > 0)
  {
    Graphene_Signal = digitalRead(Graphene_Sense_Pin); //  Wait for Graphene  ON
  }

  Next_Beat = 0;      // reset flag here as interrupt can change it
  Start_Beat_Timer(); // start timer1 with correct Tempo

  // do we repeat this Tune_
  for (int Tune_Repeat_Count = 0; Tune_Repeat_Count < Repeats_This_Tune; Tune_Repeat_Count++)
  {
    // Beat_Count'ing from 0 to Tune1_Length i.e. thru the tune
    for (int Beat_Count = 0; Beat_Count < Tune_Length; Beat_Count++)
    {
      // read note (from program memory),
      // this is where we need the pointer
      Load_Note = pgm_read_byte(&Tune_Pointer[Beat_Count]);

      // extract which fans to switch on from note data
      Fans_From_Note(Load_Note);

      // play note = activate fans
      Play_Note();

      while (Next_Beat < 1)
      {
        ;// wait for beat sync i.e. next beat interrupt
      }

      // reset fans
      Fans_Off();
      // reset beat flag
      Next_Beat = 0;

    }  // for (int Beat_Count = 0; Beat_Count < Tune1_Length; Beat_Count++) DONE

    DEBUG_PL("\t\tfor");

  }  // for (int Tune_Repeat_Count = 0; Tune_Repeat_Count < Tune1_Repeats; Tune_Repeat_Count++) DONE

  // tune is done so get ready for next one ...
  tune++;
  // ... unless all tunes have been played
  if (tune > tunes_max) tune = 1;  // back to start TODO correct? or stop?? TODO

  // if the external signal is still 'active (= LOW)' then wait here
  while (Graphene_Signal < 1)
  {
    Graphene_Signal = digitalRead(Graphene_Sense_Pin); //  wait for Graphene signal OFF (= HIGH)
  }

}  //  loop() DONE


// set fan array depending on note value
void Fans_From_Note(unsigned char Load_Note)
{
  // extract which fans to switch on
  if (Load_Note >= 128)
  {
    // fan 8 - rem array index starts from 0
    fan[7] = ON;
    Load_Note = Load_Note - 128;
  }
  if (Load_Note >= 64)
  {
    // fan 7 - rem array index starts from 0
    fan[6] = ON;
    Load_Note = Load_Note - 64;
  }
  if (Load_Note >= 32)
  {
    // fan 6 - rem array index starts from 0
    fan[5] = ON;
    Load_Note = Load_Note - 32;
  }
  if (Load_Note >= 16)
  {
    // fan 5 - rem array index starts from 0
    fan[4] = ON;
    Load_Note = Load_Note - 16;
  }
  if (Load_Note >= 8)
  {
    // fan 4 - rem array index starts from 0
    fan[3] = ON;
    Load_Note = Load_Note - 8;
  }
  if (Load_Note >= 4)
  {
    // fan 3 - rem array index starts from 0
    fan[2] = ON;
    Load_Note = Load_Note - 4;
  }
  if (Load_Note >= 2)
  {
    // fan 2 - rem array index starts from 0
    fan[1] = ON;
    Load_Note = Load_Note - 2;
  }
  if (Load_Note >= 1)
  {
    // fan 1 - rem array index starts from 0
    fan[0] = ON;
    Load_Note = Load_Note - 1;
  }
  if (Load_Note > 0)
  {
    ;// this should never happen here
    DEBUG_PL("error: Load_Note to fan translation failed");
  }
}

// activate fans
void Play_Note(void)
{
  // cycle thru fans array and set accordingly
  for (int i = 0; i < 8; i++ )
  {
    digitalWrite( fanPin[i], fan[i] );
  }
  DEBUG_PL("play");
}

// all fans off together
void Fans_Off(void)
{
  // fans off, clear fan array
  for (int i = 0; i < 8; i++ )
  {
    fan[i] = OFF;
    digitalWrite( fanPin[i], OFF );
  }
  DEBUG_PL("OFF");
}

// setup, preload and start timer 1
void Start_Beat_Timer()
{
  // set up timer 1 (the 16-bit timer) for overflow interrupt

  noInterrupts();              // disable all interrupts

  // TCCRx - Timer/Counter Control Register - the prescaler can be configured here
  TCCR1A = 0;                  // set entire TCCR1A register to 0
  TCCR1B = 0;                  // same for TCCR1B

  // TIMSKx - Timer/Counter Interrupt Mask Register - to enable/disable timer interrupts
  //
  // When the timer overflow interrupt enable bit TOIEx in the interrupt
  // mask register TIMSKx is set, the timer overflow interrupt service
  // routine ISR(TIMERx_OVF_vect) will be called.
  TIMSK1 |= (1 << TOIE1);      // enable timer overflow interrupt

  // TCNTx - Timer/Counter Register - the actual timer value is stored here
  TCNT1 = Timer1_Beat_Count;   // preload timer

  // TCCRx - Timer/Counter Control Register - the prescaler can be configured here
  // 1 into CS12, 0 in CS11 and CS10 (from above 'set ... register to 0')
  TCCR1B |= (1 << CS12);       // sets 256 prescaler 16 uSec counts

  //Timer1_Beat_Count = (65536 - (Beat_Time / 16)); // preload timer 65536-(416666/16) = 39494
  //ted test
  Timer1_Beat_Count = (65536 - (Beat_Time / 32)); // preload timer 65536-(416666/16) = 39494

  interrupts();                // enable all interrupts

  DEBUG_P("\tT1BtCnt ");
  DEBUG_PN(Timer1_Beat_Count);
}

/*
   Timer Overflow:

   Timer overflow means the timer has reached its limit value.

   When a timer overflow interrupt occurs, the timer overflow bit
   TOVx will be set in the interrupt flag register TIFRx.

   When the timer overflow interrupt enable bit TOIEx in the interrupt
   mask register TIMSKx is set, the timer overflow interrupt service
   routine ISR(TIMERx_OVF_vect) will be called.
*/
ISR(TIMER1_OVF_vect)        // interrupt service routine
{
  TCNT1 = Timer1_Beat_Count;   // Reload timer1 with beat count
  Next_Beat = 1;
}


/*
   timer info

   For 16MHz:

  Prescale  Time per    Max Period
         counter tick

     1      0.0625 uS      8.192 mS
     8      0.5 uS        65.536 mS
    64      4 uS         524.288 mS
   256     16 uS       2097.152 mS
  1024     64 uS       8388.608 mS

  In general:

    Max Period = ( Prescale ) * ( 1 / Frequency ) * ( 2^17 )

    Time per Tick = ( Prescale ) * ( 1 / Frequency )
*/
