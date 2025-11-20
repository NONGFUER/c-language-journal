#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "admin.h"
#include "menu.h"
#include "types.h"
#include "control.h"
#include "global.h"
#include "user.h"

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
                printf("返回主菜单...\n");
                menu_choice();  // 调用主菜单函数
                return;
                
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
                printf("返回管理员菜单...\n");
                admin_menu_choice();  // 调用管理员菜单函数
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
    // 加载车次信息
    load_train_info();
    
    while (1) {
        menu_train();  // 显示管理车次信息子菜单
        
        int choice = get_valid_choice(0, 5);
        
        switch(choice) {
            case 1:
                admin_train_query();
                break;
                
            case 2:
                admin_train_list();
                break;
                
            case 3:
                admin_train_add();
                break;
                
            case 4:
                admin_train_delete();
                break;
                
            case 5:
                admin_train_modify();
                break;
                
            case 0:
                printf("返回管理员菜单...\n");
                admin_menu_choice();  // 调用管理员菜单函数
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
            // 在admin_user_modify函数中修改输入部分
            case 1: {
            char new_password[50];
            while (1) {
            printf("请输入新密码：");
            fgets(new_password, sizeof(new_password), stdin);
            // 去除换行符
            new_password[strcspn(new_password, "\n")] = 0;
            
            if (!is_password_valid(new_password)) {
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
                    fgets(new_id_card, sizeof(new_id_card), stdin);
                    // 去除换行符
                    new_id_card[strcspn(new_id_card, "\n")] = 0;
                    
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

// 车次相关全局变量定义
train all_trains[50];
int train_count = 0;

// 加载车次信息
void load_train_info() {
    FILE *fp = fopen("train_info.txt", "rb");
    if (fp == NULL) {
        printf("车次信息文件不存在，将创建新文件。\n");
        return;
    }
    
    train_count = 0;
    while (fread(&all_trains[train_count], sizeof(train), 1, fp) == 1) {
        train_count++;
        if (train_count >= 50) break;
    }
    fclose(fp);
    
    printf("成功加载 %d 个车次信息。\n", train_count);
}
// 保存车次信息
void save_train_info() {
    FILE *fp = fopen("train_info.txt", "wb");
    if (fp == NULL) {
        printf("车次信息文件保存失败！\n");
        return;
    }
    
    if (train_count > 0) {
        fwrite(all_trains, sizeof(train), train_count, fp);
    }
    fclose(fp);
}

// 车次查询
void admin_train_query() {
    printf("====车次查询====\n");
    
    if (train_count == 0) {
        printf("当前没有车次数据！\n");
        return;
    }
    
    int choice;
    printf("请选择查询方式：\n");
    printf("1. 按车次查询\n");
    printf("2. 按始发站查询\n");
    printf("3. 按终点站查询\n");
    printf("0. 返回\n");
    printf("请输入选择：");
    scanf("%d", &choice);
    clear_input_buffer();
    
    char search_key[30];
    int found = 0;
    
    switch (choice) {
        case 1:
            printf("请输入车次：");
            fgets(search_key, sizeof(search_key), stdin);
            // 去除换行符
            search_key[strcspn(search_key, "\n")] = 0;
            
            printf("\n=== 查询结果 ===\n");
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].train_number, search_key) == 0) {
                    printf("车次：%s\n", all_trains[i].train_number);
                    printf("始发站：%s\n", all_trains[i].start_station);
                    printf("终点站：%s\n", all_trains[i].end_station);
                    printf("出发时间：%s\n", all_trains[i].departure_time);
                    printf("到达时间：%s\n", all_trains[i].arrival_time);
                    printf("票价：%.2f元\n", all_trains[i].price);
                    printf("总座位数：%d\n", all_trains[i].total_seats);
                    printf("余票：%d\n", all_trains[i].remaining_tickets);
                    printf("状态：%s\n", all_trains[i].is_active ? "启用" : "停用");
                    printf("================\n");
                    found = 1;
                    break;
                }
            }
            break;
            
        case 2:
            printf("请输入始发站：");
            fgets(search_key, sizeof(search_key), stdin);
            // 去除换行符
            search_key[strcspn(search_key, "\n")] = 0;
            
            printf("\n=== 查询结果 ===\n");
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].start_station, search_key) == 0) {
                    printf("%d. 车次：%s | 终点站：%s | 出发时间：%s | 票价：%.2f元 | 余票：%d\n", 
                           i+1, all_trains[i].train_number, all_trains[i].end_station,
                           all_trains[i].departure_time, all_trains[i].price, all_trains[i].remaining_tickets);
                    found = 1;
                }
            }
            break;
            
        case 3:
            printf("请输入终点站：");
            fgets(search_key, sizeof(search_key), stdin);
            // 去除换行符
            search_key[strcspn(search_key, "\n")] = 0;
            
            printf("\n=== 查询结果 ===\n");
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].end_station, search_key) == 0) {
                    printf("%d. 车次：%s | 始发站：%s | 出发时间：%s | 票价：%.2f元 | 余票：%d\n", 
                           i+1, all_trains[i].train_number, all_trains[i].start_station,
                           all_trains[i].departure_time, all_trains[i].price, all_trains[i].remaining_tickets);
                    found = 1;
                }
            }
            break;
            
        case 0:
            printf("返回上级菜单。\n");
            return;
            
        default:
            printf("无效的选择！\n");
            return;
    }
    
    if (!found && choice != 0) {
        printf("未找到符合条件的车次！\n");
    }
}

