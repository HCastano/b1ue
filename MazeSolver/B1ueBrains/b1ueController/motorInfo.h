#define MICH_SERVOMIN  170
#define MICH_SERVOMAX  520

#define MAX_SERVOMIN  155
#define MAX_SERVOMAX  550

#define JIMMY_SERVOMIN  175
#define JIMMY_SERVOMAX  525

#define BOBBY_SERVOMIN  165
#define BOBBY_SERVOMAX  505

#define RUPERT_SERVOMIN  160
#define RUPERT_SERVOMAX  550

#define LISA_SERVOMIN  175
#define LISA_SERVOMAX  600

// The servos come in pairs
// The first motor in the pair will go "up" when the
// angles commanded are less than 90, while the second
// motor in the pair will go up when angles less than 90
// are provided
//
// e.g To make Michelle and Max go up by 30-deg, Michelle
// needs to be commanded to 60-deg and Max to 120-deg
enum ServoID {
  // -- A + A` --
  Michelle,
  Max,
  // -- B + B` --
  Jimmy,
  Bobby,
  // -- C + C` --
  Rupert,
  Lisa,
  // Bookkeeping
  NumberOfServos,
};

struct Servo {
  ServoID id;
  uint16_t previousAngle;
  uint16_t nextAngle;
  uint16_t servoMin;
  uint16_t servoMax;
};

// TODO: Do this elsewhere
Servo servo1 = {Michelle, 90, 90, MICH_SERVOMIN, MICH_SERVOMAX};
Servo servo2 = {Max, 90, 90, MAX_SERVOMIN, MAX_SERVOMAX};
Servo servo3 = {Jimmy, 90, 90, JIMMY_SERVOMIN, JIMMY_SERVOMAX};
Servo servo4 = {Bobby, 90, 90, BOBBY_SERVOMIN, BOBBY_SERVOMAX};
Servo servo5 = {Rupert, 90, 90, RUPERT_SERVOMIN, RUPERT_SERVOMAX};
Servo servo6 = {Lisa, 90, 90, LISA_SERVOMIN, LISA_SERVOMAX};

struct ServoAngles {
    uint16_t A;
    uint16_t B;
    uint16_t C;
    uint16_t D;
    uint16_t E;
    uint16_t F;
};

ServoAngles readAnglesFromSerial();

void sweepServo(Servo servo);
void increaseSweep(Servo servo);
void decreaseSweep(Servo servo);

void setServoPositions(ServoAngles angles);
