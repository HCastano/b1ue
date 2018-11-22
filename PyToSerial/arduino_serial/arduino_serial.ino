#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "motorInfo.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void resetMotorPositions() {
  delay(1500);
  for (int i = 90; i >= 20; i--) {
    delay(5);

    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);
    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);

    pwm.setPWM(Michelle, 0, mich_pulselen);
    pwm.setPWM(Max, 0, max_pulselen);

    pwm.setPWM(Jimmy, 0, jimmy_pulselen);
    pwm.setPWM(Bobby, 0, bobby_pulselen);

    pwm.setPWM(Rupert, 0, rupert_pulselen);
    pwm.setPWM(Lisa, 0, lisa_pulselen);
  }

  delay(500);
  for (int i = 20; i <= 90; i++) {
    delay(5);

    // Want to replace MICH_SERVOMIN with something like Michelle.MIN
    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);
    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);

    pwm.setPWM(Michelle, 0, mich_pulselen);
    pwm.setPWM(Max, 0, max_pulselen);

    pwm.setPWM(Jimmy, 0, jimmy_pulselen);
    pwm.setPWM(Bobby, 0, bobby_pulselen);

    pwm.setPWM(Rupert, 0, rupert_pulselen);
    pwm.setPWM(Lisa, 0, lisa_pulselen);
  }

  delay(100);
}

void sweepServo(Servo servo) {
   if (servo.previousAngle <= servo.nextAngle) {
    increaseSweep(servo);
  } else {
    decreaseSweep(servo);
  }
}

void increaseSweep(Servo servo) {
  for (int i = servo.previousAngle; i <= servo.nextAngle; i++) {
    // TODO: Look into changing this to -90 to 90
    uint16_t pulseLength = map(i, 0, 180, servo.servoMin, servo.servoMax);
    pwm.setPWM(servo.id, 0, pulseLength);
  }
}

void decreaseSweep(Servo servo) {
  for (int i = servo.previousAngle; i >= servo.nextAngle; i--) {
    uint16_t pulseLength = map(i, 0, 180, servo.servoMin, servo.servoMax);
    pwm.setPWM(servo.id, 0, pulseLength);
  }
}

// NOTE: I'm not sure if this is quick enough to make
// it seem like the motors are all moving at the same
// time instead of sequentially
void setServoPositions(ServoAngles angles) {
  servo1.nextAngle = angles.A;
  sweepServo(servo1);

  servo2.nextAngle = angles.B;
  sweepServo(servo2);

  servo3.nextAngle = angles.C;
  sweepServo(servo3);

  servo4.nextAngle = angles.D;
  sweepServo(servo4);

  servo5.nextAngle = angles.E;
  sweepServo(servo5);

  servo6.nextAngle = angles.F;
  sweepServo(servo6);
}

// -- Utility functions -- //

// Might want to do something like have it read until it hits an
// termination character (\n), at which point we should have all
// six angles and we can go ahead and send that to the motors
ServoAngles readAnglesFromSerial() {
  int angle1 = Serial.read();
  int angle2 = Serial.read();
  int angle3 = Serial.read();
  int angle4 = Serial.read();
  int angle5 = Serial.read();
  int angle6 = Serial.read();

  ServoAngles newAngles =
    (ServoAngles) {
      angle1,
      angle2,
      angle3,
      angle4,
      angle5,
      angle6
  };

  return newAngles;
}

// -- Standard Arduino Functions -- //

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // Want to ensure that the motors are at 90-deg before starting anything
  resetMotorPositions();
  delay(10);
}

void loop() {
  // This will be skipped if no data present, leading to
  // the code sitting in the delay function below
  while (Serial.available()) {
    // Delay allows the buffer to fill
    // Not sure if we'll need this though
    delay(30);

    if (Serial.available() > 0) {
      // Read a single byte from the serial buffer
      char c = Serial.read();
      ServoAngles newAngles = readAnglesFromSerial();

      if (c == 'E') {
        Serial.println(c);

        // {120 -> Goes down, 120 -> Goes up}
        setServoPositions(newAngles);
      } else if (c == 'X') {
        setServoPositions(newAngles);
      }
      Serial.println(c);
    }
  }

  delay(500);
  Serial.flush();
}
