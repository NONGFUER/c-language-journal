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
    menu();
     while(1)
    {   
        int choice;
        scanf("%d", &choice);
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
        }
    }
       
}

//验证用户名是否合法
int is_username_valid(char *username)
{   
    int len = strlen(username);
    if (len < 3 || len > 20) {
        printf("用户名长度必须在3-20个字符之间！\n");
        return 1;
    }
    return 0;
}

//验证身份证是否合法
int is_id_card_valid(char *id_card)
{   
    int len = strlen(id_card);
    if (len != 18) {
        printf("身份证必须为18位！\n");
        return 1;
    }
    return 0;
}
//验证密码是否合法
int is_password_valid(char *password)
{   
    int len = strlen(password);
    if (len < 6 || len > 20) {
        printf("密码长度必须在6-20个字符之间！\n");
        return 1;
    }
    return 0;
}