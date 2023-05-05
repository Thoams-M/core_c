#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h> 
#include "coeur.h"


typedef struct
{
	int branch; 
	int signBrench; 
	int decalage; 
	int iv;
	int opcode;
	int ope1;
	int ope2;
	int dest;
	int valeurIv;
	
}instruction;

instruction decode(coeur cpu)
{
	instruction inst;
	int bitIv = 0b00000001;
	int bitOpcode = 0b000000001111;
	int bitOpe1 = 0b0000000000001111;
	int bitOpe2 = 0b00000000000000001111;
	int bitDest = 0b000000000000000000001111;
	int bitValeurIv = 0b00000000000000000000000011111111;
	
		
		
	inst.iv = (cpu.inst >> 24) & bitIv;
	inst.opcode = (cpu.inst >> 20) & bitOpcode;
	inst.ope1 = (cpu.inst >> 16) & bitOpe1;
	inst.ope2 = (cpu.inst >> 12) & bitOpe2;
	inst.dest = (cpu.inst >> 8) & bitDest;
	inst.valeurIv = cpu.inst & bitValeurIv;
	
	printf("valeur de iv %d \n",inst.iv);
	printf("valeur de inst.opcode %d \n",inst.opcode);
	printf("valeur de inst.ope1 %d \n",inst.ope1);
	printf("valeur de inst.ope2 %d \n",inst.ope2);
	printf("valeur de inst.dest %d \n",inst.dest);
	printf("valeur de inst.valeurIv %d \n",inst.valeurIv);
	
	
	return(inst);
	
	
	
	
	/*
	opcode, the first operand, the second operand, the destination, the
	immediate value (all in hexadecimal) and the immediate value flag
	
	0000    |    000  |  0     |   0000       |    0000          |        0000     |     0000  |   0000 0000
	brench  | set 0   | IV     |  Opcode      |   operand1       |   operand2      |   dest    |  IV
	*/ 



}

