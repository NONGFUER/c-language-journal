//内存管理code练习
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    //int a = 10;//4个字节
    //int arr[10];//40个字节
    //以上是向内存申请空间的方法，申请空间的大小是没法改变的

    //核心就四个函数malloc/free/realloc/calloc
    int arr[10] = {0};
    int *p = (int *)malloc(40);//向内存申请40个字节
    if( p == NULL )
    {
        printf("%s\n",strerror(errno));
        //printf("内存申请失败\n");
        return 1;
    }
    //使用内存
    for(int i=0;i<10;i++)
    {
        p[i] = i*10;
        printf("p[%d]=%d\n",i,p[i]);
    }
    //扩容
     int *ptr = realloc(p,80);//重新申请80个字节的空间
     if( ptr != NULL )
     {
        p = ptr;//指针指向新的空间
     }
      for(int i=0;i<10;i++)
    {
        printf("p[%d]=%d\n",i,p[i]);
    }
    //没有free的话，内存会一直被占用，直到程序结束，操作系统自动回收
    free(p);//释放内存
    p = NULL;
    //==============================
    int *p1 = (int *)calloc(10,sizeof(int));
    if(p1 == NULL )
    {
        printf("%s\n",strerror(errno));
        return 1;
    }
    for(int i=0;i<10;i++)
    {
        printf("p1[%d]=%d\n",i,p1[i]);
    }   
    free(p1);
    p1 = NULL;
    return 0;
}