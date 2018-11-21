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

// The servos come in pairs
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

struct ServoAngles {
    uint16_t A;
    uint16_t B;
    uint16_t C;
    uint16_t D;
    uint16_t E;
    uint16_t F;
};

void sweepServo(Servo servo);
void increaseSweep(Servo servo);
void decreaseSweep(Servo servo);

void setServoPositions(ServoAngles angles);
