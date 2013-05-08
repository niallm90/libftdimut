#include "libftdimut.h"

void ftdimut_setTesting(bool value) {
  ftdimut_testing = value;
}

void ftdimut_msleep(unsigned int milliSeconds) {
  struct timespec reqtime;
  unsigned int remainder = 0;

  remainder = milliSeconds % MILLISECINSEC;
  if(remainder == 0) {
    reqtime.tv_sec = milliSeconds / MILLISECINSEC;
  } else {
    reqtime.tv_sec = (milliSeconds - remainder) / MILLISECINSEC;
  }

  reqtime.tv_nsec = NANOSECINMILLISEC * remainder;
  nanosleep(&reqtime, NULL);
}

FT_STATUS ftdimut_setup() {
  FT_STATUS ftStatus; 
  unsigned char timer;

  if(ftdimut_testing == true) {
    return FT_OK;
  }

	ftStatus = FT_SetVIDPID(USB_VID, USB_PID);
  if(ftStatus != FT_OK) return ftStatus;
	ftStatus = FT_Open(0, &ftdimut_ftHandle);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_ResetDevice(ftdimut_ftHandle);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_Purge(ftdimut_ftHandle, FT_PURGE_RX | FT_PURGE_TX);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_SetBaudRate(ftdimut_ftHandle, 15625);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_SetDataCharacteristics(ftdimut_ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_SetFlowControl(ftdimut_ftHandle, FT_FLOW_NONE, 0, 0);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_SetTimeouts(ftdimut_ftHandle, 1000, 1000);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_GetLatencyTimer(ftdimut_ftHandle, &timer);
  if(ftStatus != FT_OK) return ftStatus;
  ftStatus = FT_SetLatencyTimer(ftdimut_ftHandle, 1);
  if(ftStatus != FT_OK) return ftStatus;

  return FT_OK;
}

FT_STATUS ftdimut_init() {
  FT_STATUS ftStatus; 
  unsigned char buf[4];
  unsigned int bytesRead = 0;

  if(ftdimut_testing == true) {
    printf("Test mode init.\n");
    return FT_OK;
  }

  if(ftdimut_getData(0x17) != 0) {
    return FT_OK;
  }

  printf("Sending 0x00 at 5 baud\n");

  printf("Break on......\n");
  ftStatus = FT_SetBreakOn(ftdimut_ftHandle);
  if(ftStatus != FT_OK) return ftStatus;
  ftdimut_msleep(1800);
  printf("Break off......\n");
  ftStatus = FT_SetBreakOff(ftdimut_ftHandle);
  if(ftStatus != FT_OK) return ftStatus;

  ftStatus = FT_Read(ftdimut_ftHandle, buf, 4, &bytesRead);
  if(ftStatus != FT_OK) return ftStatus;

  if(bytesRead == 4) {
    return FT_OK;
  }
  return FT_OTHER_ERROR;
}

FT_STATUS ftdimut_close() {
	return FT_Close(ftdimut_ftHandle);
}

unsigned char ftdimut_getData(unsigned char request) {
  unsigned int bytesRead, bytesWrote;
  unsigned char buf[2];

  if(ftdimut_testing == true) {
    return 30;
  }

  FT_Write(ftdimut_ftHandle, &request, 1, &bytesWrote);
  if(bytesWrote != 1) {
    return 0;
  }
  FT_Read(ftdimut_ftHandle, buf, 2, &bytesRead);
  if(bytesRead != 2) {
    return 0;
  }

  return buf[1];
}
