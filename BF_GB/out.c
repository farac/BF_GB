#include <stdio.h>
char mem[65536] = { 0 };
int p=0;

int main(){

mem[p] +=1;
while (mem[p]){
mem[p] -=1;
while (mem[p]){
p -=2;
while (mem[p]){
mem[p] +=1;
while (mem[p]){
mem[p] -=3;
p +=1;
}
mem[p] -=1;
while (mem[p]){
p -=3;
}
}
}
p +=3;
mem[p] -=1;
}
while (mem[p]){
}
while (mem[p]){
mem[p] +=1;
}
while (mem[p]){
}
p +=1;
mem[p] -=1;
putchar (mem[p]);
mem[p] -=3;
putchar (mem[p]);
p +=1;
putchar (mem[p]);
putchar (mem[p]);
p +=1;
putchar (mem[p]);
p -=4;
mem[p] -=1;
putchar (mem[p]);
p -=1;
mem[p] +=1;
putchar (mem[p]);
p +=5;
putchar (mem[p]);
p +=1;
putchar (mem[p]);
p -=2;
putchar (mem[p]);
p -=1;
mem[p] -=1;
putchar (mem[p]);

return 0;
}