#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


#define SUCCESS			0
#define ERROR			-1

							//char mem[65536] = {0};
							//int p=0;

#define OP_ADD			1	//	mem[p] +=x
#define OP_SUB			2	//	mem[p] -=x
#define OP_RIGHT		3	//	p +=x;
#define OP_LEFT			4	//	p -=x-
#define OP_OUTPUT		5	//	putchar (mem[p])
#define OP_INPUT		6	//	mem[p] = getchar()
#define OP_WHILE_OPEN	7	//	while (mem[p]){
#define OP_WHILE_CLOSE	8	//	}

int bfFileToStack(P_Node);
int toIStack(P_Node, P_NodeI);
int toCFile(P_Node);
int optRedundantLoopBegining(P_Node); //prvo runnaj ovi za pocetak wipeat
int optRedundantTrailingLoops(P_Node);

int main() {
	P_Node BFHead;
	BFHead = (P_Node)malloc(sizeof(struct Node));
	BFHead->Next = NULL;
	
	P_NodeI HeadI;
	HeadI = (P_NodeI)malloc(sizeof(struct NodeI));
	HeadI->Next = NULL;

	bfFileToStack(BFHead);
	PrintStack(BFHead);
	printf("\n\n\n");

	optRedundantLoopBegining(BFHead);
	PrintStack(BFHead);
	printf("\n\n\n");

	optRedundantTrailingLoops(BFHead);
	PrintStack(BFHead);
	printf("\n\n\n");

	toIStack(BFHead, HeadI);
	free(BFHead);
	PrintStackI(HeadI);

}

int bfFileToStack(P_Node Head) {
	FILE* fp = NULL;
	fp = fopen("in.bf", "r");
	if (fp == NULL) 
		return ERROR;

	int c; //radi EOFa, char = int ionako
	c = 0;
	
	while ((c = getc(fp)) != EOF) {
		if(c=='>'||c=='<'||c=='+'||c=='-'||c=='.'||c==','||c=='['||c==']')
		 PutLast(Head, c); 
	}
}

int toIStack(P_Node Head, P_NodeI HeadI) {
	int c = 1;
	P_Node Temp = Head;
	while (Head->Next != NULL && Temp!= NULL) {			//branin se od Temp = NULL errora
		Head = Head->Next;
		Temp = Head->Next;
		//if (Temp = NULL) break; zadnje doda breakove triba vidit sta jebe
		switch (Head->el) {
		case '+':
			if (Head->el == '+' && Temp->el =='+') {		//<,>,+ i - se optimizira tako
				c++;										//da gledan kolko se puta 
				Head = Head->Next;							//ponavljaju i saljen jednu naredbu
				Temp = Head->Next;
															
			}
			PutLastI(HeadI, OP_ADD, c);
			c = 1;
			break;
		case '-':
			if (Head->el == '-' && Temp->el == '-') {
				c++;
				Head = Head->Next;
				Temp = Head->Next;
			}
			PutLastI(HeadI, OP_SUB, c);
			c = 1;
			break;
		case '>':
			if (Head->el == '>' && Temp->el == '>') {
				c++;
				Head = Head->Next;
				Temp = Head->Next;
			}
			PutLastI(HeadI, OP_RIGHT, c);
			c = 1;
			break;
		case '<':
			if (Head->el == '<' && Temp->el == '<') {
				c++;
				Head = Head->Next;
				Temp = Head->Next;
			}
			PutLastI(HeadI, OP_LEFT , 0);
			c = 1;
			break;
		case '.':
			PutLastI(HeadI, OP_OUTPUT, 0); break;
		case ',':
			PutLastI(HeadI, OP_INPUT, 0); break;
		case '[':
			PutLastI(HeadI, OP_WHILE_OPEN, 0); break;
		case ']':
			PutLastI(HeadI, OP_WHILE_CLOSE, 0); break;
		}
		
	}
	return SUCCESS;
}

int toCFile(P_Node Head) {

}

//pocetna [] petlja je "mrtva" ako je zatvorena, mos brisat
int optRedundantLoopBegining(P_Node Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_Node Temp, I;
	Temp = NULL;
	I = Head->Next;
	if (I->el == '[') {
		while (I->Next != NULL && I->el != ']') {
			I = I->Next;
			Temp = I->Next;
		}
		if (I->el == ']') {
			while (Head->Next != Temp)
				Pop(Head);
		}

	}
	I = Head->Next;		//samo radi incomplete warrninga
	if (I->el == '[')
		optRedundantLoopBegining(Head);	//rekurzija za jebat svima mater ako ih vise
	return SUCCESS;
}

//vise [x][y][z] zaredon, brises sve osim prve, redudantne su
int optRedundantTrailingLoops(P_Node Head) {
	if (Head->Next == NULL)
		return ERROR;
	P_Node Temp, I, Prev, WTemp;
	int c=0;		
	Temp = NULL;
	Prev = NULL;
	I = Head->Next;
	while (I->Next != NULL && c!=2) {	//dvaput jer prvu ostavljas na miru
		Prev = I;
		I = I->Next;
		if (I->el == '[') c++; 
	}
	if (I->el == '[') {		//ignoriran kad svaka [ nema ], kontan da je kod OK
		do {
			I = I->Next;		//ne moze bit NULL jer mora bit makar ]
			while (I->Next != NULL && I->el != ']') {
				I = I->Next;
				Temp = I->Next;
			}
			WTemp = I->Next;	//useless temp jer ne mos dvaput ->
		} while (WTemp->el == '[');			//da uvati i sve ostale trailing []
		if (Temp == NULL) Temp = I->Next;	//edge case kad je samo []

		if (I->el == ']') {
			while (Prev->Next != Temp)
				Pop(Prev);
		}
	}
		return SUCCESS;
}