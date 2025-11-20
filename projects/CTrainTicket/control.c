#include<stdio.h>
#include<stdlib.h>
#include "string.h"
#include "menu.h"
#include "auth.h"

enum menu_choice
{
    LOGIN_USER = 1,
    LOGIN_ADMIN,
    REGISTER,
    EXIT
};

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// 获取有效的菜单选择
int get_valid_choice(int min, int max) {
    int choice = 0;
    int ch;
    int is_reading = 1;
    
     do{
        printf("请输入您的选择 (%d-%d): ", min, max);
        
        choice = 0;
        is_reading = 1;
        
        // 读取并处理输入
        while (is_reading && (ch = getchar()) != '\n' && ch != EOF) {
            if (ch >= '0' && ch <= '9') {
                choice = choice * 10 + (ch - '0');
            } else {
                is_reading = 0;  // 遇到非数字字符，停止读取
            }
        }
        
        // 验证输入
        if (choice >= min && choice <= max) {
            break;
        }
        
        // 清除可能的剩余输入
        if (ch != '\n') {
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        
        printf("无效选择！请输入 %d-%d 之间的数字。\n", min, max);
    }while (1);
    
    return choice;
}

//退出程序
void exit_program()
{
    printf("退出程序\n");
    //这里可以添加一些清理操作，比如保存数据等
    printf("感谢使用火车订票系统，再见！\n");
    exit(0);
}

//主菜单选择功能
void menu_choice()
{   
    while(1)
    {   
        menu();  // 显示主菜单
        int choice = get_valid_choice(1, 4);
        
        switch(choice)
        {
            case LOGIN_USER:
                login_user();//旅客登录
                break;
            case LOGIN_ADMIN:
                login_admin();//管理员登录
                break;
            case REGISTER:
                register_user();//旅客注册
                break;
            case EXIT:
                exit_program();//退出程序
                break;
            default:
                printf("无效选择，请重新输入\n");
                break;
        }
        
        printf("\n按回车键返回主菜单...");
        getchar();
    }
}

//验证用户名是否合法
int is_username_valid(char *username)
{   
    int len = strlen(username);
    if (len < 3 || len > 20) {
        printf("用户名长度必须在3-20个字符之间！\n");
        return 0;  // 不合法
    }
    return 1;  // 合法
}

//验证身份证是否合法
int is_id_card_valid(char *id_card)
{   
    int len = strlen(id_card);
    if (len != 18) {
        printf("身份证必须为18位！\n");
        return 0;  // 不合法
    }
    
    // 检查是否全部为数字
    for (int i = 0; i < len; i++) {
        if (id_card[i] < '0' || id_card[i] > '9') {
            printf("身份证必须全部为数字！\n");
            return 0;  // 不合法
        }
    }
    
    return 1;  // 合法
}

//验证密码是否合法
int is_password_valid(char *password)
{   
    int len = strlen(password);
    if (len < 6 || len > 20) {
        printf("密码长度必须在6-20个字符之间！\n");
        return 0;  // 不合法
    }
    return 1;  // 合法
}

// 清空文件内容的函数
int clear_file(const char *filename) {
    FILE *fp = fopen(filename, "w");  // 以写入模式打开，会清空文件内容
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        return -1;
    }
    
    fclose(fp);
    printf("成功清空文件：%s\n", filename);
    return 0;
}

