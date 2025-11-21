# C语言面试笔试题库

## 📚 目录
- [1. 关键字相关](#1-关键字相关)
- [2. 数据类型与运算符](#2-数据类型与运算符)
- [3. 变量与常量](#3-变量与常量)
- [4. 控制语句](#4-控制语句)
- [5. 数组与排序算法](#5-数组与排序算法)
- [6. 指针](#6-指针)
- [7. 函数](#7-函数)
- [8. 结构体/共用体/枚举](#8-结构体共用体枚举)
- [9. 内存管理](#9-内存管理)

---

## 1. 关键字相关

### 🔍 面试题1：static的特点
**问题：** 请说明static关键字的特点。

**标准答案：**
1. **限制作用域**：static修饰的变量或函数只在定义它的文件内可见
2. **延长生命周期**：static局部变量在函数调用结束后不会被销毁，保持其值
3. **存放位置**：static变量存放在静态存储区（.data或.bss段）
4. **初值**：未初始化的static变量自动初始化为0

**示例代码：**
```c
#include <stdio.h>

void test_static() {
    static int count = 0;  // 只在第一次调用时初始化
    count++;
    printf("Count: %d\n", count);
}

int main() {
    test_static();  // 输出: Count: 1
    test_static();  // 输出: Count: 2
    test_static();  // 输出: Count: 3
    return 0;
}
```

### 🔍 面试题2：如何引用一个其他文件中的全局变量
**问题：** 如何在当前文件中引用另一个文件中定义的全局变量？

**标准答案：**
使用`extern`关键字声明外部变量。

**示例代码：**
```c
// file1.c
int global_var = 100;

// file2.c
extern int global_var;  // 声明外部变量

void func() {
    printf("Global variable: %d\n", global_var);
}
```

### 🔍 面试题3：sizeof和strlen的区别
**问题：** 请说明sizeof和strlen的区别。

**标准答案：**
| 特性 | sizeof | strlen |
|------|--------|--------|
| 类型 | 运算符 | 函数 |
| 作用 | 计算数据类型或变量所占内存大小 | 计算字符串长度（不包括'\0'） |
| 参数 | 可以是类型或变量 | 必须是字符串指针 |
| 编译时 | 编译时确定 | 运行时确定 |

**示例代码：**
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "hello";
    
    printf("sizeof(str): %zu\n", sizeof(str));  // 输出: 6 (包括'\0')
    printf("strlen(str): %zu\n", strlen(str));  // 输出: 5 (不包括'\0')
    
    return 0;
}
```

### 🔍 面试题4：const的特点
**问题：** 请说明const关键字的特点。

**标准答案：**
1. **常量性**：const修饰的变量值不可修改
2. **指针const**：
   - `const int *p`：指向常量的指针（指针可变，值不可变）
   - `int *const p`：常量指针（指针不可变，值可变）
   - `const int *const p`：指向常量的常量指针（指针和值都不可变）
3. **函数参数**：const参数表示函数内不会修改该参数

**示例代码：**
```c
#include <stdio.h>

int main() {
    int a = 10, b = 20;
    
    // 指向常量的指针
    const int *p1 = &a;
    // *p1 = 30;  // 错误：不能修改指向的值
    p1 = &b;      // 正确：可以修改指针指向
    
    // 常量指针
    int *const p2 = &a;
    *p2 = 30;     // 正确：可以修改指向的值
    // p2 = &b;   // 错误：不能修改指针指向
    
    return 0;
}
```

### 🔍 面试题5：typedef和define区别
**问题：** 请说明typedef和define的区别。

**标准答案：**
| 特性 | typedef | define |
|------|---------|--------|
| 处理时机 | 编译时 | 预处理时 |
| 作用域 | 遵循C语言作用域规则 | 文件作用域 |
| 类型检查 | 有类型检查 | 无类型检查，简单文本替换 |
| 指针定义 | 更安全 | 容易出错 |

**示例代码：**
```c
#include <stdio.h>

typedef int * INT_PTR;
#define INT_DEF int *

int main() {
    INT_PTR a, b;    // a和b都是int指针
    INT_DEF c, d;    // c是int指针，d是int变量
    
    printf("sizeof(a): %zu\n", sizeof(a));  // 指针大小
    printf("sizeof(c): %zu\n", sizeof(c));  // 指针大小
    printf("sizeof(d): %zu\n", sizeof(d));  // int大小
    
    return 0;
}
```

---

## 2. 数据类型与运算符

### 📝 笔试题1：计算类型的取值范围
**问题：** 计算char、unsigned char、int类型的取值范围。

**标准答案：**
```c
#include <stdio.h>
#include <limits.h>

int main() {
    printf("char范围: %d ~ %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char范围: 0 ~ %u\n", UCHAR_MAX);
    printf("int范围: %d ~ %d\n", INT_MIN, INT_MAX);
    
    // 手动计算
    printf("char: -128 ~ 127 (即 -2^7 ~ 2^7-1)\n");
    printf("unsigned char: 0 ~ 255\n");
    printf("int: -2^31 ~ 2^31-1\n");
    
    return 0;
}
```

### 📝 笔试题2：将一个数的某一位置1或清零
**问题：** 写出将一个数的某一位置1或清零的表达式。

**标准答案：**
```c
#include <stdio.h>

// 将第n位置1
#define SET_BIT(x, n) ((x) |= (1 << (n)))

// 将第n位清零
#define CLEAR_BIT(x, n) ((x) &= ~(1 << (n)))

// 检查第n位是否为1
#define CHECK_BIT(x, n) ((x) & (1 << (n)))

int main() {
    unsigned char num = 0b10101010;  // 170
    
    SET_BIT(num, 0);     // 将第0位置1
    printf("置1后: 0x%02X\n", num);  // 输出: 0xAB
    
    CLEAR_BIT(num, 1);   // 将第1位清零
    printf("清零后: 0x%02X\n", num);  // 输出: 0xA9
    
    return 0;
}
```

### 📝 笔试题3：用宏定义表示出两个数中的最小值
**问题：** 用宏定义表示出两个数中的最小值。

**标准答案：**
```c
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int x = 10, y = 20;
    printf("最小值: %d\n", MIN(x, y));  // 输出: 10
    
    // 注意：宏定义要加括号防止优先级问题
    printf("MIN(3+2, 1+4): %d\n", MIN(3+2, 1+4));  // 正确: 5
    
    return 0;
}
```

---

## 3. 变量与常量

### 🔍 面试题6：全局变量和局部变量的区别
**问题：** 请说明全局变量和局部变量的区别。

**标准答案：**
| 特性 | 全局变量 | 局部变量 |
|------|----------|----------|
| 存放位置 | 静态存储区(.data/.bss) | 栈区 |
| 生命周期 | 程序运行期间 | 函数调用期间 |
| 作用域 | 整个程序 | 定义它的函数或代码块内 |
| 初值 | 未初始化时为0 | 未初始化时为随机值 |
| 定义位置 | 函数外部 | 函数内部 |

**示例代码：**
```c
#include <stdio.h>

int global_var;  // 全局变量，自动初始化为0

void test() {
    int local_var;  // 局部变量，未初始化值为随机
    static int static_var;  // 静态局部变量，自动初始化为0
    
    printf("全局变量: %d\n", global_var);
    printf("局部变量: %d (随机值)\n", local_var);
    printf("静态局部变量: %d\n", static_var);
    
    static_var++;
}

int main() {
    test();
    test();
    return 0;
}
```

---

## 4. 控制语句

### 📝 笔试题4：打印水仙花数
**问题：** 打印所有的水仙花数（三位数，各位数字立方和等于该数本身）。

**标准答案：**
```c
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
```

### 📝 笔试题5：打印99乘法表
**问题：** 打印99乘法表。

**标准答案：**
```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d×%d=%-2d ", j, i, i*j);
        }
        printf("\n");
    }
    return 0;
}
```

### 📝 笔试题6：打印图案
**问题：** 打印如下图案：

**标准答案：**
```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
```

---

## 5. 数组与排序算法

### 📝 笔试题7：冒泡排序
**问题：** 实现冒泡排序算法。

**标准答案：**
```c
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    bubble_sort(arr, n);
    
    printf("排序后: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
```

### 📝 笔试题8：打印斐波那契数列前15个数
**问题：** 打印斐波那契数列前15个数。

**标准答案：**
```c
#include <stdio.h>

int main() {
    int n = 15;
    long long fib[15];
    
    fib[0] = 0;
    fib[1] = 1;
    
    printf("斐波那契数列前15个数: ");
    printf("%lld %lld ", fib[0], fib[1]);
    
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        printf("%lld ", fib[i]);
    }
    printf("\n");
    
    return 0;
}
```

### 📝 笔试题9：打印杨辉三角前10行
**问题：** 打印杨辉三角前10行。

**标准答案：**
```c
#include <stdio.h>

int main() {
    int rows = 10;
    int triangle[10][10];
    
    // 初始化杨辉三角
    for (int i = 0; i < rows; i++) {
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        
        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }
    
    // 打印杨辉三角
    printf("杨辉三角前10行:\n");
    for (int i = 0; i < rows; i++) {
        // 打印前导空格，使其居中
        for (int k = 0; k < rows - i - 1; k++) {
            printf("  ");
        }
        
        for (int j = 0; j <= i; j++) {
            printf("%4d", triangle[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

---

## 6. 指针

### 🔍 面试题7：说一说对指针的理解
**问题：** 请说一说你对指针的理解。

**标准答案：**
1. **本质**：指针是存储内存地址的变量
2. **类型**：指针有类型，决定了指针运算的步长
3. **运算**：支持算术运算（+,-,++,--）和关系运算
4. **多级指针**：可以有多级指针（如二级指针、三级指针）
5. **应用**：动态内存分配、函数参数传递、数组操作等

**示例代码：**
```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;        // 一级指针
    int **pp = &p;      // 二级指针
    
    printf("a的值: %d\n", a);
    printf("p指向的值: %d\n", *p);
    printf("pp指向的指针指向的值: %d\n", **pp);
    
    return 0;
}
```

### 🔍 面试题8：指针和数组的区别
**问题：** 请说明指针和数组的区别。

**标准答案：**
| 特性 | 指针 | 数组 |
|------|------|------|
| 本质 | 变量，存储地址 | 常量，代表连续内存空间 |
| 大小 | 固定（通常4或8字节） | 元素个数×元素大小 |
| 赋值 | 可以指向不同地址 | 数组名是常量，不能赋值 |
| sizeof | 返回指针大小 | 返回整个数组大小 |
| 运算 | 支持指针算术运算 | 数组名可退化为指针 |

**示例代码：**
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *p = arr;
    
    printf("sizeof(arr): %zu\n", sizeof(arr));  // 20
    printf("sizeof(p): %zu\n", sizeof(p));      // 4或8
    
    // p = p + 1;  // 正确：指针可以移动
    // arr = arr + 1;  // 错误：数组名是常量
    
    return 0;
}
```

### 🔍 面试题9：指针数组和数组指针的区别
**问题：** 请说明指针数组和数组指针的区别。

**标准答案：**
1. **指针数组**：数组，元素是指针
   - 格式：`int *arr[5]`
   - 含义：包含5个int指针的数组
2. **数组指针**：指针，指向数组
   - 格式：`int (*arr)[5]`
   - 含义：指向包含5个int元素的数组的指针

**示例代码：**
```c
#include <stdio.h>

int main() {
    int a = 1, b = 2, c = 3;
    
    // 指针数组
    int *ptr_arr[3] = {&a, &b, &c};
    printf("指针数组: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", *ptr_arr[i]);
    }
    printf("\n");
    
    // 数组指针
    int arr[3] = {10, 20, 30};
    int (*arr_ptr)[3] = &arr;
    printf("数组指针: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", (*arr_ptr)[i]);
    }
    printf("\n");
    
    return 0;
}
```

### 📝 笔试题10：二级指针访问数据，函数传参
**问题：** 使用二级指针进行函数传参。

**标准答案：**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocate_memory(char **str) {
    *str = (char *)malloc(100 * sizeof(char));
    if (*str != NULL) {
        strcpy(*str, "Hello, World!");
    }
}

int main() {
    char *text = NULL;
    allocate_memory(&text);  // 传递二级指针
    
    if (text != NULL) {
        printf("分配的内容: %s\n", text);
        free(text);
    }
    
    return 0;
}
```

---

## 7. 函数

### 📝 笔试题11：实现两个数据交互的代码，分析打印结果
**问题：** 实现两个数据交互的代码，并分析打印结果。

**标准答案：**
```c
#include <stdio.h>

// 值传递（错误示例）
void swap_wrong(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// 地址传递（正确示例）
void swap_correct(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    
    printf("交换前: x=%d, y=%d\n", x, y);
    
    swap_wrong(x, y);
    printf("错误交换后: x=%d, y=%d\n", x, y);  // 值未改变
    
    swap_correct(&x, &y);
    printf("正确交换后: x=%d, y=%d\n", x, y);  // 值已交换
    
    return 0;
}
```

### 📝 笔试题12：void fun(int a[100]){ sizeof(a) }
**问题：** 分析`void fun(int a[100]){ sizeof(a) }`中sizeof(a)的结果。

**标准答案：**
```c
#include <stdio.h>

void fun(int a[100]) {
    printf("函数内sizeof(a): %zu\n", sizeof(a));  // 输出指针大小
}

int main() {
    int arr[100];
    printf("主函数内sizeof(arr): %zu\n", sizeof(arr));  // 输出400（100×4）
    
    fun(arr);
    return 0;
}
```
**解释：** 数组作为函数参数时会退化为指针，所以sizeof(a)返回的是指针大小而不是数组大小。

### 📝 笔试题13：写出strlen、strcpy、strcat源码实现
**问题：** 写出strlen、strcpy、strcat函数的源码实现。

**标准答案：**
```c
#include <stdio.h>

// strlen实现
size_t my_strlen(const char *str) {
    const char *p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

// strcpy实现
char *my_strcpy(char *dest, const char *src) {
    char *p = dest;
    while ((*p++ = *src++) != '\0') {
        // 空循环，完成复制
    }
    return dest;
}

// strcat实现
char *my_strcat(char *dest, const char *src) {
    char *p = dest;
    
    // 找到dest的结尾
    while (*p != '\0') {
        p++;
    }
    
    // 追加src
    while ((*p++ = *src++) != '\0') {
        // 空循环，完成追加
    }
    
    return dest;
}

int main() {
    char str1[50] = "Hello";
    char str2[] = " World";
    
    printf("字符串长度: %zu\n", my_strlen(str1));
    
    my_strcpy(str1, "Hello");
    printf("复制后: %s\n", str1);
    
    my_strcat(str1, str2);
    printf("连接后: %s\n", str1);
    
    return 0;
}
```

### 🔍 面试题10：说一说对函数的理解
**问题：** 请说一说你对函数的理解。

**标准答案：**
1. **模块化**：将复杂问题分解为小函数，提高代码可读性和可维护性
2. **代码复用**：相同功能可以多次调用，避免代码重复
3. **参数传递**：
   - 值传递：形参是实参的副本，修改不影响实参
   - 地址传递：传递地址，可以修改实参的值
4. **返回值**：函数可以返回一个值，也可以返回指针（指针函数）
5. **递归**：函数可以调用自身，解决分治问题

**示例代码：**
```c
#include <stdio.h>

// 递归函数示例：计算阶乘
long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 指针函数示例：返回字符串
char *get_greeting() {
    return "Hello, World!";
}

int main() {
    printf("5的阶乘: %ld\n", factorial(5));
    printf("问候语: %s\n", get_greeting());
    return 0;
}
```

---

## 8. 结构体/共用体/枚举

### 🔍 面试题11：结构体的字节对齐原则
**问题：** 请说明结构体的字节对齐原则。

**标准答案：**
1. **对齐规则**：
   - 结构体成员的偏移量必须是其类型大小的整数倍
   - 结构体总大小必须是最大成员大小的整数倍
2. **pragma pack**：可以使用`#pragma pack(n)`指定对齐字节数
3. **填充字节**：编译器会自动插入填充字节以满足对齐要求

**示例代码：**
```c
#include <stdio.h>

struct Example1 {
    char a;     // 1字节
    // 3字节填充
    int b;      // 4字节
    char c;     // 1字节
    // 3字节填充
};  // 总大小: 1 + 3 + 4 + 1 + 3 = 12字节

struct Example2 {
    int a;      // 4字节
    char b;     // 1字节
    char c;     // 1字节
    // 2字节填充
};  // 总大小: 4 + 1 + 1 + 2 = 8字节

int main() {
    printf("Example1大小: %zu\n", sizeof(struct Example1));
    printf("Example2大小: %zu\n", sizeof(struct Example2));
    return 0;
}
```

### 🔍 面试题12：什么是大小端？如何验证大小端？
**问题：** 什么是大小端？如何验证大小端？

**标准答案：**
1. **大端模式**：高位字节存储在低地址
2. **小端模式**：低位字节存储在低地址
3. **验证方法**：使用联合体或指针检查内存布局

**示例代码：**
```c
#include <stdio.h>

// 方法1：使用联合体
union EndianTest {
    int num;
    char bytes[4];
};

// 方法2：使用指针
int check_endian() {
    int num = 1;
    return *(char *)&num == 1;  // 返回1表示小端，0表示大端
}

int main() {
    // 方法1验证
    union EndianTest test;
    test.num = 0x12345678;
    
    if (test.bytes[0] == 0x12) {
        printf("大端模式\n");
    } else if (test.bytes[0] == 0x78) {
        printf("小端模式\n");
    }
    
    // 方法2验证
    if (check_endian()) {
        printf("小端模式\n");
    } else {
        printf("大端模式\n");
    }
    
    return 0;
}
```

### 🔍 面试题13：结构体和共用体的区别
**问题：** 请说明结构体和共用体的区别。

**标准答案：**
| 特性 | 结构体(struct) | 共用体(union) |
|------|---------------|---------------|
| 内存使用 | 各成员独立占用内存 | 所有成员共享同一块内存 |
| 大小 | 各成员大小之和（考虑对齐） | 最大成员的大小 |
| 赋值影响 | 修改一个成员不影响其他成员 | 修改一个成员会覆盖其他成员 |
| 应用场景 | 存储相关数据的集合 | 节省内存，同一时间只使用一个成员 |

**示例代码：**
```c
#include <stdio.h>

struct Student {
    int id;
    char name[20];
    float score;
};  // 大小约28字节（考虑对齐）

union Data {
    int i;
    float f;
    char str[20];
};  // 大小20字节

int main() {
    printf("结构体大小: %zu\n", sizeof(struct Student));
    printf("共用体大小: %zu\n", union Data);
    
    union Data data;
    data.i = 10;
    printf("整数: %d\n", data.i);
    
    data.f = 3.14;
    printf("浮点数: %f\n", data.f);  // 整数值被覆盖
    
    return 0;
}
```

### 🔍 面试题14：枚举和define区别
**问题：** 请说明枚举和define的区别。

**标准答案：**
| 特性 | 枚举(enum) | 宏定义(define) |
|------|------------|----------------|
| 类型安全 | 有类型检查 | 无类型检查，文本替换 |
| 调试 | 调试时可看到枚举值名称 | 调试时看到的是数字 |
| 作用域 | 遵循C语言作用域规则 | 文件作用域 |
| 自动赋值 | 枚举值自动递增 | 需要手动指定值 |

**示例代码：**
```c
#include <stdio.h>

// 枚举定义
enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

// 宏定义
#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_BLUE 2

int main() {
    enum Color c = RED;
    
    switch (c) {
        case RED:
            printf("红色\n");
            break;
        case GREEN:
            printf("绿色\n");
            break;
        case BLUE:
            printf("蓝色\n");
            break;
    }
    
    return 0;
}
```

---

## 9. 内存管理

### 🔍 面试题15：栈区和堆区的区别
**问题：** 请说明栈区和堆区的区别。

**标准答案：**
| 特性 | 栈区(Stack) | 堆区(Heap) |
|------|-------------|------------|
| 管理方式 | 系统自动管理 | 手动管理(malloc/free) |
| 分配速度 | 快 | 慢 |
| 内存大小 | 较小，固定 | 较大，动态 |
| 生命周期 | 函数调用期间 | 手动控制 |
| 碎片问题 | 无 | 可能有内存碎片 |
| 应用 | 局部变量、函数参数 | 动态数据结构、大内存块 |

**示例代码：**
```c
#include <stdio.h>
#include <stdlib.h>

void stack_example() {
    int stack_var = 10;  // 栈区变量
    printf("栈区变量: %d\n", stack_var);
}  // 函数结束，stack_var自动释放

void heap_example() {
    int *heap_var = (int *)malloc(sizeof(int));  // 堆区变量
    *heap_var = 20;
    printf("堆区变量: %d\n", *heap_var);
    free(heap_var);  // 必须手动释放
}

int main() {
    stack_example();
    heap_example();
    return 0;
}
```

### 🔍 面试题16：什么内存泄漏？
**问题：** 什么是内存泄漏？

**标准答案：**
**内存泄漏**是指程序在运行过程中，动态分配的内存没有被正确释放，导致该内存无法被再次使用。

**主要原因：**
1. malloc后忘记free
2. 指针被重新赋值前未释放原内存
3. 异常情况下未执行free

**示例代码：**
```c
#include <stdio.h>
#include <stdlib.h>

// 内存泄漏示例
void memory_leak() {
    int *ptr = (int *)malloc(100 * sizeof(int));
    // 使用ptr...
    // 忘记free(ptr);  // 内存泄漏！
}

// 正确做法
void no_memory_leak() {
    int *ptr = (int *)malloc(100 * sizeof(int));
    if (ptr != NULL) {
        // 使用ptr...
        free(ptr);  // 正确释放
    }
}

int main() {
    memory_leak();      // 内存泄漏
    no_memory_leak();   // 正确释放
    return 0;
}
```

### 🔍 面试题17：什么是野指针？
**问题：** 什么是野指针？

**标准答案：**
**野指针**是指指向无效内存地址的指针。

**产生原因：**
1. 指针未初始化
2. 指针指向的内存被释放后未置NULL
3. 指针操作越界

**示例代码：**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 情况1：未初始化指针
    int *wild_ptr1;  // 野指针
    // printf("%d\n", *wild_ptr1);  // 未定义行为
    
    // 情况2：释放后未置NULL
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 10;
    free(ptr);  // 释放内存
    // ptr现在成为野指针
    // printf("%d\n", *ptr);  // 未定义行为
    
    // 正确做法：释放后置NULL
    ptr = NULL;
    
    return 0;
}
```

### 🔍 面试题18：产生段错误的原因？怎么解决段错误？
**问题：** 产生段错误的原因？怎么解决段错误？

**标准答案：**
**段错误(Segmentation Fault)** 是程序访问了不允许访问的内存地址。

**常见原因：**
1. 访问空指针
2. 访问已释放的内存
3. 数组越界访问
4. 栈溢出
5. 修改字符串常量

**解决方法：**
1. 使用调试器(gdb)定位错误
2. 检查指针是否为空
3. 检查内存是否已释放
4. 检查数组边界
5. 使用valgrind等工具检测内存问题

**示例代码：**
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 情况1：访问空指针
    // int *ptr = NULL;
    // printf("%d\n", *ptr);  // 段错误
    
    // 情况2：数组越界
    // int arr[5] = {1, 2, 3, 4, 5};
    // printf("%d\n", arr[10]);  // 段错误
    
    // 情况3：修改字符串常量
    // char *str = "hello";
    // str[0] = 'H';  // 段错误
    
    // 正确做法：使用字符数组
    char str[] = "hello";
    str[0] = 'H';  // 正确
    
    printf("%s\n", str);
    
    return 0;
}
```

---

## 🎯 总结

本试题库涵盖了C语言面试和笔试中的核心知识点，包括：
- **基础概念**：数据类型、运算符、变量常量
- **控制结构**：分支、循环、控制语句
- **数据结构**：数组、指针、函数
- **高级特性**：结构体、共用体、枚举
- **内存管理**：栈、堆、内存泄漏、段错误

**学习建议：**
1. 理解每个概念的本质，不要死记硬背
2. 多动手编写代码，验证理论理解
3. 使用调试工具分析程序运行过程
4. 结合实际项目经验，深入理解内存管理

**祝您学习顺利，面试成功！** 🚀
