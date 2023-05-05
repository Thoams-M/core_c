#include<stdio.h>
#include<stdlib.h>

typedef struct {

	// registers
	int pc;
	
	unsigned long long int r[15]; // r[0] = registre 0 etc.
	

	int flagEqual;
	int flagInf;
	int flagSup; 
	
	int flagInfEqual;
	int flagSupEqual;
	
	int flagADC;
	int flagSBC;
	 
	int inst;
	
}coeur;

int littleToBig(int instructionFinal)
{
	
	uint32_t b0,b1,b2,b3;
	uint32_t res;

	b0 = (instructionFinal & 0x000000ff) << 24u;
	b1 = (instructionFinal & 0x0000ff00) << 8u;
	b2 = (instructionFinal & 0x00ff0000) >> 8u;
	b3 = (instructionFinal & 0xff000000) >> 24u;

	res = b0 | b1 | b2 | b3;
	
	return(res);
}
