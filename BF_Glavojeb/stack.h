#pragma once //valjda bolje od guardova?
#include <stdio.h>
#include <stdio.h>
//#ifndef STACK_H_INCL
//#define STACK_H_INCL

typedef struct NodeI;	//nodeInstrcution
typedef struct NodeI* P_NodeI;
typedef struct NodeI
{
	unsigned short opCode;
	unsigned short x;
	struct NodeI* Next;
};

int PushI(P_NodeI, unsigned short opC, unsigned short val);
int PopI(P_NodeI);	//pop ne vraca, samo brise u mene, koristi peek
					//u pop posalji onog prije onog sta brises za DelNode
char PeekI(P_NodeI);
int PutLastI(P_NodeI, unsigned short opC, unsigned short val);
P_NodeI NewBlankElementI();
int PrintStackI(P_NodeI);
int PrintAsBF(P_NodeI);
int PrintAsI(P_NodeI);
int BFFileToStack(P_NodeI, char*);
int StackToCFile(P_NodeI, char*);

//#endif // !STACK_H_INCL

