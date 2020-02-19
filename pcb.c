#include "pcb.h"
#include <stdlib.h>

PCB* makePCB(int start, int end) {
	PCB* pcb = (PCB*)malloc(sizeof(PCB));
	pcb->PC = start;
	pcb->start = start;
	pcb->end = end;
	return pcb;
}