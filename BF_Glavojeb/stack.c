#pragma warning(disable:4996)		//ko CRT_NO_
#pragma once
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
	if (q == NULL) {
		printf("NewBlankElement: MALLOC ERROR");				//MALLOC ERROR
		return ERROR;
	}
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

	if (S == NULL)
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
		printf("Empty Stack!");
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
			case OP_RIGHT:			printf("p +=%hu;\n",P->x);break;
			case OP_LEFT:			printf("p -=%hu;\n", P->x);break;
			case OP_ADD:			printf("mem[p] +=%hu;\n", P->x);break;
			case OP_SUB:			printf("mem[p] -=%hu;\n", P->x);break;
			case OP_OUTPUT:			printf("putchar (mem[p]);\n");break;
			case OP_INPUT:			printf("mem[p] = getchar();\n");break;
			case OP_WHILE_OPEN:		printf("while (mem[p]){\n");break;
			case OP_WHILE_CLOSE:	printf("}\n");break;						//bit ce jos
			}
			P = P->Next;
		}
		printf("\n\n");
	}
}

int BFFileToStack(P_NodeI Head,char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("bfFileToStack: ERROR OPENING FILE\n");
		return ERROR;
	}

	int c;					//radi EOFa, char = int ionako
	c = 0;

	while ((c = getc(fp)) != EOF) {
		switch (c) {
		case '+': PutLastI(Head, OP_ADD, 1);			break;
		case '-': PutLastI(Head, OP_SUB, 1);			break;
		case '>': PutLastI(Head, OP_RIGHT, 1);			break;
		case '<': PutLastI(Head, OP_LEFT, 1);			break;
		case '.': PutLastI(Head, OP_OUTPUT, 1);			break;
		case ',': PutLastI(Head, OP_INPUT, 1);			break;
		case '[': PutLastI(Head, OP_WHILE_OPEN, 1);		break;
		case ']': PutLastI(Head, OP_WHILE_CLOSE, 1);	break;
		default:										break;
		}
	}
	fclose(fp);
	return SUCCESS;
}

int StackToCFile(P_NodeI P, char* fileName) {
	P = P->Next;				// ne zelis ispisat head pa ides odma na iduci
	FILE* fp = NULL;
	fp = fopen(fileName,"w");
	if (fp == NULL) {
		printf("StackToCFile: ERROR OPENING FILE\n");
		return ERROR;
	}

	if (P == NULL) {
		printf("StackToCFile: ERROR EMPTY STACK!\n");
		return ERROR;
	}

	else {
		fprintf(fp, "#include <stdio.h>;\n");
		fprintf(fp, "char mem[65536] = { 0 };\n");
		fprintf(fp, "int p=0;\n\n");
		fprintf(fp, "int main(){;\n\n");
		while (P != NULL) {
			switch (P->opCode) {
			case OP_RIGHT:			fprintf(fp, "p +=%hu;\n", P->x);			break;
			case OP_LEFT:			fprintf(fp,"p -=%hu;\n", P->x);				break;
			case OP_ADD:			fprintf(fp,"mem[p] +=%hu;\n", P->x);		break;
			case OP_SUB:			fprintf(fp,"mem[p] -=%hu;\n", P->x);		break;
			case OP_OUTPUT:			fprintf(fp,"putchar (mem[p]);\n");			break;
			case OP_INPUT:			fprintf(fp,"mem[p] = getchar();\n");		break;
			case OP_WHILE_OPEN:		fprintf(fp,"while (mem[p]){\n");			break;
			case OP_WHILE_CLOSE:	fprintf(fp,"}\n");						break;				
			}														//bit ce jos
			
			P = P->Next;
		}
		fprintf(fp,"\nreturn 0;\n}");
	}
	fclose(fp);
	return SUCCESS;
}

