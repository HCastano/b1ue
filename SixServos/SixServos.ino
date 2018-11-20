#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Right side (close to 0-deg)
#define MICH_SERVOMIN  170
#define MICH_SERVOMAX  520

#define MAX_SERVOMIN  155
#define MAX_SERVOMAX  550

#define JIMMY_SERVOMIN  175
#define JIMMY_SERVOMAX  525

#define BOBBY_SERVOMIN  165
#define BOBBY_SERVOMAX  505

#define RUPERT_SERVOMIN  150
#define RUPERT_SERVOMAX  570

#define LISA_SERVOMIN  175
#define LISA_SERVOMAX  600

typedef enum Servo {
  Lisa,
  Michelle,
  Max,
  Jimmy,
  Bobby,
  Rupert,
};

uint8_t servoNum = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("--- Starting the Loop ---");

  delay(1500);
  for (int i = 90; i >= 20; i--) {
    delay(15);

    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);
    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);

    pwm.setPWM(0, 0, mich_pulselen);
    pwm.setPWM(1, 0, max_pulselen);

    pwm.setPWM(2, 0, jimmy_pulselen);
    pwm.setPWM(3, 0, bobby_pulselen);

    pwm.setPWM(4, 0, rupert_pulselen);
    pwm.setPWM(5, 0, lisa_pulselen);
  }

  delay(500);
  for (int i = 20; i <= 140; i++) {
    delay(15);

    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);
    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);

    pwm.setPWM(0, 0, mich_pulselen);
    pwm.setPWM(1, 0, max_pulselen);

    pwm.setPWM(2, 0, jimmy_pulselen);
    pwm.setPWM(3, 0, bobby_pulselen);

    pwm.setPWM(4, 0, rupert_pulselen);
    pwm.setPWM(5, 0, lisa_pulselen);
  }

  delay(200);
  for (int i = 140; i >= 20; i--) {
    delay(15);

    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);
    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);

    pwm.setPWM(0, 0, mich_pulselen);
    pwm.setPWM(1, 0, max_pulselen);

    pwm.setPWM(2, 0, jimmy_pulselen);
    pwm.setPWM(3, 0, bobby_pulselen);

    pwm.setPWM(4, 0, rupert_pulselen);
    pwm.setPWM(5, 0, lisa_pulselen);
  }

  for (int i = 20; i <= 90; i++) {
    delay(15);

    uint16_t mich_pulselen = map(i, 0, 180, MICH_SERVOMIN, MICH_SERVOMAX);
    uint16_t max_pulselen = map(i, 180, 0, MAX_SERVOMIN, MAX_SERVOMAX);

    uint16_t jimmy_pulselen = map(i, 0, 180, JIMMY_SERVOMIN, JIMMY_SERVOMAX);
    uint16_t bobby_pulselen = map(i, 180, 0, BOBBY_SERVOMIN, BOBBY_SERVOMAX);

    uint16_t lisa_pulselen = map(i, 180, 0, LISA_SERVOMIN, LISA_SERVOMAX);
    uint16_t rupert_pulselen = map(i, 0, 180, RUPERT_SERVOMIN, RUPERT_SERVOMAX);

    pwm.setPWM(0, 0, mich_pulselen);
    pwm.setPWM(1, 0, max_pulselen);

    pwm.setPWM(2, 0, jimmy_pulselen);
    pwm.setPWM(3, 0, bobby_pulselen);

    pwm.setPWM(4, 0, rupert_pulselen);
    pwm.setPWM(5, 0, lisa_pulselen);
  }

  Serial.println("--- Ending the Loop ---");
  delay(1500);
}
