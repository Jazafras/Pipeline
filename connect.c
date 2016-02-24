#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#define buffer 1024

int main(int argc, char **argv) { 
	if (argc < 4) {
		fprintf(stderr, "Not enough arguments\n");
		exit(4);
	}
	int position=0; //colon position
	int colon;
	for (colon = 0; colon < argc; colon++){
		if (strcmp(argv[colon], ":")==0){ //found colon
			position = colon;
			argv[position] = NULL;
			break;
		}
		if (position == argc-1){
			fprintf(stderr, "No argument after colon\n");
			exit(3);		
		} 
	}
	if (colon == argc){
		fprintf(stderr, "Colon wasn't found\n");
		exit(5);
	}

	int leftLength;
	int rightLength;
	for(int i = 0; i < position; i++){ //find length of left portion before colon
		leftLength = i;
		//printf("test");
	}
	for(int i = position+1; i < argc; i++){ //find length of right portion after colon
		rightLength = i - position;
	}

	int pid;
	int fd[2]; 
	pipe(fd); 
	switch (pid = fork()) { 
		case 0: /* child */ 
			dup2(fd[0], 0); 
			close(fd[1]); //child does not need end of the pipe 
			execvp(argv[position+1], &argv[position+1]); 
			perror(argv[0]); 

		default: /* parent */ 
			dup2(fd[1], 1); 
			close(fd[0]); //parent does not need end of the pipe 
			//printf("test/n");			
			execvp(argv[1], &argv[1]); 
			perror(argv[0]);
			//printf("test\n"); 

		case -1: 
			perror("fork"); 
			exit(1); 
	} 
	exit(0); 
} 
