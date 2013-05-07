#include "libftdimut.h"
#include <stdio.h>
#include <ftd2xx.h>
#include <stdbool.h>
#include <sys/time.h>

clock_t start = 0;

clock_t getTime() {
  return clock() - start;
}

int main() {
  FT_STATUS ftStatus;
  unsigned int i;

  start = clock();

  ftStatus = ftdimut_setup();
  if(ftStatus != FT_OK) {
    if(ftStatus == FT_DEVICE_NOT_FOUND) {
      printf("Make sure the device is plugged in.\n");
    } else if(ftStatus == FT_DEVICE_NOT_OPENED) {
      printf("Make sure the ftdi_sio and usbserial modules are not loaded.\n");
      printf("You can remove them with 'rmmod ftdi_sio usbserial'.\n");
    } else {
      printf("Unknown error during setup.\n");
    }
    return 1;
  }

  do {
    ftStatus = ftdimut_init();
    if(ftStatus != FT_OK && ftStatus != FT_OTHER_ERROR) {
      printf("Unknown error during init.\n");
      return 1;
    }
    usleep(10000);
  } while (ftStatus == FT_OTHER_ERROR);
  
  printf("%f: %d\n", (float)getTime()/CLOCKS_PER_SEC, ftdimut_getData(0x17));

  for(i = 0; i < 100; i++) {
    printf("%d: %03d %03d\n", getTime(), ftdimut_getData(0x17), ftdimut_getData(0x21));
    usleep(100000);
  }

  ftStatus = ftdimut_close();
  if(ftStatus != FT_OK) {
    printf("Unknown error during clos.\n");
    return 1;
  } 
}
