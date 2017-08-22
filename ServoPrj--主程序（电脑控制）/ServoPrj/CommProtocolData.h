#include "def.h"

#ifndef COMMPROTOCOLDATA_H_
#define COMMPROTOCOLDATA_H_

#define FRAME_LEN    13

void SendCurPrg(uint8_t prg);
void InitComm(int Baud);
BYTE GetBuffer(BYTE *data);
BYTE GetFrameDataPart(BYTE *data);
void ClearBuffer();
void PrintDone();
BYTE Write_section(BYTE addr,BYTE *buf,BYTE len);
BYTE Read_section(BYTE addr,BYTE *buf,BYTE len);

#endif
