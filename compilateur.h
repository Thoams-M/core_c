#include<stdio.h>
#include<stdlib.h>


int littleToBig(int instructionFinal)
{
	int octet1,octet2,octet3,octet4;
	int O1,O2,O3;
	
	octet1 = instructionFinal & 0b00000000000000000000000011111111;
	octet2 = (instructionFinal >> 8) & 0b000000000000000011111111;
	octet3 = (instructionFinal >> 16) & 0b0000000011111111;
	octet4 = instructionFinal >> 24;
	
	
	O1 = (octet1 << 8) + octet2;
	O2 = (O1 << 8) ^ octet3;
	O3 = (O2 << 8) ^ octet4;
	
	int BigEndian = (-1)*O3;
	
	return(BigEndian);
}
