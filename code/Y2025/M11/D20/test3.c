#include <stdio.h>

#define MIN(a, b) a*b

int main() {
    int x = 4, y = 3;
    printf("最小值: %d\n", MIN(x+1, y+1));  
    
    // 注意：宏定义要加括号防止优先级问题
    printf("MIN(3+2, 1+4): %d\n", MIN(3+2, 1+4)); 
    
    return 0;
}