// 认证相关功能（登录、注册）
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "user.h"
#include "types.h"
#include "control.h"
#include "admin.h"
#include "global.h"


//旅客登录功能
void login_user()
{ 
    char username[20];
    char password[20];
    int count = 0;
    printf("====旅客登录====\n");
    while(1){
        printf("请输入用户名：\n");
        scanf("%s", username);
        printf("请输入密码：\n");
        scanf("%s", password);
        clear_input_buffer();
        //判断用户名是否存在
        if(is_username_exists(username)){
            user* now_user = find_user_by_username(username);
            if(strcmp(password,now_user->password) == 0){
                printf("登录成功！\n");
                menu_user();
                break;
            }else{
                 count++;
                if(count == 3) {
                    printf("错误次数过多，系统自动退出！\n");
                    exit(0);
                }
                printf("密码错误，请重新输入！\n");
            }             
        }
        else{
            printf("用户名不存在，请重新输入！\n");
        }
    }
     return;
}

/**
 * 管理员登录功能
 */
void login_admin()
{   char username[50];
    char password[50];
    int count = 0;
    printf("=====管理员登录=====\n");
    while(1){
        printf("请输入管理员用户名：");
        scanf("%s", username);
        printf("请输入管理员密码：");
        scanf("%s", password);
        clear_input_buffer();
        if (strcmp(username, adm.username) == 0 && strcmp(password, adm.password) == 0) {
            printf("管理员登录成功！\n");
            admin_menu_choice();
            break;
        }
        else{
            count++;
            if(count == 3) {
                printf("错误次数过多，系统自动退出！\n");
                exit(0);
            };
            printf("用户名或密码错误！\n");
            printf("输入用户名或者密码错误3次，将自动退出系统\n");
        }
        
    }
    
}

//旅客注册功能
void register_user()
{
    char temp_pwd[20];
    user new_user;
    printf("旅客注册\n");
    while(1){
        printf("请输入用户名：\n");
        scanf("%s",new_user.username);
        //验证用户名是否合法
        if(!is_username_valid(new_user.username)) break;
    }
    while (1)
    {
        printf("请输入身份证号：\n");
        scanf("%s",new_user.id_card);
        //验证身份证号是否合法
        if(!is_id_card_valid(new_user.id_card)) break;
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
        scanf("%s",new_user.password);
        if(strcmp(temp_pwd,new_user.password) == 0){
            printf("注册成功！\n");
            printf("用户名：%s\n",new_user.username);
            printf("身份证号：%s\n",new_user.id_card);
            
            //保存用户信息到文件
            save_new_user(&new_user);
            //注册成功后返回主菜单
            menu();
            break;
        }
        else{
            printf("两次输入的密码不一致，请重新输入！\n");
        }
        
    }

 


   
   
}



