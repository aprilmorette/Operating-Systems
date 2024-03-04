/* Author name: April Duff
   Email: apduff@okstate.edu
   Date: February 11, 2024
   Program Description: Creates 16 processes with five fork() calls.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid = fork();
	fork() || fork() && fork();
	fork();
	
	/* prints processes */
	if (pid < 0) {
		printf("fork failed");
		exit(1);
	} 

	else if (pid == 0) {	// child process
		printf("child process %d\n", getpid());
	} 

	else {	  // parent process
		printf("parent process %d\n", getpid());
	}

	return 0;
}
