//用户相关函数实现
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "global.h"
#include "control.h"
#include "user.h"
#include "menu.h"
#include "ticket.h"  // 添加车票头文件

// 全局变量声明
extern user all_users[10];
extern int user_count;
extern train all_trains[50];
extern int train_count;

// 用户菜单选择
void user_menu_choice(user *current_user) {
    while (1) {
        menu_user();  // 显示用户菜单
    
        int choice = get_valid_choice(1, 5);
        switch(choice) {
            case 1:
                printf("\n--- 用户基本信息维护 ---\n");
                user_info_maintenance(current_user);
                break;
                
            case 2:
                printf("\n--- 查询操作 ---\n");
                user_query_operation(current_user);
                break;
                
            case 3:
                printf("\n--- 退票操作 ---\n");
                user_cancel_ticket_operation(current_user);
                break;
                
            case 4:
                printf("\n--- 订票操作 ---\n");
                user_book_ticket_operation(current_user);
                break;
                
            case 5:
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

// 用户基本信息维护
void user_info_maintenance(user *current_user) {
    while (1) {
        printf("\n=== 用户基本信息维护 ===\n");
        printf("1. 修改密码\n");
        printf("2. 查看详细信息\n");
        printf("0. 返回上级菜单\n");
        printf("请输入选择：");
        
        int choice = get_valid_choice(0, 2);
        
        switch(choice) {
            case 1:
                user_change_password(current_user);
                break;
                
            case 2:
                user_view_details(current_user);
                break;
                
            case 0:
                printf("返回用户菜单...\n");
                user_menu_choice(current_user);  // 调用用户菜单函数
                return;
                
            default:
                printf("无效的选择！\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

// 修改密码
void user_change_password(user *current_user) {
    char new_password[50];
    char confirm_password[50];
    
    printf("\n=== 修改密码 ===\n");
    printf("当前用户：%s\n", current_user->username);
    
    printf("请输入新密码：");
    fgets(new_password, sizeof(new_password), stdin);
    // 去除换行符
    new_password[strcspn(new_password, "\n")] = 0;
    
    if (!is_password_valid(new_password)) {
        printf("密码不合法！\n");
        return;
    }
    
    printf("请确认新密码：");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    // 去除换行符
    confirm_password[strcspn(confirm_password, "\n")] = 0;
    
    if (strcmp(new_password, confirm_password) != 0) {
        printf("两次输入的密码不一致！\n");
        return;
    }
    
    strcpy(current_user->password, new_password);
    printf("密码修改成功！\n");
    
    // 保存用户信息到文件
    save_user_info();
}

// 查看详细信息
void user_view_details(user *current_user) {
    printf("\n=== 用户详细信息 ===\n");
    printf("用户名：%s\n", current_user->username);
    printf("身份证号：%s\n", current_user->id_card);
    printf("密码：%s\n", current_user->password);
    printf("已订车票数量：%d\n", current_user->ticket_count);
    
    if (current_user->ticket_count > 0) {
        printf("\n=== 已订车票列表 ===\n");
        for (int i = 0; i < current_user->ticket_count; i++) {
            printf("%d. 车次：%s | 座位号：%s | 状态：%s\n", 
                   i+1, current_user->booked_tickets[i].train_number,
                   current_user->booked_tickets[i].seat_number,
                   current_user->booked_tickets[i].is_booked ? "有效" : "已退票");
        }
    }
}

// 用户查询操作
void user_query_operation(user *current_user) {
    while (1) {
        printf("\n=== 查询操作子菜单 ===\n");
        printf("1. 查询已订的车票信息\n");
        printf("2. 查询火车的车票信息\n");
        printf("0. 返回上级菜单\n");
        printf("请输入选择：");
        
        int choice = get_valid_choice(0, 2);
        
        switch(choice) {
            case 1:
                user_query_booked_tickets(current_user);
                break;
                
            case 2:
                user_train_ticket_submenu(current_user);
                break;
                
            case 0:
                printf("返回用户菜单...\n");
                user_menu_choice(current_user);  // 调用用户菜单函数
                return;
                
            default:
                printf("无效的选择！\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

// 火车车票查询子菜单
void user_train_ticket_submenu(user *current_user) {
    while (1) {
        printf("\n=== 火车车票查询子菜单 ===\n");
        printf("a. 按车次查询车票信息\n");
        printf("b. 按始发站查询车票信息\n");
        printf("c. 按终点站查询车票信息\n");
        printf("0. 返回上级菜单\n");
        printf("请输入选择：");
        
        char choice;
        scanf(" %c", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 'a':
            case 'A':
                user_query_train_tickets_by_number();
                break;
                
            case 'b':
            case 'B':
                user_query_train_tickets_by_start();
                break;
                
            case 'c':
            case 'C':
                user_query_train_tickets_by_end();
                break;
                
            case '0':
                printf("返回查询操作菜单...\n");
                user_query_operation(current_user);
                return;  // 这里返回到user_query_operation函数
                
            default:
                printf("无效的选择！\n");
                break;
        }
        
        printf("\n按回车键继续...");
        getchar();
    }
}

// 按车次查询车票信息
void user_query_train_tickets_by_number() {
    char train_number[10];
    printf("请输入车次：");
    fgets(train_number, sizeof(train_number), stdin);
    // 去除换行符
    train_number[strcspn(train_number, "\n")] = 0;
    
    int found = 0;
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].train_number, train_number) == 0 && all_trains[i].is_active) {
            printf("\n=== 车次信息详情 ===\n");
            printf("车次：%s\n", all_trains[i].train_number);
            printf("始发站：%s\n", all_trains[i].start_station);
            printf("终点站：%s\n", all_trains[i].end_station);
            printf("出发时间：%s\n", all_trains[i].departure_time);
            printf("到达时间：%s\n", all_trains[i].arrival_time);
            printf("票价：%.2f元\n", all_trains[i].price);
            printf("总座位数：%d\n", all_trains[i].total_seats);
            printf("余票：%d\n", all_trains[i].remaining_tickets);
            
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("未找到车次 '%s' 的信息！\n", train_number);
    }
}

// 按始发站查询车票信息
void user_query_train_tickets_by_start() {
    char start_station[30];
    printf("请输入始发站：");
    fgets(start_station, sizeof(start_station), stdin);
    // 去除换行符
    start_station[strcspn(start_station, "\n")] = 0;
    
    int found_count = 0;
    printf("\n=== 查询结果 ===\n");
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].start_station, start_station) == 0 && all_trains[i].is_active) {
            printf("%d. 车次：%s | 终点站：%s | 出发时间：%s | 票价：%.2f元 | 余票：%d\n",
                   found_count+1, all_trains[i].train_number, all_trains[i].end_station,
                   all_trains[i].departure_time, all_trains[i].price, all_trains[i].remaining_tickets);
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("未找到始发站为 '%s' 的车次！\n", start_station);
    }
}

// 按终点站查询车票信息
void user_query_train_tickets_by_end() {
    char end_station[30];
    printf("请输入终点站：");
    fgets(end_station, sizeof(end_station), stdin);
    // 去除换行符
    end_station[strcspn(end_station, "\n")] = 0;
    
    int found_count = 0;
    printf("\n=== 查询结果 ===\n");
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].end_station, end_station) == 0 && all_trains[i].is_active) {
            printf("%d. 车次：%s | 始发站：%s | 出发时间：%s | 票价：%.2f元 | 余票：%d\n",
                   found_count+1, all_trains[i].train_number, all_trains[i].start_station,
                   all_trains[i].departure_time, all_trains[i].price, all_trains[i].remaining_tickets);
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("未找到终点站为 '%s' 的车次！\n", end_station);
    }
}

// 用户订票操作
void user_book_ticket_operation(user *current_user) {
    printf("==== 订票操作 ====\n");
    
    if (train_count == 0) {
        printf("当前没有可订的车次信息！\n");
        return;
    }
    
    // 显示可订车次列表
    printf("\n=== 可订车次列表 ===\n");
    int available_count = 0;
    train available_trains[50];
    
    for (int i = 0; i < train_count; i++) {
        if (all_trains[i].is_active && all_trains[i].remaining_tickets > 0) {
            available_trains[available_count] = all_trains[i];
            printf("%d. 车次：%s | %s → %s | 出发：%s | 票价：%.2f元 | 余票：%d\n",
                   available_count+1, available_trains[available_count].train_number,
                   available_trains[available_count].start_station, available_trains[available_count].end_station,
                   available_trains[available_count].departure_time, available_trains[available_count].price,
                   available_trains[available_count].remaining_tickets);
            available_count++;
        }
    }
    
    if (available_count == 0) {
        printf("当前没有可订的车次！\n");
        return;
    }
    
    printf("请选择要订票的车次 (1-%d)，输入0取消：", available_count);
    int choice = get_valid_choice(0, available_count);
    
    if (choice == 0) {
        printf("订票操作已取消。\n");
        return;
    }
    
    // 执行订票
    if (book_ticket(current_user, &available_trains[choice-1])) {
        // 更新全局车次数据
        for (int i = 0; i < train_count; i++) {
            if (strcmp(all_trains[i].train_number, available_trains[choice-1].train_number) == 0) {
                all_trains[i].remaining_tickets--;
                break;
            }
        }
    }
}

// 用户退票操作
void user_cancel_ticket_operation(user *current_user) {
    printf("==== 退票操作 ====\n");
    
    if (current_user->ticket_count == 0) {
        printf("您当前没有已订车票，无法退票！\n");
        return;
    }
    
    // 显示已订车票列表
    user_query_booked_tickets(current_user);
    
    printf("请选择要退票的车票编号 (1-%d)，输入0取消：", current_user->ticket_count);
    int choice = get_valid_choice(0, current_user->ticket_count);
    
    if (choice == 0) {
        printf("退票操作已取消。\n");
        return;
    }
    
    // 执行退票
    if (cancel_ticket(current_user, choice-1)) {
        printf("退票成功！\n");
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
    // 检查用户数量是否已达上限
    if (user_count >= MAX_USERS) {
        printf("用户数量已达上限(%d个)，无法添加新用户！\n", MAX_USERS);
        return;
    }
    
    // 确保新用户数据被正确初始化
    memset(&all_users[user_count], 0, sizeof(user));
    
    // 只复制必要的字段，避免垃圾数据污染
    strncpy(all_users[user_count].username, user_info->username, sizeof(all_users[user_count].username)-1);
    strncpy(all_users[user_count].password, user_info->password, sizeof(all_users[user_count].password)-1);
    strncpy(all_users[user_count].id_card, user_info->id_card, sizeof(all_users[user_count].id_card)-1);
    
    // 确保字符串以null结尾
    all_users[user_count].username[sizeof(all_users[user_count].username)-1] = '\0';
    all_users[user_count].password[sizeof(all_users[user_count].password)-1] = '\0';
    all_users[user_count].id_card[sizeof(all_users[user_count].id_card)-1] = '\0';
    
    // 确保车票数量为0
    all_users[user_count].ticket_count = 0;
    
    user_count++;

    // 使用统一的保存函数
    save_user_info();
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

// 保存所有用户信息到文件
void save_user_info() {
    FILE *fp = fopen("user_info.txt", "wb");
    if (fp == NULL) {
        printf("打开文件失败，无法保存用户信息！\n");
        return;
    }
    
    fwrite(all_users, sizeof(user), user_count, fp);
    fclose(fp);
    printf("用户信息已保存到文件！\n");
}