#define SUCCESS			0
#define ERROR			-1		

							//char mem[65536] = {0};
							//int p=0;

#define OP_ADD			1	//	+	mem[p] +=x
#define OP_SUB			2	//	-	mem[p] -=x
#define OP_RIGHT		3	//	>	p +=x
#define OP_LEFT			4	//	<	p -=x
#define OP_OUTPUT		5	//	.	putchar (mem[p])
#define OP_INPUT		6	//	,	mem[p] = getchar()
#define OP_WHILE_OPEN	7	//	[	while (mem[p]){
#define OP_WHILE_CLOSE	8	//	]	}
							// OP_CLEAR?, OP_MUL?