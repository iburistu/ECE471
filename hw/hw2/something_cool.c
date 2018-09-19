#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // check to see if the user has included a numerical command line argument
    if (argc != 2) {
	printf("usage: hello_world [length]\n");
	return 1;
    }
    // for loop that prints a number followed by a tab, followed by a space, followed by a newline
    // the command line argument is the number of times this loop will run
    for (int i = 0; i < atoi(argv[1]); i++) {
	printf("#%d:\tECE471 HOWDY\n", i + 1);
    }
	return 0;
}
