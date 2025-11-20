#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "menu.h"
#include "types.h"
#include "control.h"
#include "global.h"





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
   
}

void admin_user_list() {
    printf("====旅客用户信息列表显示====\n");
    for (int i = 0; i < user_count; i++) {
        printf("%d---用户名: %s, 身份证号: %s\n",i+1, all_users[i].username, all_users[i].id_card);
    }
    
}
void admin_user_add() {
    printf("🚀 执行：旅客用户增加\n");
    // TODO: 实现增加逻辑
}

void admin_user_delete() {
    printf("🚀 执行：旅客用户删除\n");
    // TODO: 实现删除逻辑
}

void admin_user_modify() {
    printf("🚀 执行：旅客用户修改\n");
    // TODO: 实现修改逻辑
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