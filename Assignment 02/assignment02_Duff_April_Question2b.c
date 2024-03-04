/* Author name: April Duff
   Email: apduff@okstate.edu
   Date: February 25, 2024
   Program Description: Assignment 02 Question 2 Part b
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_var = 0;

static int static_var = 0;

void* thread_function(void* arg) {
	int local_var = 0;

	int* dynamic_var = (int*)malloc(sizeof(int));
	*dynamic_var = 0;

	local_var++;
	(*dynamic_var)++;
	global_var++;
	static_var++;

	free(dynamic_var);

	int i;
	pid_t pid;

	for (i = 0; i < 3; i++) {
		pid = fork();
		if (pid == 0) {		// if child process
			local_var++;
			(*dynamic_var)++;
			global_var++;
			static_var++;

			// prints process id, thread id, local, dynamic, global, and static variables for the current thread
			printf("pid: %d, tid: %ld, local: %d, dynamic: %d, global: %d, static: %d\n", getpid(), pthread_self(), local_var, *dynamic_var, global_var, static_var);

			exit(0);
		} else if (pid < 0) {	// if fork is unsuccessful
			fprintf(stderr, "Fork failed\n");
			return NULL;
		}
	}

	for (i = 0; i < 3; i++) {
		wait(NULL);
	}

	pthread_exit(NULL);
}

int main() {
	pthread_t threads[3];
	int i;

	for (i = 0; i < 3; i++) {
		pthread_create(&threads[i], NULL, thread_function, NULL);
	}
	for (i = 0; i < 3; i++) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}
