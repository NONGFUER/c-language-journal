
//一元多次方程的相加，是顺序表的应用
//还没写完，学完顺序表再写
#include <stdio.h>

#define LIST_INIT_SIZE = 100; //初始化顺序表的分配量

typedef struct 
{
    float p;    //系数
    int e;       //指数
}Polynomial;

typedef struct 
{
    Polynomial *elem;   //存储空间的基地址
    int length; //当前长度
}SqList;
