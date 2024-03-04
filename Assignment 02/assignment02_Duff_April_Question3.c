/* Author name: April Duff
   Email: apduff@okstate.edu
   Date: February 25, 2024
   Program Description: Assignment 02 Question 3
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

void *thread_function1(void *arg) {
	printf("Thread 1 created\n");

	/* Thread does something meaningful task..*/

	char *argv[] = {"ls", "-l", NULL};
	
	if (fork() == 0) {
		execvp("ls", argv);
		perror("execvp");
	} else {
		printf("Thread 1 is done\n");
	}
}

void *thread_function2(void *arg) {
	printf("Thread 2 created\n");

	/* Thread does something meaningful task..*/

	printf("Thread 2 is done\n");
	pthread_exit(NULL);
}

int main() {
	pid_t pid;
	pthread_t thread_id;

	printf("Main process started\n");

	if (pthread_create(&thread_id, NULL, thread_function1, NULL) != 0){
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&thread_id, NULL, thread_function2, NULL) != 0){
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		printf("Child process executing\n");
	} else {
		printf("Parent process continuing\n");
	}

	if (pthread_join(thread_id, NULL) != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	printf("Main process is done\n");

	return 0;
}
