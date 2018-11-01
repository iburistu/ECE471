#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


int main(int argc, char **argv) {

        int spi_fd;
	int result;
	/* Open SPI device */
	
	spi_fd = open("/dev/spidev0.0",O_RDWR);
	if (spi_fd < 0) {
	    printf("Error opening SPI device!\n");
	    return 0;
	}
	/* Set SPI Mode_0 */

	int mode = SPI_MODE_0;

	result = ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
	if (result < 0) {
	    printf("Error writing to SPI device!\n");
	    return 0;
	}

	// SPI setup
 	int value;
	struct spi_ioc_transfer spi;   	
	unsigned char data_out[3] = {0x01, 0x10, 0x00};
	unsigned char data_in[3];
	
	double F,C;
	/* Loop forever printing the CH0 and CH1 Voltages 	*/
	/* Once per second.					*/

	/* Use the SPI_IOC_MESSAGE(1) ioctl() as described in the class notes */
	
	while(1) {

	    data_out[1] = 0x20;				// second channel

	    memset(&spi, 0, sizeof(struct spi_ioc_transfer));	// clear the SPI struct

	    spi.tx_buf = (unsigned long)&data_out;	
	    spi.rx_buf = (unsigned long)&data_in;
	    spi.len = 3;
	    spi.delay_usecs = 0;
	    spi.speed_hz = 100000;
	    spi.bits_per_word = 8;
	    spi.cs_change = 0;
	    
	    result = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi);

	    value = (data_in[1] << 8) | data_in[2];	// read first two bits of data_in[1] and all of data_in[2]

	    C = (((float)value - 500) / 10) + 50;	// formula I found online that converts the value in milivolts to a temperature in C
	    F = ((C * 9) / 5) + 32;			// convert that temperature to F
	    printf("C: %f\nF: %f\n",C,F);


	    sleep(1);					// sleep 1 second

	}



	return 0;
}
