/*************************************************
**						**
**  Based on Arduino Library Stepper.h		**
**  http://www.arduino.cc/en/Tutorial/Stepper	**
**						**
**  Downloaded from:				**
**  www.arduino-projekte.de			**
**						**
*************************************************/


#include "Arduino.h"
#include "AH_28BYJ48.h"



AH_28BYJ48::AH_28BYJ48(int number_of_steps, int motor_pin_1, int motor_pin_2,
		       int motor_pin_3, int motor_pin_4)
{
  this->step_number = 0;	// which step the motor is on
  this->speed = 0;		// the motor speed, in revolutions per minute
  this->direction = 0;		// motor direction
  this->last_step_time = 0;	// time stamp in ms of the last step taken
  this->last_step_us = 0;	// time stamp in us of the last step taken
  this->number_of_steps = number_of_steps; // total number of steps for this motor

  // Arduino pins for the motor control connection:
  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->motor_pin_3 = motor_pin_3;
  this->motor_pin_4 = motor_pin_4;

  // setup the pins on the microcontroller:
  pinMode(this->motor_pin_1, OUTPUT);
  pinMode(this->motor_pin_2, OUTPUT);
  pinMode(this->motor_pin_3, OUTPUT);
  pinMode(this->motor_pin_4, OUTPUT);

}

//*****************************************************************************

void AH_28BYJ48::setSpeedRPM(long Speed)
{
  this->step_delay = 60L * 1000L / this->number_of_steps / Speed;
  this->step_delay_us = step_delay * 1000;
}

//*****************************************************************************

void AH_28BYJ48::setSpeedHz(long Speed)
{
  this->step_delay = 1000/Speed;
  this->step_delay_us = step_delay * 1000;
}

//*****************************************************************************

void AH_28BYJ48::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take

  if (steps_to_move > 0) {this->direction = 1;}
  if (steps_to_move < 0) {this->direction = 0;}

  while(steps_left > 0) {

  if (millis() - this->last_step_time >= this->step_delay) {

      this->last_step_time = millis();

      if (this->direction == 1) {
	this->step_number++;
	if (this->step_number == this->number_of_steps) {
	  this->step_number = 0;
	}
      }
      else {
	if (this->step_number == 0) {
	  this->step_number = this->number_of_steps;
	}
	this->step_number--;
      }

      steps_left--;
      stepMotor(this->step_number % 8);
    }
  }
}

int AH_28BYJ48::step_noblock(int do_steps)
{
  static int steps_left = 0;

  if (0 == steps_left) {
    steps_left = abs(do_steps);
    this->direction = (do_steps > 0) ? 1 : 0;
  }

  if (micros() - this->last_step_us >= this->step_delay_us) {

    this->last_step_us = micros();

    if (this->direction == 1) {
      this->step_number++;

      if (this->step_number == this->number_of_steps) {
	this->step_number = 0;
      }
    }
    else {
      if (this->step_number == 0) {
	this->step_number = this->number_of_steps;
      }
      this->step_number--;
    }
    steps_left--;
    stepMotor(this->step_number % 8);
  }
  return steps_left;
}


//*****************************************************************************

void AH_28BYJ48::stepMotor(int thisStep)
{
    switch (thisStep) {
    case 0:
      digitalWrite(motor_pin_1, LOW);  //BLU
      digitalWrite(motor_pin_2, LOW);  //Pink
      digitalWrite(motor_pin_3, LOW);  //Yellow
      digitalWrite(motor_pin_4, HIGH); //Orange
      break;
    case 1:
      digitalWrite(motor_pin_1, LOW);  //BLU
      digitalWrite(motor_pin_2, LOW);  //Pink
      digitalWrite(motor_pin_3, HIGH); //Yellow
      digitalWrite(motor_pin_4, HIGH); //Orange
      break;
    case 2:
      digitalWrite(motor_pin_1, LOW);  //BLU
      digitalWrite(motor_pin_2, LOW);  //Pink
      digitalWrite(motor_pin_3, HIGH); //Yellow
      digitalWrite(motor_pin_4, LOW);  //Orange
      break;
    case 3:
      digitalWrite(motor_pin_1, LOW);  //BLU
      digitalWrite(motor_pin_2, HIGH); //Pink
      digitalWrite(motor_pin_3, HIGH); //Yellow
      digitalWrite(motor_pin_4, LOW);  //Orange
      break;
    case 4:
      digitalWrite(motor_pin_1, LOW);  //BLU
      digitalWrite(motor_pin_2, HIGH); //Pink
      digitalWrite(motor_pin_3, LOW);  //Yellow
      digitalWrite(motor_pin_4, LOW);  //Orange
      break;
    case 5:
      digitalWrite(motor_pin_1, HIGH);  //BLU
      digitalWrite(motor_pin_2, HIGH);  //Pink
      digitalWrite(motor_pin_3, LOW);   //Yellow
      digitalWrite(motor_pin_4, LOW);   //Orange
      break;
    case 6:
      digitalWrite(motor_pin_1, HIGH);  //BLU
      digitalWrite(motor_pin_2, LOW);  //Pink
      digitalWrite(motor_pin_3, LOW);  //Yellow
      digitalWrite(motor_pin_4, LOW);  //Orange
      break;
    case 7:
      digitalWrite(motor_pin_1, HIGH); //BLU
      digitalWrite(motor_pin_2, LOW);  //Pink
      digitalWrite(motor_pin_3, LOW);  //Yellow
      digitalWrite(motor_pin_4, HIGH); //Orange
      break;
    }
}

//*****************************************************************************
