#include<stdio.h>
#include<stdlib.h>
int main()
 {
    int * ptr = (int *)malloc(40);
    if(ptr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    free(ptr);
    ptr = NULL;
    return 0;

}