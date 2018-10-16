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
	/* Write 'ECE 471' to display */
	while(1) {

	    buffer[0] = 0x00;	    // offset pointer
	    buffer[1] = 0x79;	    // 'E'
	    buffer[2] = 0x00;	    // next 8 bits of column 1, not connected
	    buffer[3] = 0x39;	    // 'C'
	    buffer[4] = 0x00;	    // next 8 bits of column 2, not connected
	    buffer[5] = 0x00;	    
	    buffer[6] = 0x00;
	    buffer[7] = 0x79;	    // 'E'
	    buffer[8] = 0x00;
	    buffer[9] = 0x00;
	    buffer[10] = 0x00;
	    buffer[11] = 0x00;
	    buffer[12] = 0x00; 
	    buffer[13] = 0x00;
	    buffer[14] = 0x00;
	    buffer[15] = 0x00;
	    buffer[16] = 0x00;
	    

	    write(fd,buffer,17);
	    if(result < 0) {
		printf("Error writing to I2C device!  Exiting!\n");
		return(-1);
	    }

	    sleep(1);

	    // clear the buffer
	    buffer[0] = 0x00;	  
	    for(int i = 0; i < 16; i++) buffer[i+1] = 0x00; 
	    
	    write(fd,buffer,17);
	    if(result < 0) {
		printf("Error writing to I2C device!  Exiting!\n");
		return(-1);
	    }

	    // write '471'
	    buffer[0] = 0x00;	    // offset pointer
	    buffer[1] = 0x66;	    // '4'
	    buffer[2] = 0x00;	    // next 8 bits of column 1, not connected
	    buffer[3] = 0x07;	    // '7'
	    buffer[4] = 0x00;	    // next 8 bits of column 2, not connected
	    buffer[5] = 0x00; 
	    buffer[6] = 0x00;
	    buffer[7] = 0x06;	    // '1'
	    buffer[8] = 0x00;
	    buffer[9] = 0x00;
	    buffer[10] = 0x00;
	    buffer[11] = 0x00;
	    buffer[12] = 0x00; 
	    buffer[13] = 0x00;
	    buffer[14] = 0x00;
	    buffer[15] = 0x00;
	    buffer[16] = 0x00;
	    
	    write(fd,buffer,17);
	    if(result < 0) {
		printf("Error writing to I2C device!  Exiting!\n");
		return(-1);
	    }
	    
	    sleep(1);    

	    // clear the buffer
	    buffer[0] = 0x00;
	    for(int i = 0; i < 16; i++) buffer[i+1] = 0x00;

	    write(fd,buffer,17);
	    if(result < 0) {
		printf("Error writing to I2C device!  Exiting!\n");
		return(-1);
	    }
	    

	}
	/* Close device */

	close(fd);

	return 0;
}
