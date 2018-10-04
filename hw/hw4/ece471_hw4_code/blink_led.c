#include <stdio.h>
#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "gpio.h"

int main(int argc, char **argv)
{
    GPIOExport(18);
    GPIOExport(17);
    sleep(1);
    GPIODirection(18,"out");
    GPIODirection(17,"in");
     
    while(1) {
	GPIOWrite(18,1);
	usleep(500000);
	GPIOWrite(18,0);
	usleep(500000);
    }
    return 0;
}
