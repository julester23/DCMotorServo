//Include Encoder and PID_v1 to enable DCMotorServo's usage of them.
//(see: http://stackoverflow.com/questions/6504211/is-it-possible-to-include-a-library-from-another-library-using-the-arduino-ide)
#include <Encoder.h>
#include <PID_v1.h>
#include <DCMotorServo.h>

#define pin_dcmoto_dir1 4
#define pin_dcmoto_dir2 5
#define pin_dcmoto_pwm_out 6
#define pin_dcmoto_encode1 3
#define pin_dcmoto_encode2 2
//Determined by experimentation, depends on your encoder, and your belt/gearing ratios:
#define dcmoto_encoder_1_inch 1344

DCMotorServo servo = DCMotorServo(pin_dcmoto_dir1, pin_dcmoto_dir2, pin_dcmoto_pwm_out, pin_dcmoto_encode1, pin_dcmoto_encode2);

void setup() {

  //Tune the servo feedback
  //Determined by trial and error
  servo.myPID->SetTunings(0.1,0.15,0.05);
  servo.setPWMSkip(50);
  servo.setAccuracy(20);
  //Un-necessary, initializes to 0:
  //servo.setCurrentPosition(0);
}


void loop() {
  //wait 1s before starting
  static unsigned long motor_timeout = millis() + 1000;
  static bool motor_go = 0;

  servo.run();

  if (servo.finished()) {
    if(motor_go) {
      //stop disengages the motor feedback system, in which case if you moved the motor, it would fight you if you didn't "stop" it first (provided you were still running servo.run() operations)
      servo.stop();
      motor_timeout = millis() + 1500;
      motor_go = 0;
    }
    if(motor_timeout < millis()) {
      //Setting a move operation will ensure that servo.finished() no longer returns true
      servo.move(dcmoto_encoder_1_inch);
      motor_go = 1;
    }
  }
}
