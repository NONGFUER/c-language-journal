#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // 动态分配单个整数
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    *ptr = 42;
    printf("单个整数: %d\n", *ptr);
    free(ptr);

    // 动态分配数组
    int size = 5;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    free(arr);

    // 使用 realloc 扩展内存
    int *data = (int *)malloc(3 * sizeof(int));
    if (data == NULL) return 1;
    for (int i = 0; i < 3; i++) data[i] = i;
    
    data = (int *)realloc(data, 6 * sizeof(int));
    if (data == NULL) return 1;
    for (int i = 3; i < 6; i++) data[i] = i * 10;
    printf("扩展后的数据: ");
    for (int i = 0; i < 6; i++) printf("%d ", data[i]);
    printf("\n");
    free(data);

    return 0;
}