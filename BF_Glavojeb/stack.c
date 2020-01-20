#include "stack.h"
#include <stdio.h>

#define SUCCESS		0
#define ERROR		-1

P_Node NewBlankElement() {

	P_Node q;
	q = NULL;
	q = (P_Node)malloc(sizeof(struct Node));
	return q;
}
int Push(P_Node S, char x) { // S-glava
	P_Node q;
	P_Node tmp;

	q = NewBlankElement();
	if (q == NULL) //MALLOC ERROR
		return ERROR;
	else {
		tmp = S->Next;
		q->el = x;
		q->Next = tmp;
		S->Next = q;

		return SUCCESS;
	}
}

int PutLast(P_Node S, char x) {
	P_Node q;

	q = NewBlankElement();
	if (q == NULL) //MALLOC ERROR
		return ERROR;
	else {
		while (S->Next != NULL)
			S = S->Next;

		q->el = x;
		q->Next = NULL;
		S->Next = q;

		return SUCCESS;
	}
}
int Pop(P_Node S) { //pop ne vraca, samo brise u mene

	if (S->Next == NULL)
		return ERROR; //UNDERFLOW GUARD
	else {
		P_Node tmp;

		tmp = S->Next;
		S->Next = tmp->Next;
		free(tmp);

		return SUCCESS;
	}
}

char Peek(P_Node S) {

	if (S->Next == NULL)
		return ERROR; //UNDERFLOW PRAZAN STOG
	else {
		char x;
		P_Node tmp;

		tmp = S->Next;
		x = tmp->el;
		return x;
	}
}
//int IsEmpty(P_Node S) {
//	if (S->Next == NULL)
//		return 1;
//	else return 0;
//}

int PrintStack(P_Node P) {

	P = P->Next; // ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("nema elemenata");
	else
	{
		while (P != NULL)
		{
			printf("%c ", P->el);
			P = P->Next;
		}
		printf("\n");
	}

	return SUCCESS;
}

P_NodeI NewBlankElementI() {

	P_NodeI q;
	q = NULL;
	q = (P_NodeI)malloc(sizeof(struct NodeI));
	return q;
}
int PushI(P_NodeI S, unsigned short opC, unsigned short val) { // S-glava
	P_NodeI q;
	P_NodeI tmp;

	q = NewBlankElementI();
	if (q == NULL) //MALLOC ERROR
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
	if (q == NULL) //MALLOC ERROR
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
int PopI(P_NodeI S) { //pop ne vraca, samo brise u mene

	if (S->Next == NULL)
		return ERROR; //UNDERFLOW GUARD
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

	P = P->Next; // ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("nema elemenata");
	else
	{
		while (P != NULL)
		{
			printf("opCode:%c x:%c \n", P->opCode, P->x);
			P = P->Next;
		}
		printf("\n");
	}

	return SUCCESS;
}

