#include "CommProtocolData.h"

BYTE buf_len = 0;
BYTE buffer[64];

void SendCurPrg(uint8_t prg)
{
  Serial.write(CMD_PRG);
  Serial.write(prg);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
}

void PrintChar(BYTE c)
{
  Serial.print(c);
}

void PrintDone()
{
  Serial.println("Done");
}

void copyBuf(BYTE *data)
{
  for(int i=0;i<buf_len;i++)
  {
    data[i] = buffer[i];
  }
}

void InitComm(int Baud)
{
  Serial.begin(Baud);
}

BYTE GetBuffer(BYTE *data)
{ 
  while(Serial.available())
  {
    buffer[buf_len] = Serial.read();
    //Serial.print(buffer[buf_len]);
    buf_len ++;
  }
  return buf_len;
}

BYTE GetFrameDataPart(BYTE *data)
{
  GetBuffer(data);
  if(buf_len == FRAME_LEN)
  {
    copyBuf(data);
    buf_len = 0;
    return 1;
  }
  else return 0;
}

void ClearBuffer()
{
  buf_len = 0;
}



