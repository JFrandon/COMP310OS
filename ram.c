#include <stdio.h>
#include <string.h>
#include "ram.h"

char* RAM[1000]; //initializes global ram as empty array

int get_first_empty_cell() {
	int i;
	for (i = 0; i<1000 && RAM[i]; i++);
	if (i == 1000) return -1;
	return i;
}

void cleanRam(int start, int end) {
	for (int i = start; i < end; i++) RAM[i] = NULL;
}

char* getFromRam(int index) {
	return RAM[index];
}

int addToRAM(FILE* p, int* start, int* end) {
	int s = get_first_empty_cell();
	if (s == -1) return 0;
	int e;
	char buffer[1000];
	for (e = s; !feof(p) && e < 100; e++) {
		fgets(buffer, 999,p);
		char* v = (char*)calloc(1000, sizeof(char));
		strcpy(v, buffer);
		RAM[e] = v;
	}
	if (!feof(p)) {
		cleanRam(s, e);
		return 0;
	}
	*start = s;
	*end = e;
	return 1;
}