#include "CommProtocolData.h"

BYTE buf_len = 0;
BYTE buffer[10];

void PrintChar(BYTE c)
{
  Serial.print(c);
}

void copyBuf(BYTE *data)
{
  for(int i=0;i<buf_len;i++)
  {
    data[i] = buffer[i];
  }
  //Serial.write(data,buf_len);
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
    //Serial.write(buffer[buf_len]);
    buf_len ++;
  }
  //Serial.write(buf_len);
  return buf_len;
}

BYTE GetFrameDataPart(BYTE *data)
{
    //Serial.write(GetBuffer(data));
    GetBuffer(data);//Serial.write(data,buf_len);
  if((buf_len >= 8)&&(buffer[buf_len-1]==0X0A))
  {
    copyBuf(data);
    //Serial.write(data,buf_len);
    for(int i=6;i<buf_len;i++)
    {
      if(data[i]==0X0D)
      {
        data[9] = i;//Serial.write(buf_len);
        break;
      }
    }
    data[1] -= '0';
    data[3] -= '0';
    data[4] -= '0';
    data[5] -= '0';
    if(data[9]==7)
    {
      data[6] -= '0';
    }
    //Serial.write(data,data[9]);
    buf_len = 0;
    return 1;
  }
  else
  {
    //Serial.write(buf_len);
    return 0;
  }
  
}

void ClearBuffer()
{
  buf_len = 0;
}



