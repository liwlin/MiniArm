#include "Mem.h"
#include "ServoMain.h"
#include "ServoDriver.h"
#include "CommProtocolData.h"

BYTE data[64] = {0x5A,1,0x5A,1,0x5A,1,0x5A,1,0x5A,1,1};
BYTE flag = 0;
BYTE bIsPrintDown = 0;
BYTE d[10] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x40};
BYTE addr = 0xF0;
BYTE len = 10;
BYTE RUN_CMD = CMD_DEBUG;

Servo_info mem_info;
BYTE bIsLoadE2PROM = 0;

BYTE RunDebug()
{
  int rundata,rdi=7;
  BYTE rdata;
  ClearBuffer();
  while(1)
  {
     if(GetFrameDataPart(data))
     {
          if(data[0] != 0x23)
          {
            Serial.write(data,data[9]);
            return 0;
          }
        if(data[data[9]+1] != 0X0A)
        {
          return 0;
        }
        if(data[9]==6)
        {
          rundata = data[3]*100+data[4]*10+data[5];
        }
        else if(data[9]==7)
        {
          rundata = data[3]*1000+data[4]*100+data[5]*10+data[6];
        }
        rdata = (rundata-500)*9/100;
     SetServoMoveto(data[1]-1,rdata,ServoSpeedResolution);
     }
     MoveAllServoToDest();
     
  }
}

void setup() {
  Serial.begin(9600);
  InitServoPort();
  mem_info.section_hasData = HAS_DATA;
}
// the loop routine runs over and over again forever:
void loop() {
  RunDebug();
}



