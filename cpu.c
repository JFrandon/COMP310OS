#include "cpu.h"
#include "ram.h"
#include "shell.h"
#include <string.h>

CPU GLOBALCPU; //initializes the global CPU to an empty structure

int iscpufree() {
	return (GLOBALCPU.quanta == 0);
}

void freecpu() {
	GLOBALCPU.quanta = 0;
}

void setIP(int ip) {
	GLOBALCPU.IP = ip;
}

int getIP() {
	return GLOBALCPU.IP;
}

int run(int quanta) {
	int error = 0;
	GLOBALCPU.quanta = quanta;
	for (; GLOBALCPU.quanta > 0 ; (GLOBALCPU.IP)++ , (GLOBALCPU.quanta)--) {
		char* command = getFromRam(GLOBALCPU.IP);
		strcpy(GLOBALCPU.IR, command);
		error = parse(GLOBALCPU.IR);
		if (error != 0) {
			return error;
		}
	}
	return error;

}