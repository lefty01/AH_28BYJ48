#include <AH_28BYJ48.h>


const int stepsPerRevolution = 64 * 64;  // number of steps per revolution
					 // * gear factor
const int stepsBarrierUpDown = stepsPerRevolution / 4;

// initialize the library
AH_28BYJ48 myStepper(stepsPerRevolution,  A0, A1, A2, A3);

const long debounceDelay = 40;

// two led on pin 3 and 4
const int blink0 = 3;
const int blink1 = 4;
// push button with pull-down on pin 11
const int button2 = 11;
// toggle switch sets either one of pin 12/13 high/low ... just an example
const int sw1 = 12;
const int sw2 = 13;

bool barrier = false;
int blinkState = 0;
int prevBlinkState = 0;
const long blinkDelay = 600;
long lastBlink = 0;


void setup() {
  pinMode(blink0,  OUTPUT);
  pinMode(blink1,  OUTPUT);
  myStepper.setSpeedRPM(5);
}

void loop() {

  buttonSwitch(button2, blinkState);
  if (blinkState) {
    if ((millis() - lastBlink) > blinkDelay) {
      // toggle blink0/blink1 leds
      int blink0State = digitalRead(blink0);
     digitalWrite(blink1, blink0State);
     digitalWrite(blink0, !blink0State);
     lastBlink = millis();
    }
    prevBlinkState = blinkState;
  }
  else if (prevBlinkState) {
    digitalWrite(blink0, LOW);
    digitalWrite(blink1, LOW);
    prevBlinkState = blinkState;
  }


  int rc;
  // barrier control
  if (digitalRead(sw1)) {
    if (barrier != true) {
      //Serial.println("SCHRANKE ZU");
      rc = myStepper.step_noblock(stepsBarrierUpDown);
    }
    if (0 == rc) barrier = true;
  }
  if (digitalRead(sw2)) {
    if (barrier != false) {
      //Serial.println("SCHRANKE AUF");
      rc = myStepper.step_noblock(-stepsBarrierUpDown);
    }
    if (0 == rc) barrier = false;
  }
}

bool buttonSwitch(int n, int &state)
{
  static int buttonState;
  static int lastButtonState;
  static long lastDebounceTime;
  bool rc = false;
  int read = digitalRead(n);

  if (read != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (read != buttonState) {
      buttonState = read;

      if (buttonState == HIGH) {
	state = !state;
	rc = true;
      }
    }
  }
  lastButtonState = read;
  return rc;
}
