
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "shell.h"

#define SUCCESS 0 
#define ON_MAC 1
#define COMMON_SIZE 128
#define HISTORY_FILE "history.txt"

FILE * history;

int main(){

	fprintf(stdout, "on.\n");
	loop();
	fprintf(stdout, "done.\n");
	
	if(ON_MAC){
		fclose(stdout);
		fclose(stdin);
	}

	return SUCCESS; 
}

void loop(){

	while(1){
		fprintf(stdout, "$");

		/* Read a line from stdin. Line is heap allocated */
		char * line_heap = get_big_line(stdin);
		if(line_heap == NULL) die("malloc() failed");

		/* To free the heap allocared buffer immediately */
		char line_stack[strlen(line_heap)];
		memset(line_stack, 0, strlen(line_heap));
		strcpy(line_stack, line_heap);
		free(line_heap);

		/* Get the shell arguments into usual argv form */
		int argc = get_argc(line_stack, ' ');
		if(argc == 0) continue;
		char * argv[argc + 1];
		get_argv(line_stack, argv);
		argv[argc] = 0; 

		if(interpret(argv, argc) == 0) break;
	}
}

/* Function returns a pointer to a heap allocated null terminated array.
   This array contains the characters of the line of file fp.
   Function returns NULL if malloc error occured. */
char * get_big_line(FILE * fp){
	
	int actual_size = 0;
	int buf_size = COMMON_SIZE;
	char * buf = malloc(buf_size * sizeof *buf);
	// memset(buf, 0, buf_size * sizeof *buf );
	if(buf == NULL) return NULL; 

	char c = fgetc(fp);
	while( c != EOF && c != '\n'){
		
		/* Reallocate the buffer and expand it in case it is full */
		if(actual_size == buf_size - 1){
			buf_size *= 2;
			buf = realloc(buf, buf_size);
			if(buf == NULL) return NULL;
		}

		buf[actual_size] = c;
		actual_size++;

		c = fgetc(fp);
	}

	buf[actual_size] = '\0';
	return buf;
}

/* Tokenize and build an array of pointers */
void get_argv(char * line, char ** argv){
	char * arg = strtok(line, " ");
	int i = 0;
	while(arg != NULL){
		argv[i++] = arg;
		arg = strtok(NULL, " "); 
	}
}

/* Function get the number of arguments/tokens in a string */
int get_argc(char * line, char delim){
	
	int count = 0;
	int i;
	if(strlen(line) == 0) return 0;

	for(i = 0; i < strlen(line) - 1; i++){
		if(line[i] == delim && line[i + 1] != delim) count++;
	}

	return ++count; 
}

void print_argv(char ** argv, int argc){
	int i = 0;
	while(i < argc){
		fprintf(stdout, "%s ", argv[i]);
		i++;
	}
	fprintf(stdout, "\n");
}

int interpret(char ** argv, int argc){

	if(!strcmp(argv[0], "exit")){
		return 0;
	}else if(!strcmp(argv[0], "history")){

	}else if(!strcmp(argv[0], "cd")){
		chdir(argv[1]);
	}else{
		execute(argv);
	}
	return 1;

}

/* Function executes the the binary */
void execute(char ** argv){
	
	pid_t child; 
	if((child = fork()) < 0) die_errno();
	if(child == 0){
		execvp(argv[0], argv);
		die_errno();
	}else{
		wait(NULL);
	}
}

void die(char * error_message){
	fprintf(stderr, "error: %s\n", error_message);
	exit(1);
}

void die_errno(){
	fprintf(stderr, "error: %s\n", strerror(errno));
	exit(1);
}


