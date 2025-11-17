#include<stdio.h>
#include<stdlib.h>

struct S
{
    int a;
    int arr[];
};

// 主函数：演示柔性数组成员的使用方法
// 参数：无
// 返回值：程序执行状态，总是返回0表示正常退出
int main()
{
	//int sz = sizeof(struct S);
    //printf("sz = %d\n", sz);
	// 分配内存空间给结构体及其柔性数组成员，额外分配10个整数的空间
	struct S* ps = malloc(sizeof(struct S) + 10 * sizeof(int));
    if(ps){
        return 1;
    }
    ps->a = 100;
    // 初始化柔性数组成员的元素值
    for(int i = 0; i < 10; i++)
    {
        ps->arr[i] = i;
    }
    // 打印柔性数组成员的所有元素值
    for (int i = 0; i < 10; i++)
    {
       printf("%d\n", ps->arr[i]);
    }
    free(ps); // 释放分配的内存
    ps = NULL;
    return 0;
}