// 车次列表信息显示
void admin_train_list() {
    printf("====车次列表信息显示====\n");
    
    if (train_count == 0) {
        printf("当前没有车次数据！\n");
        return;
    }
    
    printf("\n=== 车次列表 (共%d个车次) ===\n", train_count);
    for (int i = 0; i < train_count; i++) {
        printf("%d. 车次：%-8s | 始发站：%-10s | 终点站：%-10s | 出发时间：%s | 票价：%.2f元 | 余票：%d | 状态：%s\n", 
               i+1, all_trains[i].train_number, all_trains[i].start_station, all_trains[i].end_station,
               all_trains[i].departure_time, all_trains[i].price, all_trains[i].remaining_tickets,
               all_trains[i].is_active ? "启用" : "停用");
    }
    printf("===========================\n");
}

// 车次增加
void admin_train_add() {
    printf("====车次增加====\n");
    
    if (train_count >= 50) {
        printf("车次数量已达上限(50个)，无法添加新车次！\n");
        return;
    }
    
    train new_train;
    
    // 输入车次
    while (1) {
        printf("请输入车次：");
        fgets(new_train.train_number, sizeof(new_train.train_number), stdin);
        // 去除换行符
        new_train.train_number[strcspn(new_train.train_number, "\n")] = 0;
        
        // 检查车次是否重复
        int train_exists = 0;
        for (int i = 0; i < train_count; i++) {
            if (strcmp(all_trains[i].train_number, new_train.train_number) == 0) {
                train_exists = 1;
                break;
            }
        }
        
        if (train_exists) {
            printf("车次 '%s' 已存在，请重新输入！\n", new_train.train_number);
            continue;
        }
        
        if (strlen(new_train.train_number) == 0) {
            printf("车次不能为空！\n");
            continue;
        }
        
        break;
    }
    
    // 输入始发站
    printf("请输入始发站：");
    fgets(new_train.start_station, sizeof(new_train.start_station), stdin);
    // 去除换行符
    new_train.start_station[strcspn(new_train.start_station, "\n")] = 0;

    // 输入终点站
    printf("请输入终点站：");
    fgets(new_train.end_station, sizeof(new_train.end_station), stdin);
    // 去除换行符
    new_train.end_station[strcspn(new_train.end_station, "\n")] = 0;

    // 输入出发时间
    printf("请输入出发时间(HH:MM)：");
    fgets(new_train.departure_time, sizeof(new_train.departure_time), stdin);
    // 去除换行符
    new_train.departure_time[strcspn(new_train.departure_time, "\n")] = 0;
    
    // 输入到达时间
    printf("请输入到达时间(HH:MM)：");
    fgets(new_train.arrival_time, sizeof(new_train.arrival_time), stdin);
    // 去除换行符
    new_train.arrival_time[strcspn(new_train.arrival_time, "\n")] = 0;
    
    // 输入票价
    printf("请输入票价：");
    scanf("%f", &new_train.price);
    clear_input_buffer();
    
    // 输入总座位数
    printf("请输入总座位数：");
    scanf("%d", &new_train.total_seats);
    clear_input_buffer();
    
    // 设置初始余票数等于总座位数
    new_train.remaining_tickets = new_train.total_seats;
    new_train.is_active = 1;  // 默认启用
    
    // 保存新车次
    all_trains[train_count] = new_train;
    train_count++;
    
    // 更新文件
    save_train_info();
    
    printf("车次 '%s' 添加成功！\n", new_train.train_number);
}

