#include<stdio.h>
#include<stdlib.h>
#include "compilateur.h"


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
	//unsigned long a=0b01101110010101101000100010000011;
	int BigEndian, BigEndian2;
	int instructionFinal, instructionFinal2;

	FILE *fic;
	fic = fopen("sauvegarde.bin", "r+");
		
	if(fic == NULL)
		{
			fprintf(stderr, "Erreur ouverture fichier.\n");
			exit(EXIT_FAILURE);
		}
		
	fread(&BigEndian, sizeof(BigEndian), 1, fic);
	printf("BigEndian : %d\n",BigEndian);

	fread(&BigEndian2, sizeof(BigEndian2), 1, fic);
	printf("BigEndian2 : %d\n",BigEndian2);
	
	instructionFinal = (-1)*littleToBig(BigEndian);
	instructionFinal2 = (-1)*littleToBig(BigEndian2);



	unsigned long inst = instructionFinal2;
	printf("%ld\n",inst);

	//Recherche de la valeur de branch
	int branch;
	branch = inst>>28;
	//le signe de branch se met en negatif et je n'arrive pas à savoir pourquoi 
	//(mon instruction de 32bits est pourtant celle que je veux.)
	int chgmtDeSigne;
	if (branch<0){chgmtDeSigne=branch*(-1);}
	branch=chgmtDeSigne;
	printf("valeur branch : %d\n",branch);

	//Recherche du signe (27eme bit)
	int z = inst>>27;
	SigneBranch = z & bitSigneBranch;
	printf("SigneBranch : %d\n",SigneBranch);


	//valeur de ce que l'on va ajouter à l'adressage
	pcBranch = inst & bitPcBranch;
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

