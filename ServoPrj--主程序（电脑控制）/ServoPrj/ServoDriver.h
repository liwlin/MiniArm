
#include "def.h"
#include <Servo.h>

#ifndef SERVODRIVER_H_
#define SERVODRIVER_H_

#define MIN_POS  1100
#define MAX_POS  2000
#define SERVO_NUM  6

void InitServoPort();
BYTE SetServoMoveto(BYTE servo_num,BYTE destpos,BYTE spe);
BYTE MoveAllServoToDest();

#endif
