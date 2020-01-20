#pragma warning(disable:4996)		//ko CRT_NO_
#include "stack.h"
#include <stdio.h>
#include "opcodes.h"

P_NodeI NewBlankElementI() {

	P_NodeI q;
	q = NULL;
	q = (P_NodeI)malloc(sizeof(struct NodeI));
	return q;
}
int PushI(P_NodeI S, unsigned short opC, unsigned short val) {		// S-glava
	P_NodeI q;
	P_NodeI tmp;

	q = NewBlankElementI();
	if (q == NULL)			//MALLOC ERROR
		return ERROR;
	else {
		tmp = S->Next;
		q->opCode = opC;
		q->x = val;
		q->Next = tmp;
		S->Next = q;

		return SUCCESS;
	}
}

int PutLastI(P_NodeI S, unsigned short opC, unsigned short val) {
	P_NodeI q;

	q = NewBlankElementI();
	if (q == NULL)			//MALLOC ERROR
		return ERROR;
	else {
		while (S->Next != NULL)
			S = S->Next;

		q->opCode = opC;
		q->x = val;
		q->Next = NULL;
		S->Next = q;

		return SUCCESS;
	}
}
int PopI(P_NodeI S) {		//pop ne vraca, samo brise u mene

	if (S->Next == NULL)
		return ERROR;		//UNDERFLOW GUARD
	else {
		P_NodeI tmp;

		tmp = S->Next;
		S->Next = tmp->Next;
		free(tmp);

		return SUCCESS;
	}
}

//char PeekI(P_NodeI S) {			!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//	if (S->Next == NULL)
//		return ERROR; //UNDERFLOW PRAZAN STOG
//	else {
//		char x;
//		P_Node tmp;
//
//		tmp = S->Next;
//		x = tmp->el;
//		return x;
//	}
//}
//int IsEmptyI(P_NodeI S) {
//	if (S->Next == NULL)
//		return 1;
//	else return 0;
//}

int PrintStackI(P_NodeI P) {

	P = P->Next;			// ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("nema elemenata");
	else{
		while (P != NULL)
		{
			printf("opCode:%c x:%c \n", P->opCode, P->x);
			P = P->Next;
		}
		printf("\n");
	}

	return SUCCESS;
}

int PrintAsBF(P_NodeI P) {   //vraca dobro samo nakon loop optimizacija

	P = P->Next;			// ne zelis ispisat head pa ides odma na iduci
	if (P == NULL) {
		printf("PrintAsBF: ERROR NO ELEMENTS\n");
		return ERROR;
	}
	else {
		while (P != NULL) {
			switch (P->opCode) {
			case OP_RIGHT: printf(">"); break;
			case OP_LEFT: printf("<"); break;
			case OP_ADD: printf("+"); break;
			case OP_SUB: printf("-"); break;
			case OP_OUTPUT: printf("."); break;
			case OP_INPUT: printf(","); break;
			case OP_WHILE_OPEN:	printf("["); break;
			case OP_WHILE_CLOSE: printf("]"); break;
			}
			P = P->Next;
		}
		printf("\n\n");
	}
}

int PrintAsI(P_NodeI P) {   

	P = P->Next;			// ne zelis ispisat head pa ides odma na iduci
	if (P == NULL) {
		printf("PrintAsI: ERROR NO ELEMENTS\n");
		return ERROR;
	}
	else {
		while (P != NULL) {
			switch (P->opCode) {
			case OP_RIGHT:			printf("p +=%hu\n",P->x);break;
			case OP_LEFT:			printf("p -=%hu\n", P->x);break;
			case OP_ADD:			printf("mem[p] +=%hu\n", P->x);break;
			case OP_SUB:			printf("mem[p] -=%hu\n", P->x);break;
			case OP_OUTPUT:			printf("putchar (mem[p])\n");break;
			case OP_INPUT:			printf("mem[p] = getchar()\n");break;
			case OP_WHILE_OPEN:		printf("while (mem[p]){\n");break;
			case OP_WHILE_CLOSE:	printf("}\n");break;						//bit ce jos
			}
			P = P->Next;
		}
		printf("\n\n");
	}
}

int bfFileToStack(P_NodeI Head) {
	FILE* fp = NULL;
	fp = fopen("in.bf", "r");
	if (fp == NULL)
		return ERROR;

	int c;					//radi EOFa, char = int ionako
	c = 0;

	while ((c = getc(fp)) != EOF) {
		switch (c) {
		case '>': PutLastI(Head, 3, 1); break;
		case '<': PutLastI(Head, 4, 1); break;
		case '+': PutLastI(Head, 1, 1); break;
		case '-': PutLastI(Head, 2, 1); break;
		case '.': PutLastI(Head, 5, 1); break;
		case ',': PutLastI(Head, 6, 1); break;
		case '[': PutLastI(Head, 7, 1); break;
		case ']': PutLastI(Head, 8, 1); break;
		default:						break;
		}
	}
	return SUCCESS;
}

int StacktoCFile(P_NodeI Head) {

}

