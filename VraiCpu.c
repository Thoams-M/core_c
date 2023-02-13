#include<stdio.h>
#include<stdlib.h>

/*#include "types.h"
#include "instructions.h"
#include "flags.h"
*/
//void fetch(cpu *c);
//void free_cpu(cpu *c);
//void run_cpu(cpu *c)

/*void free_cpu(cpu *c) {
	free(c);
}

void run_cpu(cpu *c) {
	while (c->inst != HLT) {
		fetch(c);
		execute(c);
	}
void fetch(cpu *c) {
	if (c->inst < 0x7){c->pc++;}
	c->inst 
	
	
}*/


int main()
{
//valeur exemple
int pc=0;
int flagEqual=0;
int flagInf=0;
int flagSup=1;
int SigneBranch;
unsigned long pcBranch;
unsigned long bitSigneBranch = 0b00001;
unsigned long bitPcBranch = 0b00000111111111111111111111111111;
unsigned long a=0b01101110010101101000100010000011;
printf("%ld\n",a);
int branch;
branch = a>>28;
int z = a>>27;
SigneBranch = z & bitSigneBranch;

printf("SigneBranch : %d\n",SigneBranch);
pcBranch = a & bitPcBranch;
printf("pcBranch = %ld\n", pcBranch);


switch(branch)
{
	default : pc++;
	break;
	
	case 8 : 
	if (SigneBranch==0){pc+=pcBranch;}
	else{pc-=pcBranch;}
	break;
	
	case 9 : 
	if(flagEqual==1){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}	
	break;
	
	case 10 : 
	if(flagEqual==0){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}
	
	case 11 :
	if(flagInf==1 || flagEqual==1){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}	
	break;
	
	case 12 :
	if(flagSup==1 || flagEqual==1){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}	
	break;
	
	case 13 : 
	if(flagSup==1){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}	
	break;
	
	case 14 :
	if(flagSup==1){
		if (SigneBranch==0){pc+=pcBranch;}
		else{pc-=pcBranch;}}
	else{pc++;}	
	break;

}

printf("pc:%d\n",pc);
return 0;
}

//1010 0101 >> 4 

//1010 AND 0111 = 0010

