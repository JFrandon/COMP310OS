#ifndef RAMH
#include <stdlib.h>
#include <stdio.h>

#define RAMH
int addToRAM(FILE* p, int* start, int* end);
void cleanRam(int start, int end);
char* getFromRam(int index);

#endif // !RAMH

