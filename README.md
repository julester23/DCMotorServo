DCMotorServo
============

An Arduino Library for controlling DC motors with rotary encoders. This library uses PID and Encoder feedback. It is modeled a little bit after the AccelStepper library.

Encoder Library, for measuring quadrature encoded signals from http://www.pjrc.com/teensy/td_libs_Encoder.html
PID Library, for using encoder feedback to controll the motor from http://playground.arduino.cc/Code/PIDLibrary

HOOKUP
------
I used a 754410 quad half-H controller (a pin-compatible L293D). I'm sure it would be cheaper to make out of other components, but i've never done transistor matching, and i'm afraid of burning things.

### Example PINMAP
754410
1&9       pin_pwm_output  
2&15      pin_dir  
7&10      pin_dir  
4&5&12&13 GND  
16        5V  
8         12V  
  
3&14      motor pin 1  
6&11      motor pin 2  
  
HARDWARE
--------
 * Metal Gearmotor 37Dx57L mm with 64 CPR Encoder from www.pololu.com
 * Arduino
 * 754410 or L293D
  
PINS
----
Pinout for motor control uses 3 pins for output. It is somewhat wasteful, but had more flexibility. Two pins for direction control, and one for motor power (assuming PWM).
Be sure to pick a PWM capable pin for pin\_pwm\_output.

The two input pins are for the encoder feedback.

Two direcional pins allow for setting a motor brake by shorting the terminals of the motor together (set both directions HIGH, and preferably turn off the PWM)
  
TODO
----
implement brake feature for 3-pin mode
2-pin constructor
implement friendlier tuning method for PID
