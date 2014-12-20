/********************************************************
**                                                     **
**  Based on Arduino Library Stepper.h                 **
**  http://www.arduino.cc/en/Tutorial/Stepper          **
**                                                     **
**  Downloaded from:                                   **
**  www.arduino-projekte.de                            **
**                                                     **
** non-blocking mode by andreas loeffler (exitzero.de) **
*********************************************************/

#ifndef AH_28BYJ48_h
#define AH_28BYJ48_h

class AH_28BYJ48 {
 public:
    // constructors:
    AH_28BYJ48(int number_of_steps,
               int motor_pin_1,
               int motor_pin_2,
               int motor_pin_3,
               int motor_pin_4);

    // speed setter method:
    void setSpeedRPM(long Speed);
    void setSpeedHz(long Speed);

    // mover method:
    void step(int number_of_steps);
    int step_noblock(int n);


 private:
    void stepMotor(int this_step);

    int direction;              // Direction of rotation
    int speed;                  // Speed in RPMs
    unsigned long step_delay;   // delay between steps, in ms, based on speed
    int number_of_steps;        // total number of steps this motor can take
    int step_number;            // which step the motor is on

    // motor pin numbers:
    int motor_pin_1;            //blue
    int motor_pin_2;            //pink
    int motor_pin_3;            //yellow
    int motor_pin_4;            //orange

    long last_step_time;        // time stamp in ms of when the last step
                                // was taken
    unsigned long last_step_us;
    unsigned long step_delay_us;
};

#endif
