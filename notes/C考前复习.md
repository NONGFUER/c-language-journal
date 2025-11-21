# C语言考试复习指南

## 一、选择题重点知识点

### 1. 基础语法
- **数据类型**：int, float, double, char, void 等的大小和范围
- **变量声明与初始化**：局部变量、全局变量、静态变量
- **运算符优先级**：算术 > 关系 > 逻辑 > 赋值
- **类型转换**：隐式转换和显式转换规则

### 2. 控制结构
- if-else 嵌套的匹配规则
- switch-case 的break重要性
- 循环控制：break, continue的区别
- for循环的三部分执行顺序

### 3. 函数
- 函数声明与定义的区别
- 参数传递：值传递 vs 地址传递
- 递归函数的调用过程
- 函数返回值的类型匹配

### 4. 数组与指针
- 数组下标从0开始
- 指针的算术运算（p+1移动的大小）
- 数组名与指针的关系
- 字符串处理函数的使用

## 二、简答题重点知识点

### 1. 内存管理（重点！）
```c
// 动态内存分配函数对比
malloc(size)    // 分配指定大小的内存，不初始化
calloc(n, size) // 分配n个size大小的内存，初始化为0
realloc(ptr, size) // 重新分配内存大小
free(ptr)      // 释放内存
```

**常见内存错误：**
- 内存泄漏：忘记释放动态分配的内存
- 野指针：使用已释放的内存
- 越界访问：访问超出分配范围的内存

### 2. 文件操作
```c
// 文件操作基本流程
FILE *fp = fopen("file.txt", "r"); // 打开文件
if (fp == NULL) { // 错误检查
    printf("文件打开失败\n");
    return -1;
}
// 读写操作...
fclose(fp); // 关闭文件
```

**文件打开模式：**
- "r"：只读，文件必须存在
- "w"：只写，创建新文件或清空已有文件
- "a"：追加，在文件末尾添加
- "r+"：读写，文件必须存在
- "w+"：读写，创建新文件

### 3. 结构体与联合
```c
// 结构体定义和使用
struct Student {
    char name[20];
    int age;
    float score;
};

struct Student stu;
strcpy(stu.name, "张三");
stu.age = 20;
```

**结构体与联合的区别：**
- 结构体：各成员独立占用内存
- 联合：各成员共享同一块内存

## 三、编程题重点题型

### 1. 基础算法题
**排序算法（冒泡排序）**
```c
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
```

**查找算法（二分查找）**
```c
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

### 2. 字符串处理
```c
// 字符串反转
void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len/2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

// 字符串拷贝（手动实现）
void myStrcpy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
```

### 3. 文件操作编程
```c
// 文件拷贝程序
void copyFile(const char* src, const char* dest) {
    FILE *fp1 = fopen(src, "rb");
    FILE *fp2 = fopen(dest, "wb");
    
    if (fp1 == NULL || fp2 == NULL) {
        printf("文件打开失败\n");
        return;
    }
    
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, 1024, fp1)) > 0) {
        fwrite(buffer, 1, bytes, fp2);
    }
    
    fclose(fp1);
    fclose(fp2);
    printf("文件拷贝完成\n");
}
```

### 4. 结构体应用
```c
// 学生信息管理系统核心函数
struct Student* addStudent(struct Student* students, int* count) {
    if (*count >= MAX_STUDENTS) {
        printf("学生数量已达上限\n");
        return students;
    }
    
    printf("请输入学生姓名: ");
    scanf("%s", students[*count].name);
    printf("请输入学生年龄: ");
    scanf("%d", &students[*count].age);
    printf("请输入学生成绩: ");
    scanf("%f", &students[*count].score);
    
    (*count)++;
    return students;
}
```

## 四、易错点提醒

### 1. 指针相关
- 指针未初始化就使用
- 指针类型不匹配
- 数组越界访问
- 字符串结束符'\0'的重要性

### 2. 内存管理
- malloc后一定要检查返回值是否为NULL
- free后要将指针设为NULL
- 避免重复释放同一块内存

### 3. 文件操作
- 打开文件后一定要检查是否成功
- 读写操作后要检查是否成功
- 文件使用完毕后一定要关闭

### 4. 输入输出
- scanf读取字符串时要防止缓冲区溢出
- printf格式控制符要匹配变量类型
- 注意输入缓冲区残留问题

## 五、考试技巧

1. **选择题**：先排除明显错误的选项，注意细节
2. **简答题**：条理清晰，关键词要准确
3. **编程题**：
   - 先写注释，理清思路
   - 注意变量命名规范
   - 重要步骤要有错误检查
   - 测试边界情况

## 六、重点函数速查

| 类别 | 函数 | 功能 |
|------|------|------|
| 字符串 | strlen(), strcpy(), strcat(), strcmp() | 字符串处理 |
| 内存 | malloc(), free(), calloc(), realloc() | 动态内存管理 |
| 文件 | fopen(), fclose(), fread(), fwrite() | 文件操作 |
| 输入输出 | printf(), scanf(), getchar(), putchar() | 标准I/O |

**祝您考试顺利！**


## 押题

c语言中static关键字的作用有哪些？

1. 修饰局部变量
作用：延长局部变量的生命周期，使其在程序运行期间持续存在 特点：只初始化一次，函数调用间保持值，作用域不变

2. 修饰全局变量
作用：限制全局变量的作用域，使其只能在当前源文件内访问 特点：实现内部链接，避免命名冲突，提高模块化

3. 修饰函数
作用：限制函数的作用域，使其只能在当前源文件内调用 特点：封装内部函数，防止外部调用，避免函数名冲突

核心区别
对局部变量：改变存储期（自动→静态）
对全局变量和函数：改变链接性（外部→内部）
本质：static控制变量的存储期和函数/变量的链接性，实现信息隐藏和状态保持。