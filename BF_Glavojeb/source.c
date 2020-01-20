#pragma warning(disable:4996)		//ko CRT_NO_
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "opcodes.h"

int toCFile(P_NodeI);
int optRedundantLoopBegining(P_NodeI);		//prvo runnaj ovi za pocetak wipeat
int optRedundantTrailingLoops(P_NodeI);
int optContraction(P_NodeI);
int optAdding(P_NodeI);
//to do: [-], mnozenja
int main(int argc, char* argv[]) {
	char filenameIN[128] = "in.bf";
	char filenameOUT[128] = "out.c";

	P_NodeI HeadI;
	HeadI = (P_NodeI)malloc(sizeof(struct NodeI));
	HeadI->Next = NULL;


	//if (argc == 1)				//da mos udrit "glavojeb.exe proizvoljno.bf pozelji.c"
	//	*filenameIN = argv[1];
	//else if (argc >= 2)
	//	*filenameOUT = argv[2];

	BFFileToStack(HeadI, filenameIN);
	printf("Loaded code:\n");
	PrintAsBF(HeadI);
	printf("\n\n\n");

	optRedundantLoopBegining(HeadI);
	printf("Removed redundant loops from the begining:\n");
	PrintAsBF(HeadI);
	printf("\n\n\n");

	optRedundantTrailingLoops(HeadI);
	printf("Removed redundant trailing loops:\n");
	PrintAsBF(HeadI);
	printf("\n\n\n");

	optContraction(HeadI);
	printf("Combined multiple calls to same functions:\n");
	PrintAsI(HeadI);
	printf("\n\n\n");

	optAdding(HeadI);
	printf("Combined additive calls to functions:\n");
	PrintAsI(HeadI);
	printf("\n\n\n");	

	StackToCFile(HeadI, filenameOUT);

	return SUCCESS;
}

//pocetna [] petlja je "mrtva" ako je zatvorena, mos brisat
int optRedundantLoopBegining(P_NodeI Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_NodeI Temp, I;
	Temp = NULL;
	I = Head->Next;
	if (I->opCode == OP_WHILE_OPEN) {
		while (I->Next != NULL && I->opCode != OP_WHILE_CLOSE) {
			I = I->Next;
			Temp = I->Next;
		}
		if (I->opCode == OP_WHILE_CLOSE) {
			while (Head->Next != Temp)
				PopI(Head);
		}

	}
	I = Head->Next;									//samo radi incomplete warrninga
	if (I != NULL && I->opCode == OP_WHILE_OPEN)	//provjera null za "file je cili [][][] edgecase
		optRedundantLoopBegining(Head);				//rekurzija za jebat svima mater ako ih vise
	return SUCCESS;
}

//vise [x][y][z] zaredon, brises sve osim prve, redudantne su
int optRedundantTrailingLoops(P_NodeI Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_NodeI I, Prev, From;
	int c=0;		
	Prev = NULL;
	From = NULL;

	I = Head;	
	while (I->Next != NULL) {																	//ova nade Prev odakle pocimamo
		Prev = I;
		I = I->Next;
		if (I->opCode == OP_WHILE_OPEN)										c++;				//broji pocetke zagrada
		if (c==2 && From == NULL)											From = Prev;		//pocetak druge zagrade u nizu
		if (Prev->opCode == OP_WHILE_CLOSE && I->opCode != OP_WHILE_OPEN)	break;				//puca kad ide nesto sta nije [] iza
	}

	
	while (From != NULL && From->Next != I) {
		PopI(From);
	}

	if (I->Next == NULL) { PopI(From); return SUCCESS; }		//kad je zadnji znak OP_WHILE_CLOSE case
	
	if (I->Next == NULL ) return SUCCESS;
	else optRedundantTrailingLoops(I);

}

int optContraction(P_NodeI Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_NodeI I, Prev, PPrev;
	int c = 1;				//uvik "nade jednog", arbitrary samo meni radi logike
	I = Head->Next;
	PPrev = NULL;
	Prev = Head;

	while (I != NULL) {
		if ((I->opCode == OP_ADD || I->opCode == OP_SUB || I->opCode == OP_RIGHT || I->opCode == OP_LEFT) && Prev->opCode == I->opCode) {
			c++;			//kadgod su dva zaredon ista i da su +-<>
		}
		if (c == 2) {		//spaja kad nade dva
			I->x = Prev->x + I->x;
			PopI(PPrev);
			c = 1;

			I = Head->Next;
			PPrev = NULL;				//tiras ga da gleda ispocetka svaki put kad spoji 2, mora pogledat da nigdi ne moze da bi uspia
			Prev = Head;
		}
		PPrev = Prev;
		Prev = I;						
		I = I->Next;
	}

	return SUCCESS;
}

int optAdding(P_NodeI Head) {

	if (Head->Next == NULL)
		return ERROR;
	P_NodeI I, Prev, PPrev;
	
	int opC = 0;
	int c = 0;				
	I = Head->Next;
	PPrev = NULL;
	Prev = Head;

	while (I != NULL) {
		if ((Prev->opCode == OP_ADD && I->opCode == OP_SUB) || (Prev->opCode == OP_RIGHT && I->opCode == OP_LEFT)) {
			c = Prev->x - I->x;
			if (c == 0) { opC = -1; }
		}
		else if ((Prev->opCode == OP_SUB && I->opCode == OP_ADD) || (Prev->opCode == OP_LEFT && I->opCode == OP_RIGHT)) {
			c = I->x - Prev->x;
			if (c == 0) { opC = -1; }
		}
		
		if (c !=0) {		
			if (I->opCode == OP_ADD || I->opCode == OP_SUB) {		//add sub, namisti predznak za operaciju na kraju
				if (c > 0) { opC = OP_ADD; }
				else if (c < 0) { opC = OP_SUB; c = -c; }
			}
			else if (I->opCode == OP_RIGHT || I->opCode == OP_LEFT) {		//
				if (c > 0) { opC = OP_RIGHT; }
				else if (c < 0) { opC = OP_LEFT; c = -c; }
			}

			I->opCode = opC;
			I->x = c;						//izbaci jednog, u drugog upise novu naredbu
			PopI(PPrev);
			c = 0;
				
			I = Head->Next;
			PPrev = NULL;					//tiras ga da gleda ispocetka svaki put kad spoji 2, mora pogledat da nigdi ne moze da bi uspia
			Prev = Head;
			opC = 0;
		}
		else if (c == 0) {
			if (opC == -1) {
				PopI(PPrev);				//izbaci ca oba dva bez uvodenja novog ako su =0
				PopI(PPrev);
				
				I = Head->Next;
				PPrev = NULL;				//tiras ga da gleda ispocetka svaki put kad spoji 2, mora pogledat da nigdi ne moze da bi uspia
				Prev = Head;
				opC = 0;
			}
		}

		PPrev = Prev;
		Prev = I;
		I = I->Next;
	}
	optContraction(Head);				//moras provjerit jel mos opet izravnat posli sta
	return SUCCESS;
}