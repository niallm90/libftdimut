#include <sys/time.h>
#include <ftd2xx.h>
#include <stdbool.h>
#include <stdio.h>

#define USB_VID 0x0403
#define USB_PID 0xcc4a

FT_HANDLE ftHandle;

FT_STATUS ftdimut_setup();
FT_STATUS ftdimut_init();
FT_STATUS ftdimut_close();

unsigned char ftdimut_getData(unsigned char request);

