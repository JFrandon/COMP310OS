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
	for (i = 0; i < MEMSIZE && memory[i].name != 0 && strcmp(memory[i].name, name) != 0; i++);
	if (i == MEMSIZE) {
		puts("Memory full Unable to allocate new name");
		return 4;
	}
	if (memory[i].name == NULL) {
		memory[i].name = (char*)calloc(strlen(name), sizeof(char));
		memory[i].value = (char*)calloc(strlen(value), sizeof(char));
	}
	strcpy(memory[i].name, name);
	strcpy(memory[i].value, value);
	return 0;
}

char* getvar(char* name) {
	int i;
	for (i = 0; i < MEMSIZE && memory[i].name != 0 && strcmp(memory[i].name, name) != 0; i++);
	if (i == MEMSIZE || memory[i].name == 0) {
		return NULL;
	}
	char* value = calloc(strlen(memory[i].value), sizeof(char));
	strcpy(value, memory[i].value);
	return value;
}
