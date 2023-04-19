#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "compilateur.h"


//enum registers {
//	R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15,
//	F0, F1, F2, F3, F4, F5, F6, F7
//};

//enum instr {
//	B, BEQ, BNE, BLE, BGE, BL, B,
//	CMP,
//	MOV, 
//	ADD, ADC, SUB, SBC, 
//	LSH, RSH,
//	AND, ORR, EOR
//};


typedef struct
{
	int brench; 
	int signBrench; 
	int decalage; 
	int iv;
	int opcode;
	int ope1;
	int ope2;
	int dest;
	int valeurIv;
	
}instruction;


int main(void)
{
//compilateur
//addition 5+6

	instruction inst;
	int i,j;
	int brenchOrNot=0;//si c'est 0 pas brench si 1 brench.
	
	char* code[10][10] = {{"MOV","R0","5"},{"MOV","R1","6"},{"ADD","R0","R1"}};   
	
	for (i=0; i<10; i++){
		for (j=0; j<10; j++){
		
		//if//gérer immediate value pour gérer si c'est registre ou valeur direct
		
		//brench
		if(code[i][j]=="B" || code[i][j]=="BEQ" || code[i][j]=="BNE" || code[i][j]=="BLE" || code[i][j]=="BGE" || code[i][j]=="BL" || code[i][j]=="BG")
		{
			brenchOrNot = 1;
			
			if (code[i][j+1] < 0)
			{
			inst.signBrench=1;
			inst.decalage=code[i][j+1];
			}else{
			inst.signBrench=0;
			inst.decalage=code[i][j+1];
			
		}}
		
		if(code[i][j]=="B")
		{inst.brench=0x8;}
		
		if(code[i][j]=="BEQ")
		{inst.brench=0x9;}
		
		if(code[i][j]=="BNE")
		{inst.brench=0xa;}
		
		if(code[i][j]=="BLE")
		{inst.brench=0xb;}
		
		if(code[i][j]=="BGE")
		{inst.brench=0xc;}
		
		if(code[i][j]=="BL")
		{inst.brench=0xd;}
		
		if(code[i][j]=="BG")
		{inst.brench=0xe;}
		
		//opcode
		
		if(code[i][j]=="AND")
		{inst.opcode=0x0;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		
		//printf("code : %s\n",code[i][j]);
		}
		
		if(code[i][j]=="ORR")
		{inst.opcode=0x1;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="EOR")
		{inst.opcode=0x2;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="ADD")
		{inst.opcode=0x3;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="ADC")
		{inst.opcode=0x4;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="CMP")
		{inst.opcode=0x5;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="SUB")
		{inst.opcode=0x6;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="SBC")
		{inst.opcode=0x7;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="MOV")
		{inst.opcode=0x8;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="LSH")
		{inst.opcode=0x9;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		if(code[i][j]=="RSH")
		{inst.opcode=0xa;
		inst.ope1=code[i][j+1];
		inst.ope2=code[i][j+2];
		}
		
		
		}}
	
	FILE *fic;
	
	
	int instructionFinal, instructionFinal2;
	int BigEndian, BigEndian2;
	
	/*inst.brench = "0b1000";
	inst.signBrench = "1";
	inst.valeurIv = "11001";
	*/
	
	
	

	instructionFinal2 = 0b10000000000000000000000000011001; // B 25
	instructionFinal = 0b10001000000000000000000000011011;// B -27
	
	BigEndian = littleToBig(instructionFinal);
	BigEndian2 = littleToBig(instructionFinal2);	
	
	 
	
	
	fic = fopen("sauvegarde.bin", "wba");
	
	if(fic == NULL)
	{
		fprintf(stderr, "Erreur ouverture fichier.\n");
		exit(EXIT_FAILURE);
	}
	
	fwrite(&BigEndian, sizeof(BigEndian), 1, fic);
	fwrite(&BigEndian2, sizeof(BigEndian2), 1, fic);
	
	
	//fread(&BigEndian, sizeof(BigEndian), 1, fic);
	
	//printf("instructionFinal = %d\n", BigEndian);
	
	fclose(fic);


return 0;
}


