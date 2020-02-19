#ifndef CPUH
#define CPUH
//cpu gloal structure
typedef struct CPU {
	int IP;
	char IR[1000];
	int quanta;
} CPU;
int run(int quanta);
int iscpufree();
void freecpu();
void setIP(int ip);
int getIP();
#endif
