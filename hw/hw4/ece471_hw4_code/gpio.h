#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int GPIOExport(int pin);
int GPIOUnexport(int pin);
int GPIODirection(int pin, char *str);
int GPIORead(int pin);
int GPIOWrite(int pin, int value);

int GPIOExport(int pin) {
    char buffer[3];
    ssize_t bytes_written;
    int fd;

    // open the export file for writing print to standard error if unable to open
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open export file for writing!\n");
	return(-1);
    }
    
    // write buffer contents (pin number)
    bytes_written = snprintf(buffer, 3, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

int GPIOUnexport(int pin)
{
    char buffer[3];
    ssize_t bytes_written;
    int fd;

    // open the unexport file for writing and print to standard error if unable to open
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open unexport file for writing!\n");
	return(-1);
    }
    // write the pin number to unexport
    bytes_written = snprintf(buffer, 3, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

int GPIODirection(int pin, char *str)
{
    char string_buffer[34];
    char buffer[3];
    ssize_t bytes_written;
    int fd;

    // generate path string for open()
    sprintf(string_buffer, "/sys/class/gpio/gpio%d/direction", pin);

    // open the direction file for writing and print to standard error if unable to open
    fd = open(string_buffer, O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open direction file for writing!\n");
	return(-1);
    }
    
    // write then close
    bytes_written = snprintf(buffer, 5, "%s\n", str);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

int GPIORead(int pin)
{
    char string_buffer[34];
    char buffer[3];
    int fd;

    // generate path string for open()
    sprintf(string_buffer, "/sys/class/gpio/gpio%d/value", pin);

    // open the direction file for reading and print to standard error if unable to open
    fd = open(string_buffer, O_RDONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open GPIO%d\n",pin);
	return(-1);
    }

    // read the file on error print to standard error
    if (read(fd, buffer, 3) == -1) {
	fprintf(stderr, "Failed to read from GPIO%d\n",pin);
	return(-1);
    }

    // close and return the read contents
    close(fd);
    return(atoi(buffer));
}

int GPIOWrite(int pin, int value)
{
    char string_buffer[34];
    char buffer[3];
    ssize_t bytes_written;
    int fd;

    // generate path string for open()
    sprintf(string_buffer, "/sys/class/gpio/gpio%d/value",pin);

    // open the direction file for writing and print to standard error if unable to open
    fd = open(string_buffer, O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open GPIO%d\n",pin);
	return(-1);
    }

    // write value to pin
    bytes_written = snprintf(buffer, 2, "%d", value);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

#endif /* GPIO_H */
