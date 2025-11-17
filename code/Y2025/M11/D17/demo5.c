#include<stdio.h>
#include<stdlib.h>

struct S
{
	int a;
	int* arr;
};
int main() {
    struct S *s = (struct S* )malloc(10*sizeof(struct S)+80);
    if(s == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    s->a = 100;
    s->arr = (int*)malloc(10*sizeof(int));
    if(s->arr == NULL) {
        printf("内存分配失败\n");
      
        return 1;
    }
    for(int i = 0; i < 10; i++){
        s->arr[i] = i;
    }
    // 打印柔性数组成员的所有元素值
    for (int i = 0; i < 10; i++)
    {
       printf("%d\n", s->arr[i]);
    }
    free(s->arr); // 释放分配的内存
    free(s);
    s = NULL;
    return 0;
}