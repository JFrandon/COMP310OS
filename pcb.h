#ifndef PCBH
#define PCBH

//PCB Type
typedef struct PCB
{
	int PC;
	int start;
	int end;
} PCB;

PCB* makePCB(int start, int end);

#endif
