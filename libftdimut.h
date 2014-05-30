/*
Copyright 2014 Niall McAndrew <niallm90@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

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
void ftdimut_msleep(unsigned int milliSeconds);
FT_STATUS ftdimut_setup();
FT_STATUS ftdimut_init();
FT_STATUS ftdimut_close();

unsigned char ftdimut_getData(unsigned char request);

