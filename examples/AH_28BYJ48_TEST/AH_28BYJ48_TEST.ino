
/********************************************************
**  Downloaded from:                                   **
**  http://www.arduino-projekte.de                     **
********************************************************/

#include <AH_28BYJ48.h>

const int stepsPerRevolution = 64*64;  // number of steps per revolution * gear factor

// initialize the library 
AH_28BYJ48 myStepper(stepsPerRevolution, 4,5,6,7);    
              // pin1 blue
              // pin2 pink
              // pin3 yellow
              // pin4 orange

void setup() {
  Serial.begin(9600);
}

void loop() {
    myStepper.setSpeedHz(1000);
    myStepper.step(stepsPerRevolution);
    delay(1000);  
    
    myStepper.setSpeedRPM(10);    
    myStepper.step(-stepsPerRevolution);
    delay(1000);  
}

