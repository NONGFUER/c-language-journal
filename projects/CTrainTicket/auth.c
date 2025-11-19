// 认证相关功能（登录、注册）
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "types.h"
#include "control.h"
//旅客注册功能
void register_user()
{
    char temp_pwd[20];
    printf("旅客注册\n");
    while(1){
        printf("请输入用户名：\n");
        scanf("%s",user_info[0].username);
        //验证用户名是否合法
        if(!is_username_valid(user_info[0].username)) break;
    }
    while (1)
    {
        printf("请输入身份证号：\n");
        scanf("%s",user_info[0].id_card);
        //验证身份证号是否合法
        if(!is_id_card_valid(user_info[0].id_card)) break;
    }
    while (1)
    {
        printf("请输入密码：\n");
        scanf("%s",temp_pwd);
        if(!is_password_valid(temp_pwd)) break;
    }
    while (1)
    {
        printf("请再输入一次密码：\n");
        scanf("%s",user_info[0].password);
        if(!is_password_valid(user_info[0].password) && strcmp(temp_pwd,user_info[0].password) == 0){
            printf("注册成功！\n");
            printf("用户名：%s\n",user_info[0].username);
            printf("身份证号：%s\n",user_info[0].id_card);
            break;
        }
        else{
            printf("两次输入的密码不一致，请重新输入！\n");
        }
        
    }

 


   
   
}


//旅客登录功能
void login_user()
{ 
    char username[20];//先假设一个用户，后面再定义旅客结构体变量user
    char password[20];//先假设一个用户密码，后面加入旅客结构体变量user
    printf("旅客登录\n");
    printf("请输入用户名：\n");
    scanf("%s", username);//这里要写定义一个旅客结构体变量user，然后通过scanf函数获取用户名并赋值给user.username
    printf("请输入密码：\n");
    scanf("%s", password);
    //这里要通过scanf函数获取密码并赋值给user.password
    //这里要验证用户名和密码是否正确，假设验证通过，则进入旅客菜单
    if (strcmp(username,"sjwu") == 0 && strcmp(password,"123456") == 0) {
        printf("登录成功！\n");
        menu_user();
    } else {
        printf("用户名或密码错误！\n");
        printf("输入用户名或者密码错误3次，将自动退出系统\n");
       
    }
     return;
}

/**
 * 管理员登录功能
 */
void login_admin()
{ 
    printf("管理员登录\n");
    printf("请输入管理员用户名：");
    printf("请输入管理员密码：");
}
