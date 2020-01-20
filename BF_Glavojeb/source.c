#pragma warning(disable:4996)		//ko CRT_NO_
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "opcodes.h"

int toCFile(P_NodeI);
int optRedundantLoopBegining(P_NodeI);		//prvo runnaj ovi za pocetak wipeat
int optRedundantTrailingLoops(P_NodeI);
int optContraction(P_NodeI);

int main() {
	P_NodeI HeadI;
	HeadI = (P_NodeI)malloc(sizeof(struct NodeI));
	HeadI->Next = NULL;

	bfFileToStack(HeadI);
	PrintAsBF(HeadI);
	printf("\n\n\n");

	optRedundantLoopBegining(HeadI);
	PrintAsBF(HeadI);
	printf("\n\n\n");

	optRedundantTrailingLoops(HeadI);
	PrintAsBF(HeadI);
	printf("\n\n\n");

	PrintAsI(HeadI);
	printf("\n\n\n");
	

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
	I = Head->Next;						//samo radi incomplete warrninga
	if (I->opCode == OP_WHILE_OPEN)
		optRedundantLoopBegining(Head);	//rekurzija za jebat svima mater ako ih vise
	return SUCCESS;
}

//vise [x][y][z] zaredon, brises sve osim prve, redudantne su
int optRedundantTrailingLoops(P_NodeI Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_NodeI Temp, I, Prev, WTemp;
	int c=0;		
	Temp = NULL;
	Prev = NULL;
	I = Head->Next;
	while (I->Next != NULL && c!=2) {						//dvaput jer prvu ostavljas na miru
		Prev = I;
		I = I->Next;
		if (I->opCode == OP_WHILE_OPEN) c++;
	}
	if (I->opCode == OP_WHILE_OPEN) {						//ignoriran kad svaka [ nema ], kontan da je kod OK
		do {
			I = I->Next;									//ne moze bit NULL jer mora bit makar ]
			while (I->Next != NULL && I->opCode != OP_WHILE_CLOSE) {
				I = I->Next;
				Temp = I->Next;
			}
			WTemp = I->Next;								//useless temp jer ne mos dvaput ->
		} while (WTemp->opCode == OP_WHILE_OPEN);			//da uvati i sve ostale trailing []
		if (Temp == NULL) Temp = I->Next;					//edge case kad je samo []

		if (I->opCode == OP_WHILE_CLOSE) {
			while (Prev->Next != Temp)
				PopI(Prev);
		}
	}
	if (I->Next == NULL)return SUCCESS;
	else optRedundantTrailingLoops(Head);					//provjeri jel pogleda sve i opet zove
}

int optContraction(P_NodeI Head) {
	if (Head->Next == NULL)
		return ERROR;
}