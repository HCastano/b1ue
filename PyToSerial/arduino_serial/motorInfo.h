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

struct ServoAngles {
    uint16_t A;
    uint16_t B;
    uint16_t C;
    uint16_t D;
    uint16_t E;
    uint16_t F;
};

void setServoPositions(ServoAngles angles);
