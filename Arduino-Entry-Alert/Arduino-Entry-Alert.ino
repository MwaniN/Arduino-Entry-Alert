/*
 * Arduino-Entry-Alert
 * 1 refers to the right PIR motion sensor
 */

 
// int ledPin = 13;                // choose the pin for the LED
int inputPin1 = 2;               // choose the first input pin (for PIR sensor)
int inputPin2 = 3;               // choose the second input pin (for PIR sensor)
int workingPin = 9;             // pin for the sound "Working"
int livelongPin = 8;             // pin for the sound "Live long and prosper"
int openPin = 7;                 // pin for the opening door sound
int fastPin = 10;                // pin for when someone goes too fast
volatile int leftOn = 0;
volatile int rightOn = 0;

volatile unsigned long int pirTime1 = 0;
volatile unsigned long int pirTime2 = 0;

void setup() {
  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT);     // declare sensor as input

  setupSound(workingPin);
  //activateSound(workingPin);

  Serial.begin(9600);
  Serial.println("pretend it said working");
  attachInterrupt(digitalPinToInterrupt(2), rightActivating, RISING);
  attachInterrupt(digitalPinToInterrupt(3), leftActivating, RISING);

}
 
void loop(){
  if (pirTime1 != 0  && pirTime2 != 0)
  {
    if (pirTime1 > pirTime2){ 
      Serial.println(pirTime1);
      Serial.println(pirTime2);
      Serial.println(pirTime1 - pirTime2);
      Serial.println("This was entering");
      }
    else {
      Serial.println(pirTime2 - pirTime1);
      Serial.println("This was exiting");
      }

    // nointerrupts();
    pirTime1 = pirTime2 = 0;
    // interrupts();
  }

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