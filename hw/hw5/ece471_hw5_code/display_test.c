#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

int main(int argc, char **argv) {

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
	/* Write 1s to all Display Columns */

	buffer[0] = 0x0;
	for (int i = 0; i < 16; i++) {
	    buffer[i+1] = 0xFF;
	}
	write(fd,buffer,17);
	if(result < 0) {
	    printf("Error writing to I2C device!  Exiting!\n");
	    return(-1);
	}
	/* Close device */

	close(fd);

	return 0;
}
