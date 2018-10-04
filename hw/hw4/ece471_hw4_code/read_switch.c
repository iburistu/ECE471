#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>
#include "gpio.h"

int main(int argc, char **argv) {

    GPIOExport(17);
    GPIODirection(17, "in");

    while(1) {
	if (GPIORead(17)) {
	    usleep(5000);
	    if (GPIORead(17)) {
		printf("Input read on pin 17\n");
		while(GPIORead(17)) {}
		printf("Input removed on pin 17\n");
	    }
	}	
    }

    return(0);
}
