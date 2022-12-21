/*
 * Arduino-Entry-Alert
 * 1 refers to the right PIR motion sensor
 */

 
int ledPin = 13;                // choose the pin for the LED
int inputPin1 = 2;               // choose the input pin (for PIR sensor)
int inputPin2 = 3;               // choose the second input pin (for PIR sensor)
int pirState1 = LOW;             // we start, assuming no motion detected
int pirState2 = LOW;
int val1 = 0;                    // variable for reading the pin status
int val2 = 0;
int workingPin = 9;             // pin for the sound "Working"
int livelongPin = 8;             // pin for the sound "Live long and prosper"
int openPin = 7;                 // pin for the opening door sound
int fastPin = 10;                // pin for when someone goes too fast
volatile int leftOn = 0;
volatile int rightOn = 0;

volatile unsigned long int pirTime1 = 0;
volatile unsigned long int pirTime2 = 0;

attachInterrupt(digitalPinToInterrupt(2), rightActivating, RISING);
attachInterrupt(digitalPinToInterrupt(3), leftActivating, RISING);



void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT);     // declare sensor as input

  setupSound(workingPin);
  //activateSound(workingPin);

  Serial.begin(9600);
  Serial.println("pretend it said working");

}
 
void loop(){
  if (pirTime1 != 0  && pirTime2 != 0)
  {
    if (pirTime1 > pirTime2){ 
      Serial.println(pirTime1 - pirTime2);
      Serial.println("This was exiting");
      }
    else {
      Serial.println(pirTime2 - pirTime1);
      Serial.println("This was entering");
      }

    // nointerrupts();
    pirTime1 = pirTime2 = 0;
    // interrupts();
  }



  /* val1 = digitalRead(inputPin1);  // read input value
  if (val1 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState1 == LOW) {
      // we have just turned on
      Serial.println("Motion detected on right sensor!");
      // We only want to print on the output change, not state
      pirState1 = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState1 == HIGH){
      // we have just turned of
      Serial.println("Motion ended on right sensor!");
      // We only want to print on the output change, not state
      pirState1 = LOW;
    }
  }

  val2 = digitalRead(inputPin2);  // read input value
  if (val2 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState2 == LOW) {
      // we have just turned on
      Serial.println("Motion detected on left sensor!");
      // We only want to print on the output change, not state
      pirState2 = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState2 == HIGH){
      // we have just turned of
      Serial.println("Motion ended on left sensor!");
      // We only want to print on the output change, not state
      pirState2 = LOW;
    }
  }

  //playsounds(); */

}

void setupSound(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Set the pin high as the default state
}

void activateSound(int pin) {
  digitalWrite(pin, LOW); // bring the pin low to begin the activation
  /*
  According to the documentation, the Audio FX board needs 50ms to trigger. However,
  I've found that coming from my 3.3v Arduino Pro, it needs 100ms to get the trigger
  the going
  */
  delay(100); // hold the pin low long enough to trigger the board; may need to be longer for consistent triggering
  digitalWrite(pin, HIGH); // bring the pin high again to end the activation
}

void rightActivating(){
  rightOn = 1;
  pirTime1 = micros();
}

void leftActivating(){
  leftOn = 1;
  pirTime2 = micros();
  
}
/* void playsounds()
{
    int state1 = digitalRead(inputPin1);
    int state2 = digitalRead(inputPin2);

    if((state1 == 1) || (state2 == 1))
    {
        if(state1 == 1)
        {
            while(state1 == 1)
            {
                state1 = digitalRead(inputPin1);
                delay(1);
                Serial.println(state1);
            }
            pirTime1 = millis();
        }
        else if(state2 == 1)
        {
            while(state2 == 1)
            {
                state2 = digitalRead(inputPin2);
                delay(1);
                Serial.println(state2);
            }
            pirTime2 = millis();
        }
    }
    if((pirTime1 != 0) && (pirTime2 != 0))
    {

        if(pirTime1 > pirTime2)
             Serial.println("Leaving");
        else if(pirTime1 < pirTime2)
             Serial.println(pirTime1);
        else
            Serial.println("pirTime1 = pirTime2; Very Rare");

        pirTime1 = 0;
        pirTime2 = 0;

        delay(100);
    }
    delay(100); 
}*/