coeur execute(instruction inst, coeur cpu)
{
	unsigned long long int Max64Bits = 18446744073709551999;
	switch(inst.opcode)
		{
			case 0 : 
			//AND
				printf("Instruction AND\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] && cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] && inst.valeurIv;}
				break;
			
			case 1 : 
			//OR
				printf("Instruction OR\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] || cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] || inst.valeurIv;}
				break;
			
			case 2 : 
			//XOR
				printf("Instruction XOR\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] ^ cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] ^ inst.valeurIv;}
				break;
			
			case 3 :
			//ADD 
				printf("Instruction ADD\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] + cpu.r[inst.ope2];}
				else{
				cpu.r[inst.dest] = cpu.r[inst.ope1] + inst.valeurIv;
				//printf("cpu.r[inst.dest] = %lld et inst.dest = %d\n", cpu.r[inst.dest], inst.dest);}
				break;
				
			case 4 :
			//ADC
				printf("Instruction ADC\n");
				if(inst.iv == 0)
					{
					if(cpu.r[inst.ope1] + cpu.r[inst.ope2] > Max64Bits)//nombre max pour 64bits
					{
						cpu.r[inst.dest] = (cpu.r[inst.ope1] + cpu.r[inst.ope2]) - (Max64Bits+1);
						cpu.flagADC = 1;
						printf("Cas d'une addition avec retenue, le flagADC est set à 1\n");
						
					}
					else{cpu.r[inst.dest] = cpu.r[inst.ope1] + cpu.r[inst.ope2];}}
				else{
					if(cpu.r[inst.ope1] + inst.valeurIv > Max64Bits)
					{
						cpu.r[inst.dest] = (cpu.r[inst.ope1] + inst.valeurIv) - (Max64Bits+1);
						cpu.flagADC = 1;
						printf("Cas d'une addition avec retenue, le flagADC est set à 1\n");
					}
					else{cpu.r[inst.dest] = cpu.r[inst.ope1] + inst.valeurIv;}
				}
				break;
				
			case 5 :
			//CMP
				printf("Instruction CMP\n");
				if(inst.iv == 0)
				{
					if(cpu.r[inst.ope1] == cpu.r[inst.ope2]){cpu.flagEqual=1;}
					if(cpu.r[inst.ope1] > cpu.r[inst.ope2]){cpu.flagSup=1;}
					if(cpu.r[inst.ope1] < cpu.r[inst.ope2]){cpu.flagInf=1;}
					if(cpu.flagInf == 1 || cpu.flagEqual == 1){cpu.flagInfEqual=1;}
					if(cpu.flagSup == 1 || cpu.flagEqual == 1){cpu.flagSupEqual=1;}
				
				}
				else{
					if(cpu.r[inst.ope1] == inst.valeurIv){cpu.flagEqual=1;}
					if(cpu.r[inst.ope1] > inst.valeurIv){cpu.flagSup=1;}
					if(cpu.r[inst.ope1] < inst.valeurIv){cpu.flagInf=1;}
					if(cpu.flagInf == 1 || cpu.flagEqual == 1){cpu.flagInfEqual=1;}
					if(cpu.flagSup == 1 || cpu.flagEqual == 1){cpu.flagSupEqual=1;}
				}
				break;
			
			case 6 :
			//SUB 
				printf("Instruction SUB\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] - cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] - inst.valeurIv;}
				break;
			
			/*case 7 :
			//SBC
				if(inst.iv == 0)
					if(cpu.r[inst.ope1] < cpu.r[inst.ope2])
					{
						cpu.r[inst.dest] = (cpu.r[inst.ope1] - cpu.r[inst.ope2]) - 4294967296;
						cpu.flagSBC = 1;
					}
					else{cpu.r[inst.dest] = cpu.r[inst.ope1] + cpu.r[inst.ope2];}
				else{
					if(cpu.r[inst.ope1] + inst.valeurIv > 4294967295)
					{
						cpu.r[inst.dest] = (cpu.r[inst.ope1] + inst.valeurIv) - 4294967296;
						cpu.flagADC = 1;
					}
					else{cpu.r[inst.dest] = cpu.r[inst.ope1] + inst.valeurIv;}
				}
				break;*/
				
			case 8 :
			//MOV 
				printf("Instruction MOV\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1];}
				else{cpu.r[inst.dest] = inst.valeurIv;}
				break;	
			
			case 9 :
			//LSH 
				printf("Instruction LSH\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] << cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] << inst.valeurIv;}
				break;
			
			case 10 :
			//RSH 
				printf("Instruction RSH\n");
				if(inst.iv == 0)
				{cpu.r[inst.dest] = cpu.r[inst.ope1] >> cpu.r[inst.ope2];}
				else{cpu.r[inst.dest] = cpu.r[inst.ope1] >> inst.valeurIv;}
				break;
				
		}}
return(cpu);
}

int main()
{
	coeur cpu;
	instruction instDecode;
	cpu.pc = 0;
	
	//initialisation des flags
	cpu.flagEqual=0;
	cpu.flagInf=0;
	cpu.flagSup=0;
	
	//valeur utilisé pour retrouvé les bits qui nous intéresse lorsque l'on cherche le branch
	int SigneBranch;
	unsigned long pcBranch;
	unsigned long bitSigneBranch = 0b00000001;
	unsigned long bitPcBranch = 0b00000000111111111111111111111111;
	
	
	
	
	/*initilisation à 0*/
	for(int registre=0; registre<15; registre++)
	{
		cpu.r[registre]=0;
	}

	//ouverture du fichier
	FILE *fic;
	fic = fopen("sauvegarde.bin", "r+");
		
	if(fic == NULL)
		{
			fprintf(stderr, "Erreur ouverture fichier.\n");
			exit(EXIT_FAILURE);
		}
	//nombre de valeur définis ici
	
	fseek(fic, 0, SEEK_END);	
	int nbrInst = ((ftell(fic))/4)-1;
	fseek(fic, 0, SEEK_SET);
	int instructionFinal[nbrInst];
		
	/*boucle for jusqu'à ce que il n'y ai plus d'instruction 
	ordre : -est ce que c'est un branch --> oui = Analyse branch
					    --> non = decode() et execute()
	*/				      
	for(cpu.pc=0; cpu.pc<nbrInst+1; cpu.pc++){
	
	
	fread(&instructionFinal[cpu.pc], sizeof(instructionFinal[cpu.pc]), 1, fic);
	
	cpu.inst = littleToBig(instructionFinal[cpu.pc]);
	
	//Recherche de la valeur de branch
	int branch;
	branch = cpu.inst>>28;
	
	//le signe de branch se met en negatif et je n'arrive pas à savoir pourquoi 
	//(mon instruction de 32bits est pourtant celle que je veux.)
	int chgmtDeSigne;
	
	if (branch<0){
	chgmtDeSigne=branch*(-1);
	branch=chgmtDeSigne;
	}
	
	if (7 < branch && branch < 15)
	{

		printf("Cas d'un BCC, valeur branch : %d\n",branch);
		//Recherche du signe (24eme bit)
		int z = cpu.inst>>24;
		SigneBranch = z & bitSigneBranch;


		//valeur de ce que l'on va ajouter à l'adressage
		pcBranch = cpu.inst & bitPcBranch;


			switch(branch)
			{
				default : cpu.pc++;
				break;
				
				case 8 : 
				if (SigneBranch==0){cpu.pc+=pcBranch;}
				else{cpu.pc-=pcBranch;}
				break;
				
				case 9 : 
				if(cpu.flagEqual==1){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}	
				break;
				
				case 10 : 
				if(cpu.flagEqual==0){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}
				
				case 11 :
				if(cpu.flagInf==1 || cpu.flagEqual==1){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}	
				break;
				
				case 12 :
				if(cpu.flagSup==1 || cpu.flagEqual==1){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}	
				break;
				
				case 13 : 
				if(cpu.flagSup==1){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}	
				break;
				
				case 14 :
				if(cpu.flagSup==1){
					if (SigneBranch==0){cpu.pc+=pcBranch;}
					else{cpu.pc-=pcBranch;}}
				else{cpu.pc++;}	
				break;

			}
			
		}
	
	instDecode = decode(cpu);
	cpu=execute(instDecode,cpu);
	
	printf("pc : %d\n",cpu.pc+1);
	for(int AfficheR=0; AfficheR<15; AfficheR++)
	{
	printf("Valeur des registre initial 0x%llx\n", cpu.r[AfficheR]);
	}
	
	//Erreur qui s'affiche si le PC est inférieur à 0 où superieur au nombre d'instruction totale
	if(cpu.pc<0 || cpu.pc>nbrInst){
	printf("ERREUR PC < 0 ou Pc > NombreTotalInstruction\n");
	return 0;
	}
	}
		
return 0;
}

