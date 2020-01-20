#include <stdio.h>;
char mem[65536] = { 0 };
int p=0;

int main(){;

putchar (mem[p]);
while (mem[p]){
mem[p] = getchar();
}
mem[p] -=1;
while (mem[p]){
mem[p] = getchar();
}
putchar (mem[p]);
putchar (mem[p]);
mem[p] +=2;

return 0;
}