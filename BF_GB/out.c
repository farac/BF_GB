#include <stdio.h>
char mem[65536] = { 0 };
int p=0;

int main(){

mem[p] = getchar();
putchar (mem[p]);
mem[p] = getchar();
putchar (mem[p]);
while (mem[p]){
putchar (mem[p]);
mem[p] -=1;
}
while (mem[p]){
mem[p] -=2;
}
mem[p] = getchar();
putchar (mem[p]);
mem[p] = getchar();
putchar (mem[p]);
mem[p] = getchar();

return 0;
}