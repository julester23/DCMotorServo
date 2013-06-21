/* Encoder Library, for measuring quadrature encoded signals
 * http://www.pjrc.com/teensy/td_libs_Encoder.html*/
#include <Encoder.h>
#include <PID_v1.h>

/*
This library uses PID and Encoder feedback to control a DC motor. It is modeled a little bit after the AccelStepper library.

HOOKUP:
I used a 754410 quad half-H controller (a pin-compatible L293D). I'm sure it would be cheaper to make out of other components, but i've never done transistor matching, and i'm afraid of burning things.

Example PINMAP:
754410
1&9       pin_pwm_output
2&15      pin_dir
7&10      pin_dir
4&5&12&13 GND
16        5V
8         12V

3&14      motor pin 1
6&11      motor pin 2

HARDWARE:
Metal Gearmotor 37Dx57L mm with 64 CPR Encoder from www.pololu.com
Arduino
754410

PINS:
Pinout for motor control uses 3 pins for output. It is somewhat wasteful, but had more flexibility. Two pins for direction control, and one for motor power (assuming PWM).
Be sure to pick a PWM capable pin for pin_pwm_output.

The two input pins are for the encoder feedback.

Two direcional pins allow for setting a motor brake by shorting the terminals of the motor together (set both directions HIGH, and preferably turn off the PWM)

TODO:
implement brake feature for 3-pin mode
2-pin constructor
implement friendlier tuning method for PID
*/


class DCMotorServo {
public:
  DCMotorServo(uint8_t pin_dir_1 = 4, uint8_t pin_dir_2 = 5, uint8_t pin_pwm_output = 6, uint8_t pin_encode1 = 2, uint8_t pin_encode2 = 3);
  PID * myPID;
  void run();
  void stop();
  void move(int new_rela_position);
  void moveTo(int new_position);
  int getRequestedPosition();
  int getActualPosition();
  bool finished();
  bool setPWMSkip(uint8_t);
  void setAccuracy(unsigned int);
  void setCurrentPosition(int);
private:
  uint8_t _pin_PWM_output, _pin_dir_1, _pin_dir_2;
  double _PID_setpoint, _PID_input, _PID_output;
  uint8_t _PWM_output;
  
  Encoder * _position;
  uint8_t _pwm_skip;            //The range of PWM to skip (for me, I set it to 50 because duty-cycles under 50/255 are not enough to surpass motor and gearing frictions)
  uint8_t _position_accuracy;   //Set to the highest tolerable inaccuracy (units are encoder counts)
  void _pick_direction();
};
