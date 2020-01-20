#pragma once //valjda bolje od guardova?
#include <stdio.h>
#include <stdio.h>
//#ifndef STACK_H_INCL
//#define STACK_H_INCL

typedef struct Node;
typedef struct Node* P_Node;
typedef struct Node
{
	char el;
	struct node* Next;
	//struct node* Prev;
};

typedef struct NodeI;	//nodeInstrcution
typedef struct NodeI* P_NodeI;
typedef struct NodeI
{
	unsigned short opCode;
	unsigned short x;
	struct NodeI* Next;
};

int Push(P_Node, char);
int Pop(P_Node);	//pop ne vraca, samo brise u mene, koristi peek
					//u pop posalji onog prije onog sta brises za DelNode
char Peek(P_Node);
int PutLast(P_Node, char);
P_Node NewBlankElement();
int PrintStack(P_Node);


int PushI(P_NodeI, unsigned short opC, unsigned short val);
int PopI(P_NodeI);	//pop ne vraca, samo brise u mene, koristi peek
					//u pop posalji onog prije onog sta brises za DelNode
char PeekI(P_NodeI);
int PutLastI(P_NodeI, unsigned short opC, unsigned short val);
P_NodeI NewBlankElementI();
int PrintStackI(P_Node);

//#endif // !STACK_H_INCL

