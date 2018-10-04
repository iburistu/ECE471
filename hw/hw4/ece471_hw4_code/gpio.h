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

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open export file for writing!\n");
	return(-1);
    }

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

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open unexport file for writing!\n");
	return(-1);
    }

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

    sprintf(string_buffer, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(string_buffer, O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open direction file for writing!\n");
	return(-1);
    }
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

    sprintf(string_buffer, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(string_buffer, O_RDONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open GPIO%d\n",pin);
	return(-1);
    }

    if (read(fd, buffer, 3) == -1) {
	fprintf(stderr, "Failed to read from GPIO%d\n",pin);
	return(-1);
    }

    close(fd);
    return(atoi(buffer));
}

int GPIOWrite(int pin, int value)
{
    char string_buffer[34];
    char buffer[3];
    ssize_t bytes_written;
    int fd;

    sprintf(string_buffer, "/sys/class/gpio/gpio%d/value",pin);
    fd = open(string_buffer, O_WRONLY);
    if (-1 == fd) {
	fprintf(stderr, "Failed to open GPIO%d\n",pin);
	return(-1);
    }

    bytes_written = snprintf(buffer, 2, "%d", value);
    write(fd, buffer, bytes_written);
    close(fd);
    return(0);
}

#endif /* GPIO_H */
