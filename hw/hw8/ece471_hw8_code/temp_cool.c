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
	    // convert to F
	    result = (9.0 / 5.0) * (atof(substr) / 1000.0) + 32.0;
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

	while(1) {
		temp1=read_temp(SENSOR_NAME);
		printf("%.2lfF\n",temp1);
		sleep(1);
	}

	return 0;
}
