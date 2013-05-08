#include <ftd2xx.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define USB_VID 0x0403
#define USB_PID 0xcc4a

#define MILLISECINSEC 1000
#define NANOSECINMILLISEC 1000000

FT_HANDLE ftdimut_ftHandle;
bool ftdimut_testing = false;

void ftdimut_setTesting(bool value);
void ftdimut_msleep();
FT_STATUS ftdimut_setup();
FT_STATUS ftdimut_init();
FT_STATUS ftdimut_close();

unsigned char ftdimut_getData(unsigned char request);

