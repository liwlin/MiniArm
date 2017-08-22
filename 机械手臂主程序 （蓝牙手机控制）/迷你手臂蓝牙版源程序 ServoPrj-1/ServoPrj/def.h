#ifndef DEF_H_
#define DEF_H_
#include "Arduino.h"

#define ATmega_168

#define HAS_DATA  0x55

enum{CMD_DEBUG = 0xF0,CMD_AUTO,CMD_LOAD,CMD_PRG,CMD_UPLOAD};  //0XF0~0XF4

#define BYTE unsigned char
#define TRUE    1
#define FALSE   0

typedef struct
{
  BYTE spe_l:4;
  BYTE spe_h:4;
}SPEED;

typedef struct
{
  BYTE servo1_pos;
  BYTE servo2_pos;
  BYTE servo3_pos;
  BYTE servo4_pos;
  BYTE servo5_pos;
  BYTE servo6_pos;
  
  SPEED spe1_2;
  SPEED spe3_4;
  SPEED spe5_6; 
  
  BYTE delay_s;
}SECTION_INFO;

typedef struct
{
  BYTE section_hasData;
  BYTE section_num;
  BYTE ndef[6];
  
  SECTION_INFO info[100];
}Servo_info;

#endif
