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

BYTE RunUpLoad()
{
  Serial.println("UpLoad");
  
  if(mem_info.section_hasData != HAS_DATA)
  {
    Serial.println("NoData");
    return CMD_DEBUG;
  }
  
  if(!bIsLoadE2PROM)
  {
     BYTE t = Read_fromE2PROM(&mem_info);
     bIsLoadE2PROM = 1;
  }
  
  int index = 0;
  int numTotal = mem_info.section_num;
  
  while(index < numTotal)
  {
    Serial.write(0x86);
    Serial.write(0x61);
    Serial.write(index + 1);
    Serial.write(mem_info.info[index].servo1_pos);
    Serial.write(mem_info.info[index].spe1_2.spe_l);
    Serial.write(mem_info.info[index].servo2_pos);
    Serial.write(mem_info.info[index].spe1_2.spe_h);
    Serial.write(mem_info.info[index].servo3_pos);
    Serial.write(mem_info.info[index].spe3_4.spe_l);
    Serial.write(mem_info.info[index].servo4_pos);
    Serial.write(mem_info.info[index].spe3_4.spe_h);
    Serial.write(mem_info.info[index].servo5_pos);
    Serial.write(mem_info.info[index].spe5_6.spe_l);
    Serial.write(mem_info.info[index].servo6_pos);
    Serial.write(mem_info.info[index].spe5_6.spe_h);
    Serial.write(mem_info.info[index].delay_s);
    Serial.write(0xFE);
    index ++;
  }
  
    Serial.write(0xEE);
    Serial.write(0xBB);
    
    delay(2000);
  
  return CMD_DEBUG;
}

BYTE RunDebug()
{
  Serial.println("Debug");
  ClearBuffer();
  while(1)
  {
     if(GetFrameDataPart(data))
        { 
          bIsPrintDown = FALSE;
          //check for return
          if(data[0] > 180 && data[0] != CMD_DEBUG)
          {
            return data[0];
          }
        }
        
     SetServoMoveto(0,data[0],data[1]);
     SetServoMoveto(1,data[2],data[3]);
     SetServoMoveto(2,data[4],data[5]);
     SetServoMoveto(3,data[6],data[7]);
     SetServoMoveto(4,data[8],data[9]);
     SetServoMoveto(5,data[10],data[11]);
     flag = MoveAllServoToDest();
     
     if(flag)
     {
       bIsPrintDown = FALSE;
       delay(20);
     }
     else
     {
       if(!bIsPrintDown)
       {
         delay(data[12]*1000);
         PrintDone();
         bIsPrintDown = TRUE;
       }
     }
  }
}

BYTE RunAuto()
{
  uint8_t num = 0;
  uint8_t i = 0;
  
  Serial.println("Auto");
  ClearBuffer();
  BYTE t = Read_fromE2PROM(&mem_info);
  bIsLoadE2PROM = 1;
  Serial.write(t);
        
  num = mem_info.section_num;
  Serial.write(num);
  
  while(1)
  {
    while(i < num)
    {
      do
      {  
          delay(20);
         SetServoMoveto(0,mem_info.info[i].servo1_pos,mem_info.info[i].spe1_2.spe_l);
         SetServoMoveto(1,mem_info.info[i].servo2_pos,mem_info.info[i].spe1_2.spe_h);
         SetServoMoveto(2,mem_info.info[i].servo3_pos,mem_info.info[i].spe3_4.spe_l);
         SetServoMoveto(3,mem_info.info[i].servo4_pos,mem_info.info[i].spe3_4.spe_h);
         SetServoMoveto(4,mem_info.info[i].servo5_pos,mem_info.info[i].spe5_6.spe_l);
         SetServoMoveto(5,mem_info.info[i].servo6_pos,mem_info.info[i].spe5_6.spe_h);
      }while(MoveAllServoToDest());
      //delay
      
      SendCurPrg(((i+1)*100)/num);
      delay(mem_info.info[i].delay_s*1000);
      //check return word
      if(GetFrameDataPart(data))
      {
        if(data[0] > 180 && data[0] != CMD_AUTO)
          return data[0];
      }
      i++;
    }
     i=0;
     
  }
}

BYTE LoadInfo()
{
  int i = 0;
  
  Serial.println("Load");
  ClearBuffer();
  while(1)
  {
    if(GetFrameDataPart(data))
    {
      //check for return
      if(data[0] > 180 && data[0] != CMD_LOAD)
      {
        mem_info.section_num = i;
        BYTE t = Save_toE2PROM(&mem_info);
        delay(200);
        return data[0];
      }
      
      mem_info.info[i].servo1_pos = data[0];
      mem_info.info[i].spe1_2.spe_l = data[1];
      mem_info.info[i].servo2_pos = data[2];
      mem_info.info[i].spe1_2.spe_h = data[3];
      mem_info.info[i].servo3_pos = data[4];
      mem_info.info[i].spe3_4.spe_l = data[5];
      mem_info.info[i].servo4_pos = data[6];
      mem_info.info[i].spe3_4.spe_h = data[7];
      mem_info.info[i].servo5_pos = data[8];
      mem_info.info[i].spe5_6.spe_l = data[9];
      mem_info.info[i].servo6_pos = data[10];
      mem_info.info[i].spe5_6.spe_h = data[11];
      mem_info.info[i].delay_s = data[12];
      
      PrintDone();
      i++;
    }
    else continue;
    
  }
   mem_info.section_num = i;
}

void setup() {
  
  Serial.begin(115200);
  InitServoPort();
  mem_info.section_hasData = HAS_DATA;
}
// the loop routine runs over and over again forever:
void loop() {
  
  switch(RUN_CMD)
  {
  case CMD_DEBUG:
    {
      RUN_CMD = RunDebug();
    }
    break;
  case CMD_AUTO:
   {   
     RUN_CMD = RunAuto();
   }
   break;
  case CMD_LOAD:
   {
     RUN_CMD = LoadInfo();
   }
   break;
   case CMD_UPLOAD:
   {
     RUN_CMD = RunUpLoad();
   }
   break;
  }

//  Write_section(0x00,d,10);
//  Read_section((uint16_t)0x00,c,50);
//  
//  for(int i=0;i<50;i++)
//  {
//    Serial.write(c[i]);
//  }
//  delay(2000);
}



