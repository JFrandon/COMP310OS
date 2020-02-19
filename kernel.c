#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include "pcb.h" // include pcb type and methods
#include "cpu.h" // include cpu type and methods
#include "ram.h"

#define QUANTA 2

int min(int x, int y) {
	return x < y ? x : y;
}

//readyqueue node type, cince pcbs do not have a next pointer, wrap them in linkedlist node
typedef struct ReadyNode{
	PCB* pcb;
	struct ReadyNode* next;
}ReadyNode;
//readyquqeue global structure
struct ReadyQueue
{
	ReadyNode* head, * tail;
}READYQ;



PCB* popReady() {
	if (READYQ.head == NULL) return NULL;
	ReadyNode *n = READYQ.head;
	PCB* p = n->pcb;
	READYQ.head = n->next;
	if (READYQ.tail == n) READYQ.tail = NULL;
	return p;
}

void addToReady(PCB* pcb){
	ReadyNode* n = (ReadyNode*) malloc(sizeof(ReadyNode));
	n->pcb = pcb;
	n->next = NULL;
	if (READYQ.head && READYQ.tail) {
		READYQ.tail->next = n;
	}
	else {
		READYQ.head = n;
		READYQ.tail = n;
	}
	READYQ.tail = n;
}

int myinit(char* filename) {
	FILE* fp;
	if (!(fp = fopen(filename, "rt"))) {
		printf("Could not open file %s, exec aborted",filename);
		return 7;
	}
	int s, e;
	if (!addToRAM(fp, &s, &e)) {
		printf("Could not load file %s in ram, exec aborted", filename);
		return 8;
	}
	PCB* pcb = makePCB(s, e);
	addToReady(pcb);
	return 0;
}

int scheduler() {
	if (!iscpufree()) return 9; //cpu buisy cannot recurse using exec
	int error = 0;
	PCB* pcb;
	while ((pcb = popReady())) {
		setIP(pcb->PC);
		error = run(min(QUANTA,(pcb->end - pcb->PC)));
		pcb->PC = getIP();
		if ((pcb->PC + QUANTA < pcb->end) && error > -1) { //if didn't terminate
			addToReady(pcb);
		}
		else {
			if (error < 0) //if crashed
			{
				printf("Program at address %d terminated at line %d out of %d\n", pcb->start, (pcb->PC - pcb->start)+1, (pcb->end - pcb->start)-1);
			}
			else {
				printf("Program at address %d terminated at line %d out of %d (Dropped off bottom)\n", pcb->start, (pcb->PC - pcb->start) + 1, (pcb->end - pcb->start) - 1);
			}
			cleanRam(pcb->start, pcb->end);
			free(pcb);
		}
	}
	freecpu();
	return error;
}

int main() {
	freecpu();
	cleanRam(0, 1000);
	puts("Kernel 1.0 loaded!");
	return shellUI();
}