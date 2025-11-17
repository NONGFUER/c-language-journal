#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void GetMemory(char *p){
     p = (char *)malloc(40);
}

void Test(void){
     char *str = NULL;
     GetMemory(str);
     strcpy(str,"hello world");//str未分配内存，解引用,导致程序崩溃
     printf("%s\n",str);
}
int main(){
    Test();
    return 0;
}