/*     -----------------------------------------------------------
 *     | JAMES PERRIN GE102                                      |
 *     -----------------------------------------------------------
 *
 *      Written in co-operation with CrankTownCity
 *
 */



#define buttonPin 2  //make it wahatever your button is hooked to
#define motorPin 9   //whatever the motor is on
#define ledPin 13    // LED Max motor out indicator (WILL ONLY WORK IF YOU SET THE CORRECT STAGE FIVE OUTPUT VALUE SEE ***)

bool currentButton = LOW;  // True or False
bool lastButton = LOW;  // True or False
bool ledState = LOW;  // True or False

int motorSpeed = 0;  // The default motor value
int speedStep = (255 - 91) / 4;  //amount it goes up each press " I like the idea of the equation here but do what works".



void setup() {      // Stuff that we want to get run once and big in the bigger scope of things
  Serial.begin(9600);       // Useful for debugging
  pinMode(buttonPin, INPUT);   // Uhh setting pinmode to input fo the button
  pinMode(motorPin, OUTPUT);    // setting mot pin to output
  pinMode(ledPin, OUTPUT);     // LED to output
}

void loop() {               //      Our ''feel good drag'' majority of whats going on
  currentButton = digitalRead(buttonPin);          // Current set to true or false or 1 or 0 low or high based on whatever buttonPin is saying

  if (currentButton != lastButton) {            // ** so that the button doesnt double register... I think...

    Serial.println(motorSpeed);      // For my debugging purposes
    Serial.println(buttonPin);         // Same ^

    if (currentButton == HIGH) {            // The meat and potatoes of the opperation, Starts the next gear if the gear is still < 5

      if (motorSpeed <= 255) {                 // Will raise voltage if voltage on motor is still <= 255
        motorSpeed = motorSpeed + speedStep;
      }

      if (motorSpeed > 255) {          // turns off LED AND motor if motor is greater than 255 volts
        motorSpeed = 0;
        ledState = LOW;
      }
      if (motorSpeed == 41)  {
        motorSpeed = 91;            // Makes sure that the first gear actually gets the gear going since the first gear needs 91/255*5V
      }
    }
  }

  if (motorSpeed == 255) {
    ledState = HIGH;    // (***LIGHT WILL ONLY WORK IF THIS IS CORRECTLY SET; USE DEBUGGER TO SEE WHAT VALUE YOU NEED AT GEAR 5***)
  }

  digitalWrite(ledPin, ledState);        // Actually puts our values into action on the breadboard
  analogWrite(motorPin, motorSpeed);     // Puts our hypothetical nonsense into the physical realm

  lastButton = currentButton;         //  ties back to **
}
