#include "ServoDriver.h"

typedef struct servo_info
{
  BYTE curr_pos;
  BYTE dest_pos;
  BYTE move_spe;
  BYTE is_moving;
}SERVO_INFO;

SERVO_INFO servo_info[SERVO_NUM];
Servo servo[SERVO_NUM];
BYTE is_anyservo_moving = false;

void InitServoPort()
{
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  servo[0].attach(3);
  servo[1].attach(5);
  servo[2].attach(6);
  servo[3].attach(9);
  servo[4].attach(10);
  servo[5].attach(11);
  
  for(int i = 0;i<SERVO_NUM;i++)
  {
    servo_info[i].curr_pos = 90;
    servo_info[i].dest_pos = 90;
    servo_info[i].move_spe = 1;
    servo_info[i].is_moving = false;
  }
}

BYTE SetServoMoveto(BYTE servo_num,BYTE destpos,BYTE spe)
{  
  if(servo_num > SERVO_NUM)
  return 1;
  servo_info[servo_num].dest_pos = destpos;
  servo_info[servo_num].move_spe = spe;
  
  return 0;
}

BYTE MoveAllServoToDest()
{
  BYTE servo_cnt = 0;
  is_anyservo_moving = false;
  
  for(;servo_cnt < SERVO_NUM;servo_cnt ++)
  {
    if(servo_info[servo_cnt].curr_pos < servo_info[servo_cnt].dest_pos)
    {
      is_anyservo_moving = true;
      if((servo_info[servo_cnt].curr_pos + servo_info[servo_cnt].move_spe) < servo_info[servo_cnt].dest_pos)
      {
        servo_info[servo_cnt].curr_pos += servo_info[servo_cnt].move_spe;
        servo[servo_cnt].write(servo_info[servo_cnt].curr_pos);
      }
      else
      {
         servo_info[servo_cnt].curr_pos = servo_info[servo_cnt].dest_pos;
         servo[servo_cnt].write(servo_info[servo_cnt].dest_pos);
      }
    }
    else if(servo_info[servo_cnt].curr_pos > servo_info[servo_cnt].dest_pos)
    {
      is_anyservo_moving = true;
      if((servo_info[servo_cnt].curr_pos - servo_info[servo_cnt].move_spe) > servo_info[servo_cnt].dest_pos)
      {
        servo_info[servo_cnt].curr_pos -= servo_info[servo_cnt].move_spe;
        servo[servo_cnt].write(servo_info[servo_cnt].curr_pos);
      }
      else
      {
         servo_info[servo_cnt].curr_pos = servo_info[servo_cnt].dest_pos;
         servo[servo_cnt].write(servo_info[servo_cnt].dest_pos);
      }
    }
  }
  return is_anyservo_moving;
}


