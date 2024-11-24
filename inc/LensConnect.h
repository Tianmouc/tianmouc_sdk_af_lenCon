#ifndef _LensConnect_h
#define _LensConnect_h 1

#include "defVal.h"

#define PROGRAM_VERSION "1.0.0"

extern bool USBOpen_frag;
extern int ItemNum;
extern int fineNum;

// LensConnectC.c
const char* OnOff(uint16_t flag);

void ScanUSBLensInfo();
void UsbConnect(int deviceNumber);
void UsbDisconnect();
int init_lens();

// LensInfo.c
void GeneralInfo();
void ZoomInfo();
void FocusInfo();
void IrisInfo();
void OptFilterInfo();

// LensSetup.c
void ZoomSpeedChange();
void FocusSpeedChange();
void IrisSpeedChange();
void ZoomBacklashToggleCtl();
void FocusBacklashToggleCtl();
void IrisBacklashToggleCtl();

// LensAccess.c
void MoveLens(int motor);
void UserIDRead();
void UserIDWrite();
void FineFocusMove();
void LimFocusMove(uint16_t addrData);

#endif //_LensConnect_h

