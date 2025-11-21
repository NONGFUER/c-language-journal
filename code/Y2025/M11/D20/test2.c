#include <stdio.h>
#include <math.h>

int main() {
    printf("水仙花数: ");
    for (int i = 100; i < 1000; i++) {
        int a = i / 100;        // 百位
        int b = (i / 10) % 10;  // 十位
        int c = i % 10;         // 个位
        
        if (a*a*a + b*b*b + c*c*c == i) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}