#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>

#include "sensor_name.h"

static double read_temp(char *filename) {

    double result=0.0;
    char string1[256], string2[256];
    FILE* fd;

    fd = fopen(filename,"r");

    if (fd == NULL) {
	printf("Error opening 1-wire device!\n");
	fclose(fd);
	return 0;
    }	

    fgets(string1, sizeof(string1), fd);		// grab the contents of lines one and two
    fgets(string2, sizeof(string2), fd);

    if(strstr(string1,"YES") != NULL) {		// check to see if YES is inside string1
	char* loc = strstr(string2, "t=");		// find the location of t=
	char* substr = malloc(7);			// allocate memory for the substring
	strncpy(substr, loc + 2, 6);		// copy 6 bytes from loc + 2 to substr
	substr[6] = '\0';				// strcpy does not add a null terminator.  adding one
	result = atof(substr) / 1000.0;		// convert to float and divide by 1000.0
	return result;
    }
    else {
	printf("Error reading from sensor!\n");
	fclose(fd);
	return 0.0;
    }
}

int main(int argc, char **argv) {

    double temp1;
    int tenths, ones, tens, hundreds;

    int fd;

    unsigned char buffer[17];

    int result = 0;

    /* Open i2c device */

    fd = open("/dev/i2c-1", O_RDWR);
    if(fd < 0) {
	printf("Error opening I2C device!  Exiting!\n");
	return(-1);
    }

    /* Set slave address */

    result = ioctl(fd, I2C_SLAVE, 0x70);

    /* Turn on oscillator */

    buffer[0] = (0x2<<4) | (0x1);
    result = write(fd, buffer, 1);
    if(result < 0) {
	printf("Error writing to I2C device!  Exiting!\n");
	return(-1);
    }

    /* Turn on Display, No Blink */

    buffer[0] = (0x8<<4) | (0x1);
    result = write(fd, buffer, 1);
    if(fd < 0) {
	printf("Error writing to I2C device!  Exiting!\n");
	return(-1);
    }
    
    /* Set Brightness */

    buffer[0] = (0b11101011);
    result = write(fd, buffer, 1);
    if(result < 0) {
	printf("Error writing to I2C device!  Exiting!\n");
	return(-1);
    }

    int num2hex = [9];
    
    num2hex[0] = 0x3F;
    num2hex[1] = 0x06;
    num2hex[2] = 0x5B;
    num2hex[3] = 0x4F;
    num2hex[4] = 0x66;
    num2hex[5] = 0x6D;
    num2hex[6] = 0x7D;
    num2hex[7] = 0x07;
    num2hex[8] = 0x7F;
    num2hex[9] = 0x67;

    buffer[0] = 0x00;
    buffer[2] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = 0x00;
    buffer[6] = 0x00;
    buffer[8] = 0x00;
    buffer[10] = 0x00;
    buffer[11] = 0x00;
    buffer[12] = 0x00;
    buffer[13] = 0x00;
    buffer[14] = 0x00;
    buffer[15] = 0x00;
    buffer[16] = 0x00;

    while(1) {
	temp1=read_temp(SENSOR_NAME);
	tenths = (int)(fmod(temp1,1.0) * 10);
	ones = (int)temp1 % 10;
	tens = ((int)temp1 / 10) % 10;
	hundreds = (int)temp1 / 100;
	
	if ((int)temp1 > 100) {
	    buffer[1] = num2hex[hundreds]
	    buffer[3] = num2hex[tens];

	}

	if((int)temp1 < 100 && (int)temp1 > 0) {
	
	}
	
	if((int)temp1 < 0) {

	}

	sleep(1);

    }

    return 0;
}
