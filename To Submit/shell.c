#include <stdio.h>
#include <stdlib.h>
#include "./interpreter.h"

#define INPUT_LEN 1000
#define MAX_ARG_AMT 100

char* motd = "Welcome to the Jeremy shell!\nVersion 1.0 January 2020";
char* prompt = "$ ";

char userinput[INPUT_LEN];
int error_code = 0;

int parse(char* ui) {
	int errcode = 0;
	char* words[MAX_ARG_AMT], *p;
	int w = 0 ;
	if (*ui == '#') return 0; // detects a comment
	//breakes the line to an array of words
	for (w = 0; w < MAX_ARG_AMT && *ui != '\0' && *ui != '\n' && *ui != '\r'; w++){
		while (*ui == ' ') ui++;
		words[w] = (char*)calloc(INPUT_LEN, sizeof(char));
		p = words[w];
		while (((*p = *(ui++)) != ' ') && *p != '\0' && *p !='\n' && *p != '\r') p++;
		*p = '\0';
	}
	//interpret the array of words
	errcode = interpreter(w, words);
	//release the memory space of the words
	for (int i = 0; i < w; i++) free(words[i]);
	return errcode;
}


int main() {
	int error_code = 0;
	//prints welcome message
	puts(motd);
	do {
		//prints prompt
		printf("%s",prompt);
		//gets input, flushes stdin buffer
		fgets(userinput, 999, stdin);
		fflush(stdin);
		//parses and execute input
		error_code = parse(userinput);
		if (error_code > 10 && error_code < 20) printf("Script terminated with error code %d\n", error_code - 10);
	//if error code is negative panic, terminate. (No script and built-in program should return negative error)
	} while (error_code >= 0 );
	return error_code;
}