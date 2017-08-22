#include "def.h"

#ifndef COMMPROTOCOLDATA_H_
#define COMMPROTOCOLDATA_H_

void InitComm(int Baud);
BYTE GetBuffer(BYTE *data);
BYTE GetFrameDataPart(BYTE *data);
void ClearBuffer();

#endif
