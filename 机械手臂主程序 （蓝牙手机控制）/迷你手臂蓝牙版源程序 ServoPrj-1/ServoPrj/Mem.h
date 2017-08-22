#include "def.h"
#include <avr/eeprom.h>

#ifndef MEM_H_
#define MEM_H_

#define MEM_LEN  512

#define MEM_START  0x10
#define MEM_END  MEM_LEN

BYTE Write_section(uint16_t addr,BYTE *buf,BYTE len);
BYTE Read_section(uint16_t addr,BYTE *buf,BYTE len);
BYTE Save_toE2PROM(Servo_info* pInfo);
BYTE Read_fromE2PROM(Servo_info* pInfo);

BYTE Write_section(uint16_t addr,BYTE *buf,BYTE len)
{
  uint16_t i = 0;

  for(;i < len;i++)
  {
    if(i >= MEM_END)
    return i;
    eeprom_write_byte((uint8_t*)(addr + i),buf[i]);
  }
  return 0;
}

BYTE Read_section(uint16_t addr,BYTE *buf,BYTE len)
{
  uint16_t i = 0;
  
  for(;i < len;i++)
  {
     if((i+len) >= MEM_END)
      return i;
      
      buf[i] = eeprom_read_byte((uint8_t*)(addr + i));
  }
  
  return 0;
}

BYTE Save_toE2PROM(Servo_info* pInfo)
{
  uint16_t len = pInfo->section_num * sizeof(SECTION_INFO) + 8;
  BYTE *p = (BYTE*)pInfo;
  uint16_t write_len = 8;
  const BYTE save_step = sizeof(SECTION_INFO);
  
  Write_section(0,p,8);
  p += 8;
  
  while(write_len < (len-8))
  {
    Write_section(write_len,p,save_step);
  
    write_len += save_step;
    p += save_step;
  }
  return write_len;
}

BYTE Read_fromE2PROM(Servo_info* pInfo)
{
  BYTE bHasData = eeprom_read_byte((uint8_t*)0x01);
  if(bHasData != HAS_DATA)
  {
  }
  uint16_t len = eeprom_read_byte((uint8_t*)0x01) + 1;
  len = len*sizeof(SECTION_INFO);
  BYTE *p = (BYTE*)pInfo;
  uint16_t read_len = 8;
  const BYTE read_step = sizeof(SECTION_INFO);
  
  Read_section(0,p,8); 
  p+=8;
  
  while(read_len < len-1)
  {
    Read_section(read_len,p,read_step); 

    read_len += read_step;
    p += read_step;
  }
  return read_len;
}

#endif
