#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "admin.h"
#include "menu.h"
#include "types.h"
#include "control.h"
#include "global.h"
#include "user.h"  // 添加这一行






// 管理员主功能选择
void admin_menu_choice() {
    while (1) {
        menu_admin();  // 显示管理员主菜单
    
        int choice = get_valid_choice(1, 3);
        switch(choice) {
            case 1:
                printf("\n--- 管理旅客用户信息 ---\n");
                admin_manage_users();
                break;
                
            case 2:
                printf("\n--- 管理车次信息 ---\n");
                admin_manage_trains();
                break;
                
            case 3:
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

// 管理旅客用户信息功能选择
void admin_manage_users() {
    while (1) {
        menu_admin_user();  // 显示管理旅客用户信息子菜单
        
        int choice = get_valid_choice(0, 5);
        
        switch(choice) {
            case 1:
                admin_user_query();
                break;
                
            case 2:
                admin_user_list();
                break;
                
            case 3:
                admin_user_add();
                break;
                
            case 4:
                admin_user_delete();
                break;
                
            case 5:
                admin_user_modify();
                break;
                
            case 0:
                 menu_choice();
                return;
                
            default:
                printf("系统错误：无效的选择\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

// 管理车次信息功能选择
void admin_manage_trains() {
    while (1) {
        menu_train();  // 显示管理车次信息子菜单
        
        int choice = get_valid_choice(0, 5);
        
        switch(choice) {
            case 1:  // 对应 a
                admin_train_query();
                break;
                
            case 2:  // 对应 b
                admin_train_list();
                break;
                
            case 3:  // 对应 c
                admin_train_add();
                break;
                
            case 4:  // 对应 d
                admin_train_delete();
                break;
                
            case 5:
                admin_train_modify();
                break;
                
            case 0:
                //返回管理员菜单
                admin_menu_choice();
                return;
                
            default:
                printf("系统错误：无效的选择\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

// 旅客用户查询
void admin_user_query() {
    printf("====旅客用户查询====\n");
    
    if (user_count == 0) {
        printf("当前没有用户数据！\n");
        return;
    }
    
    char search_username[50];
    printf("请输入要查询的用户名：");
    scanf("%s", search_username);
    clear_input_buffer();
    
    user* found_user = find_user_by_username(search_username);
    if (found_user != NULL) {
        printf("\n=== 用户信息详情 ===\n");
        printf("用户名：%s\n", found_user->username);
        printf("身份证号：%s\n", found_user->id_card);
        printf("密码：%s\n", found_user->password);
        printf("====================\n");
    } else {
        printf("未找到用户名为 '%s' 的用户！\n", search_username);
    }
}

void admin_user_list() {
    printf("====旅客用户信息列表显示====\n");
    
    if (user_count == 0) {
        printf("当前没有用户数据！\n");
        return;
    }
    
    printf("\n=== 用户列表 (共%d个用户) ===\n", user_count);
    for (int i = 0; i < user_count; i++) {
        printf("%d. 用户名: %-15s 身份证号: %s\n", 
               i+1, all_users[i].username, all_users[i].id_card);
    }
    printf("===========================\n");
}

void admin_user_add() {
    printf("====旅客用户增加====\n");
    
    if (user_count >= 10) {
        printf("用户数量已达上限(10个)，无法添加新用户！\n");
        return;
    }
    
    user new_user;
    
    // 输入用户名
    while (1) {
        printf("请输入用户名：");
        scanf("%s", new_user.username);
        clear_input_buffer();
        
        if (!is_username_valid(new_user.username)) {
            continue;
        }
        
        if (is_username_exists(new_user.username)) {
            printf("用户名 '%s' 已存在，请重新输入！\n", new_user.username);
            continue;
        }
        
        break;
    }
    
    // 输入身份证号
    while (1) {
        printf("请输入身份证号：");
        scanf("%s", new_user.id_card);
        clear_input_buffer();
        
        if (!is_id_card_valid(new_user.id_card)) {
            continue;
        }
        
        // 检查身份证号是否重复
        int id_exists = 0;
        for (int i = 0; i < user_count; i++) {
            if (strcmp(all_users[i].id_card, new_user.id_card) == 0) {
                id_exists = 1;
                break;
            }
        }
        
        if (id_exists) {
            printf("身份证号 '%s' 已存在，请重新输入！\n", new_user.id_card);
            continue;
        }
        
        break;
    }
    
    // 输入密码
    char temp_pwd[50];
    while (1) {
        printf("请输入密码：");
        scanf("%s", temp_pwd);
        clear_input_buffer();
        
        if (!is_password_valid(temp_pwd)) {
            continue;
        }
        
        printf("请再次输入密码确认：");
        scanf("%s", new_user.password);
        clear_input_buffer();
        
        if (strcmp(temp_pwd, new_user.password) != 0) {
            printf("两次输入的密码不一致，请重新输入！\n");
            continue;
        }
        
        break;
    }
    
    // 保存新用户
    all_users[user_count] = new_user;
    user_count++;
    
    // 更新文件
    FILE *fp = fopen("user_info.txt", "wb");
    if (fp == NULL) {
        printf("文件保存失败！\n");
        user_count--;
        return;
    }
    
    fwrite(all_users, sizeof(user), user_count, fp);
    fclose(fp);
    
    printf("用户 '%s' 添加成功！\n", new_user.username);
}

void admin_user_delete() {
    printf("====旅客用户删除====\n");
    
    if (user_count == 0) {
        printf("当前没有用户数据！\n");
        return;
    }
    
    char delete_username[50];
    printf("请输入要删除的用户名：");
    scanf("%s", delete_username);
    clear_input_buffer();
    
    int found_index = -1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(all_users[i].username, delete_username) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("未找到用户名为 '%s' 的用户！\n", delete_username);
        return;
    }
    
    // 显示要删除的用户信息
    printf("\n=== 要删除的用户信息 ===\n");
    printf("用户名：%s\n", all_users[found_index].username);
    printf("身份证号：%s\n", all_users[found_index].id_card);
    printf("========================\n");
    
    // 确认删除
    printf("确认删除该用户吗？(y/n)：");
    char confirm;
    scanf("%c", &confirm);
    clear_input_buffer();
    
    if (tolower(confirm) == 'y') {
        // 移动数组元素
        for (int i = found_index; i < user_count - 1; i++) {
            all_users[i] = all_users[i + 1];
        }
        user_count--;
        
        // 更新文件
        FILE *fp = fopen("user_info.txt", "wb");
        if (fp == NULL) {
            printf("文件保存失败！\n");
            return;
        }
        
        if (user_count > 0) {
            fwrite(all_users, sizeof(user), user_count, fp);
        } else {
            // 如果用户数为0，清空文件
            fp = fopen("user_info.txt", "w");
            fclose(fp);
        }
        fclose(fp);
        
        printf("用户 '%s' 删除成功！\n", delete_username);
    } else {
        printf("取消删除操作。\n");
    }
}

void admin_user_modify() {
    printf("====旅客用户修改====\n");
    
    if (user_count == 0) {
        printf("当前没有用户数据！\n");
        return;
    }
    
    char modify_username[50];
    printf("请输入要修改的用户名：");
    scanf("%s", modify_username);
    clear_input_buffer();
    
    int found_index = -1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(all_users[i].username, modify_username) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("未找到用户名为 '%s' 的用户！\n", modify_username);
        return;
    }
    
    printf("\n=== 当前用户信息 ===\n");
    printf("用户名：%s\n", all_users[found_index].username);
    printf("身份证号：%s\n", all_users[found_index].id_card);
    printf("密码：%s\n", all_users[found_index].password);
    printf("===================\n");
    
    int choice;
    do {
        printf("\n请选择要修改的信息：\n");
        printf("1. 修改密码\n");
        printf("2. 修改身份证号\n");
        printf("0. 返回\n");
        printf("请输入选择：");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1: {
                char new_password[50];
                char temp_pwd[50];
                
                while (1) {
                    printf("请输入新密码：");
                    scanf("%s", temp_pwd);
                    clear_input_buffer();
                    
                    if (!is_password_valid(temp_pwd)) {
                        continue;
                    }
                    
                    printf("请再次输入新密码确认：");
                    scanf("%s", new_password);
                    clear_input_buffer();
                    
                    if (strcmp(temp_pwd, new_password) != 0) {
                        printf("两次输入的密码不一致，请重新输入！\n");
                        continue;
                    }
                    
                    strcpy(all_users[found_index].password, new_password);
                    break;
                }
                
                // 更新文件
                FILE *fp = fopen("user_info.txt", "wb");
                if (fp == NULL) {
                    printf("文件保存失败！\n");
                    return;
                }
                
                fwrite(all_users, sizeof(user), user_count, fp);
                fclose(fp);
                
                printf("密码修改成功！\n");
                break;
            }
            
            case 2: {
                char new_id_card[20];
                
                while (1) {
                    printf("请输入新身份证号：");
                    scanf("%s", new_id_card);
                    clear_input_buffer();
                    
                    if (!is_id_card_valid(new_id_card)) {
                        continue;
                    }
                    
                    // 检查身份证号是否重复（排除当前用户）
                    int id_exists = 0;
                    for (int i = 0; i < user_count; i++) {
                        if (i != found_index && strcmp(all_users[i].id_card, new_id_card) == 0) {
                            id_exists = 1;
                            break;
                        }
                    }
                    
                    if (id_exists) {
                        printf("身份证号 '%s' 已存在，请重新输入！\n", new_id_card);
                        continue;
                    }
                    
                    strcpy(all_users[found_index].id_card, new_id_card);
                    break;
                }
                
                // 更新文件
                FILE *fp = fopen("user_info.txt", "wb");
                if (fp == NULL) {
                    printf("文件保存失败！\n");
                    return;
                }
                
                fwrite(all_users, sizeof(user), user_count, fp);
                fclose(fp);
                
                printf("身份证号修改成功！\n");
                break;
            }
            
            case 0:
                printf("返回上级菜单。\n");
                break;
                
            default:
                printf("无效的选择，请重新输入！\n");
                break;
        }
    } while (choice != 0);
}

void admin_train_query() {
    printf("🚀 执行：车次查询\n");
    // TODO: 实现查询逻辑
}

void admin_train_list() {
    printf("🚀 执行：车次列表信息显示\n");
    // TODO: 实现列表显示逻辑
}

void admin_train_add() {
    printf("🚀 执行：车次增加\n");
    // TODO: 实现增加逻辑
}

void admin_train_delete() {
    printf("🚀 执行：车次删除\n");
    // TODO: 实现删除逻辑
}

void admin_train_modify() {
    printf("🚀 执行：车次修改\n");
    // TODO: 实现修改逻辑
}