/*
 * Arduino-Entry-Alert
 * 1 refers to the right PIR motion sensor
 */

 
// int ledPin = 13;                // choose the pin for the LED
int inputPin1 = 2;               // choose the first input pin (for PIR sensor)
int inputPin2 = 3;               // choose the second input pin (for PIR sensor)
int readyPin = 9;             // pin for the sound "I'm Ready"
int byePin = 8;             // pin for the sound "Goodbye for Now"
int welcomePin = 7;                 // pin for the sound "Welcome Back"
int slowdownPin = 10;                // pin for the sound "Slow Down"

volatile unsigned long int pirTime1 = 0;
volatile unsigned long int pirTime2 = 0;

void setup() {
  //pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT);     // declare sensor as input

  setupSound(slowdownPin);
  setupSound(welcomePin);
  setupSound(byePin);
  setupSound(readyPin);

  activateSound(readyPin);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), rightActivating, RISING);
  attachInterrupt(digitalPinToInterrupt(3), leftActivating, RISING);

}
 
void loop(){
  if (pirTime1 != 0  && pirTime2 != 0)
  {
    if (pirTime1 > pirTime2){ 
      Serial.println(pirTime1 - pirTime2);
      Serial.println("This was entering");
      if ((pirTime1 - pirTime2) < 100000){
        Serial.println("Too fast!");
        activateSound(slowdownPin);
        }     
      else {
           activateSound(welcomePin);
           }
      }
    else {
      Serial.println(pirTime2 - pirTime1);
      Serial.println("This was exiting");
      if ((pirTime2 - pirTime1) < 100000){
        Serial.println("Too fast!");
        activateSound(slowdownPin);
      }
      else{
        activateSound(byePin);
      }
      }

    pirTime1 = pirTime2 = 0;
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
  pirTime1 = micros();
}

void leftActivating(){
  pirTime2 = micros();
  
}