// 车次删除
void admin_train_delete() {
    printf("====车次删除====\n");
    
    if (train_count == 0) {
        printf("当前没有车次数据！\n");
        return;
    }
    
    char delete_train_number[10];
    printf("请输入要删除的车次：");
    fgets(delete_train_number, sizeof(delete_train_number), stdin);
    // 去除换行符
    delete_train_number[strcspn(delete_train_number, "\n")] = 0;
    
    int found_index = -1;
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].train_number, delete_train_number) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("未找到车次 '%s'！\n", delete_train_number);
        return;
    }
    
    // 显示要删除的车次信息
    printf("\n=== 要删除的车次信息 ===\n");
    printf("车次：%s\n", all_trains[found_index].train_number);
    printf("始发站：%s\n", all_trains[found_index].start_station);
    printf("终点站：%s\n", all_trains[found_index].end_station);
    printf("出发时间：%s\n", all_trains[found_index].departure_time);
    printf("票价：%.2f元\n", all_trains[found_index].price);
    printf("========================\n");
    
    // 确认删除
    printf("确认删除该车次吗？(y/n)：");
    char confirm;
    scanf("%c", &confirm);
    clear_input_buffer();
    
    if (tolower(confirm) == 'y') {
        // 移动数组元素
        for (int i = found_index; i < train_count - 1; i++) {
            all_trains[i] = all_trains[i + 1];
        }
        train_count--;
        
        // 更新文件
        save_train_info();
        
        printf("车次 '%s' 删除成功！\n", delete_train_number);
    } else {
        printf("取消删除操作。\n");
    }
}

// 车次修改
void admin_train_modify() {
    printf("====车次修改====\n");
    
    if (train_count == 0) {
        printf("当前没有车次数据！\n");
        return;
    }
    
    char modify_train_number[10];
    printf("请输入要修改的车次：");
    fgets(modify_train_number, sizeof(modify_train_number), stdin);
    // 去除换行符
    modify_train_number[strcspn(modify_train_number, "\n")] = 0;
    
    int found_index = -1;
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].train_number, modify_train_number) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("未找到车次 '%s'！\n", modify_train_number);
        return;
    }
    
    printf("\n=== 当前车次信息 ===\n");
    printf("车次：%s\n", all_trains[found_index].train_number);
    printf("始发站：%s\n", all_trains[found_index].start_station);
    printf("终点站：%s\n", all_trains[found_index].end_station);
    printf("出发时间：%s\n", all_trains[found_index].departure_time);
    printf("到达时间：%s\n", all_trains[found_index].arrival_time);
    printf("票价：%.2f元\n", all_trains[found_index].price);
    printf("总座位数：%d\n", all_trains[found_index].total_seats);
    printf("余票：%d\n", all_trains[found_index].remaining_tickets);
    printf("状态：%s\n", all_trains[found_index].is_active ? "启用" : "停用");
    printf("===================\n");
    
    int choice;
    do {
        printf("\n请选择要修改的信息：\n");
        printf("1. 修改始发站\n");
        printf("2. 修改终点站\n");
        printf("3. 修改出发时间\n");
        printf("4. 修改到达时间\n");
        printf("5. 修改票价\n");
        printf("6. 修改总座位数\n");
        printf("7. 启用/停用车次\n");
        printf("0. 返回\n");
        printf("请输入选择：");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                printf("请输入新始发站：");
                scanf("%s", all_trains[found_index].start_station);
                clear_input_buffer();
                printf("始发站修改成功！\n");
                break;
                
            case 2:
                printf("请输入新终点站：");
                scanf("%s", all_trains[found_index].end_station);
                clear_input_buffer();
                printf("终点站修改成功！\n");
                break;
                
            case 3:
                printf("请输入新出发时间(HH:MM)：");
                scanf("%s", all_trains[found_index].departure_time);
                clear_input_buffer();
                printf("出发时间修改成功！\n");
                break;
                
            case 4:
                printf("请输入新到达时间(HH:MM)：");
                scanf("%s", all_trains[found_index].arrival_time);
                clear_input_buffer();
                printf("到达时间修改成功！\n");
                break;
                
            case 5:
                printf("请输入新票价：");
                scanf("%f", &all_trains[found_index].price);
                clear_input_buffer();
                printf("票价修改成功！\n");
                break;
                
            case 6:
                printf("请输入新总座位数：");
                scanf("%d", &all_trains[found_index].total_seats);
                clear_input_buffer();
                printf("总座位数修改成功！\n");
                break;
                
            case 7:
                all_trains[found_index].is_active = !all_trains[found_index].is_active;
                printf("车次状态已%s！\n", all_trains[found_index].is_active ? "启用" : "停用");
                break;
                
            case 0:

                printf("返回上级菜单。\n");
                admin_manage_trains();
                break;
                
            default:
                printf("无效的选择，请重新输入！\n");
                break;
        }
        
        // 更新文件
        if (choice != 0) {
            save_train_info();
        }
    } while (choice != 0);
}