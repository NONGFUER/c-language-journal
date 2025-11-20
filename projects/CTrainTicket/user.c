//用户相关函数实现
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "global.h"



//
void user_menu_choice() {
    while (1) {
        menu_user();  // 显示管理员主菜单
    
        int choice = get_valid_choice(1, 5);
        switch(choice) {
            case 1:
                printf("\n--- 用户基本信息维护 ---\n");
                admin_manage_users();
                break;
                
            case 2:
                printf("\n--- 查询操作 ---\n");
                admin_manage_trains();
                break;
            case 3:
                printf("\n--- 退票操作 ---\n");
                admin_manage_trains();
                break; 
            case 4:
                printf("\n--- 订票操作 ---\n");
                admin_manage_trains();
                break;       
            case 5:
                menu_choice();
                return;  // 退出管理员菜单
                
            default:
                printf("系统错误：无效的选择\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

//读取用户信息
int load_user_info(user *users) {
    FILE *fp = fopen("user_info.txt", "rb");
    if (fp == NULL) {
        printf("打开文件失败\n");
        return 0;
    }
    int count = 0;  
    while (fread(&users[count], sizeof(user), 1, fp))
    {
        count++;
        if (count >= 10) {//后续加入动态分配内存
            printf("用户数量超过10个\n");
            break;
        }
    }
    for(int i = 0; i < count; i++) {
       printf("用户名：%s, 身份证号：%s,密码：%s\n", users[i].username, users[i].id_card,users[i].password);
    }
    fclose(fp);
    printf("count = %d\n", count);
    return count;
}

//保存用户信息到文件
void save_new_user(user *user_info) {
    //
    all_users[user_count] = *user_info;
    user_count++;

    FILE *fp = fopen("user_info.txt", "wb");
    if (fp == NULL) {
        printf("打开文件失败\n");
        user_count--;
        return;
    }
    
    fwrite(all_users, sizeof(user), user_count, fp);
    fclose(fp);
}

// 根据用户名查找用户
user* find_user_by_username(char *username) {
    for(int i = 0; i < user_count; i++) {
        if (strcmp(all_users[i].username, username) == 0) {
            //printf("找到用户：%s\n", all_users[i].username);
            //printf("找到用户：%s\n", all_users[i].password);
            return &all_users[i];
        }
    }
    return NULL;
}

// 检查用户名是否存在,返回1表示存在，0表示不存在
int is_username_exists(char *username) {
    return find_user_by_username(username) != NULL;
}