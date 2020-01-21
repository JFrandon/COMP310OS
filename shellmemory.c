#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MEMSIZE 100

struct MEM {
	char *name;
	char *value;
};

struct MEM memory[MEMSIZE]; 

int setvar(char* name, char* value) {
	int i;
	// find memory cell with name or first empty cell
	for (i = 0; i < MEMSIZE && memory[i].name != 0 && strcmp(memory[i].name, name) != 0; i++);
	// if went to the end of memory then memory full
	if (i == MEMSIZE) {
		puts("Memory full Unable to allocate new name");
		return 4;
	}
	// if found empty cell  creates memory space
	if (memory[i].name == NULL) {
		memory[i].name = (char*)calloc(strlen(name), sizeof(char));
		memory[i].value = (char*)calloc(strlen(value), sizeof(char));
	}
	// update memory cell value
	strcpy(memory[i].name, name);
	strcpy(memory[i].value, value);
	return 0;
}

char* getvar(char* name) {
	int i;
	// find memory cell with name or first empty cell
	for (i = 0; i < MEMSIZE && memory[i].name != 0 && strcmp(memory[i].name, name) != 0; i++);
	// if cell empty or end of memory return NULL
	if (i == MEMSIZE || memory[i].name == 0) {
		return NULL;
	}
	//returns a copy ov value in cell
	char* value = calloc(strlen(memory[i].value), sizeof(char));
	strcpy(value, memory[i].value);
	return value;
}
