#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shellmemory.h"
#include "shell.h"

// counts how many scripts have been recursively called
#define MAX_REC 1000
int script_rec_depth = 0;

//helper method for var assignment where `set x 1 2` is interpreted ass `set x "1 2 "` 
char* strconcat(char** words, int wcount) {
	char* p = calloc(1,sizeof(char));
	char** i = words;
	for (int j = wcount; j > 0; j--) {
		char* t = calloc(strlen(p) + strlen(*i)+1, sizeof(char));
		strcpy(t, p);
		strcat(t, *i);
		free(p);
		p = t;
		if (*(++i) != NULL)strcat(p, " ");
	}
	return p;
}


//prints help
int help(int argc, char* argv[]) {
	puts("Valid Commands:\n\
COMMAND\t DESCRIPTION\n\
help\t Displays all the commands\n\
 quit\t Exits / terminates the shell with 'Bye!'\n\
 set VAR STRING\t Assigns a value to shell memory\n\
 print VAR\t Displays the STRING assigned to VAR\n\
 run SCRIPT.TXT\t Executes the file SCRIPT.TXT");
	return 0;
}

//quits shell or script if in script
int quit(int argc, char* argv[]) {
	if (script_rec_depth) return 10; //if at least 1 script called return the script with err 0;
	puts("Bye!");
	exit(0);
}

//sets variable in shell memory
int set(int argc, char* argv[]) {
	if (argc < 3) return 2;
	char* words = strconcat(&argv[2],argc-2);
	//calls funtion from shellmemory
	return setvar(argv[1], words);
}

//prints var from shellmemory
int print(int argc, char* argv[]) {
	if (argc < 2) return 2;
	//getvar sends a copy of the string
	char* var = getvar(argv[1]);
	if (var == NULL) {
		puts("Variable does not exist");
		return 6;
	}
	puts(var);
	//frees the copy of the requested string
	free(var);
	return 0;
}
int run(int argc, char* argv[]) {
	if (argc < 2) return 2; // no file specified
	FILE* p;
	int error_code =  0;
	// line array
	char line[1000];
	// max recursion level attained
	if (++script_rec_depth >= MAX_REC) {
		printf("Reached %d script calls, is a script calling himself?\n", script_rec_depth);
		script_rec_depth--; //decrease recursuion level before returning
		return 3;
	}
	// unable to open said script
	if (!(p = fopen(argv[1], "rt"))) {
		puts("Specified File does not exist");
		script_rec_depth--; //decrease recursuion level before returning
		return 5;
	}
	// for every line of the file parse and execute
	fgets(line, 999, p);
	while (!feof(p))
	{
		error_code = parse(line);
		if (error_code != 0) {
			if (error_code > 9 && error_code < 20) error_code -= 10; // subscript returned before final line convert to standard error
			fclose(p);
			script_rec_depth--; //decrease recursuion level before returning
			return error_code+10; //return script error code
		}
		fgets(line, 999, p);
	}
	fclose(p);
	script_rec_depth--;//decrease recursuion level before returning
	return error_code;
}


void* commands[5][2] = { {"help",&help},{"quit",&quit},{"set",&set},{"print",&print}, {"run",&run} };

int interpreter(int argc, char *argv[] ) {
	int error_code;
	if (argc == 0) return 0;
	for (int i = 0; i < 5; i++) {
		if (strcmp(argv[0], (char*) commands[i][0])==0) {
			int (*f)(int, char* []) = commands[i][1];
			error_code = f(argc, argv);
			if (error_code == 2) {
				printf("Too few arguments for function %s\n", argv[0]);
			}
			return error_code;
		}
	}
	printf("Unknown command %s\n",argv[0]);
	return 1;
}