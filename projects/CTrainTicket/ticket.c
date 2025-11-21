#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ticket.h"
#include "types.h"
#include "global.h"
#include "menu.h"
#include "control.h"
#include "user.h"  // 添加user.h头文件包含

// 全局车票数据
extern train all_trains[50];
extern int train_count;
extern user all_users[10];
extern int user_count;

// 查询已订车票
void user_query_booked_tickets(user *current_user) {
    printf("==== 已订车票查询 ====\n");
    
    if (current_user->ticket_count == 0) {
        printf("您当前没有已订车票。\n");
        return;
    }
    
    printf("\n=== 您的已订车票列表 (共%d张) ===\n", current_user->ticket_count);
    for (int i = 0; i < current_user->ticket_count; i++) {
        ticket *t = &current_user->booked_tickets[i];
        printf("%d. 车次：%s | %s → %s | 出发：%s | 票价：%.2f元 | 座位：%s | 订票日期：%s\n",
               i+1, t->train_number, t->start_station, t->end_station,
               t->departure_time, t->price, t->seat_number, t->booking_date);
    }
}

// 查询车票信息
void user_query_train_tickets() {
    printf("==== 车票信息查询 ====\n");
    
    if (train_count == 0) {
        printf("当前没有可查询的车次信息。\n");
        return;
    }
    
    int choice;
    printf("请选择查询方式：\n");
    printf("1. 按车次查询\n");
    printf("2. 按始发站查询\n");
    printf("3. 按终点站查询\n");
    printf("4. 显示所有车次\n");
    printf("请输入选择：");
    scanf("%d", &choice);
    clear_input_buffer();
    
    char search_key[30];
    int found_count = 0;
    train found_trains[50];
    
    switch (choice) {
        case 1:
            printf("请输入车次：");
            scanf("%s", search_key);
            clear_input_buffer();
            
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].train_number, search_key) == 0 && all_trains[i].is_active) {
                    found_trains[found_count++] = all_trains[i];
                }
            }
            break;
            
        case 2:
            printf("请输入始发站：");
            scanf("%s", search_key);
            clear_input_buffer();
            
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].start_station, search_key) == 0 && all_trains[i].is_active) {
                    found_trains[found_count++] = all_trains[i];
                }
            }
            break;
            
        case 3:
            printf("请输入终点站：");
            scanf("%s", search_key);
            clear_input_buffer();
            
            for (int i = 0; i < train_count; i++) {
                if (strcmp(all_trains[i].end_station, search_key) == 0 && all_trains[i].is_active) {
                    found_trains[found_count++] = all_trains[i];
                }
            }
            break;
            
        case 4:
            for (int i = 0; i < train_count; i++) {
                if (all_trains[i].is_active) {
                    found_trains[found_count++] = all_trains[i];
                }
            }
            break;
            
        default:
            printf("无效的选择！\n");
            return;
    }
    
    if (found_count == 0) {
        printf("未找到符合条件的车次！\n");
        return;
    }
    
    printf("\n=== 查询结果 (共%d个车次) ===\n", found_count);
    for (int i = 0; i < found_count; i++) {
        printf("%d. 车次：%-8s | %s → %s | 出发：%s | 票价：%.2f元 | 余票：%d\n",
               i+1, found_trains[i].train_number, found_trains[i].start_station,
               found_trains[i].end_station, found_trains[i].departure_time,
               found_trains[i].price, found_trains[i].remaining_tickets);
    }
}

// 订票操作
int book_ticket(user *current_user, train *selected_train) {
    printf("==== 订票操作 ====\n");
    
    // 添加空指针检查
    if (current_user == NULL || selected_train == NULL) {
        printf("订票信息无效！\n");
        return 0;
    }
    
    // 检查车票是否可订
    if (!is_ticket_available(selected_train)) {
        printf("该车次余票不足，无法订票！\n");
        return 0;
    }
    
    // 检查是否已订该车票
    if (has_user_booked_ticket(current_user, selected_train->train_number)) {
        printf("您已经订过该车次的车票！\n");
        return 0;
    }
    printf("用户订票数量：%d",current_user->ticket_count+1);
    // 检查用户订票数量是否已达上限
    if (current_user->ticket_count >= MAX_TICKETS_PER_USER) {
        printf("您的订票数量已达上限(%d张)，无法继续订票！\n", MAX_TICKETS_PER_USER);
        return 0;
    }
    
    // 创建新车票 - 使用安全的字符串拷贝
    ticket new_ticket = {0}; // 初始化为0，避免未初始化内存
    
    // 使用strncpy确保不会越界
    strncpy(new_ticket.train_number, selected_train->train_number, sizeof(new_ticket.train_number)-1);
    strncpy(new_ticket.start_station, selected_train->start_station, sizeof(new_ticket.start_station)-1);
    strncpy(new_ticket.end_station, selected_train->end_station, sizeof(new_ticket.end_station)-1);
    strncpy(new_ticket.departure_time, selected_train->departure_time, sizeof(new_ticket.departure_time)-1);
    strncpy(new_ticket.arrival_time, selected_train->arrival_time, sizeof(new_ticket.arrival_time)-1);
    
    // 确保字符串以null结尾
    new_ticket.train_number[sizeof(new_ticket.train_number)-1] = '\0';
    new_ticket.start_station[sizeof(new_ticket.start_station)-1] = '\0';
    new_ticket.end_station[sizeof(new_ticket.end_station)-1] = '\0';
    new_ticket.departure_time[sizeof(new_ticket.departure_time)-1] = '\0';
    new_ticket.arrival_time[sizeof(new_ticket.arrival_time)-1] = '\0';
    
    new_ticket.price = selected_train->price;
    new_ticket.total_seats = selected_train->total_seats;
    new_ticket.remaining_tickets = selected_train->remaining_tickets - 1;
    new_ticket.is_booked = 1;
    
    // 生成座位号- 避免重复座位号
    int seat_number_base = current_user->ticket_count * 2 + 1; // 确保每次订票座位号不同
    snprintf(new_ticket.seat_number, sizeof(new_ticket.seat_number), "%d-%d", 
            (seat_number_base % 5) + 1,  // 车厢号 (1-5)
            (seat_number_base % 20) + 1); // 座位号 (1-20)
    
    // 生成订票日期
    strncpy(new_ticket.booking_date, "2024-01-01", sizeof(new_ticket.booking_date)-1);
    new_ticket.booking_date[sizeof(new_ticket.booking_date)-1] = '\0';
    
    // 添加到用户已订车票列表 - 添加边界检查
    if (current_user->ticket_count >= 0 && current_user->ticket_count < MAX_TICKETS_PER_USER) {
        current_user->booked_tickets[current_user->ticket_count] = new_ticket;
        current_user->ticket_count++;
        
        printf("订票成功！\n");
        printf("车次：%s | %s → %s | 座位：%s | 票价：%.2f元\n", 
               new_ticket.train_number, new_ticket.start_station, 
               new_ticket.end_station, new_ticket.seat_number, new_ticket.price);
        
        // 保存用户信息到文件
        save_user_info();
        
        return 1;
    } else {
        printf("订票失败：用户车票数量异常！\n");
        return 0;
    }
}

// 检查是否已订该车票
int has_user_booked_ticket(user *current_user, char *train_number) {
    // 添加空指针检查
    if (current_user == NULL || train_number == NULL) {
        return 0;
    }
    
    // 添加边界检查
    if (current_user->ticket_count < 0 || current_user->ticket_count > MAX_TICKETS_PER_USER) {
        return 0;
    }
    
    for (int i = 0; i < current_user->ticket_count; i++) {
        // 添加对booked_tickets数组元素的检查
        if (current_user->booked_tickets[i].train_number[0] != '\0' && 
            strcmp(current_user->booked_tickets[i].train_number, train_number) == 0 && 
            current_user->booked_tickets[i].is_booked) {
            return 1;
        }
    }
    return 0;
}

// 退票操作
int cancel_ticket(user *current_user, int ticket_index) {
    printf("==== 退票操作 ====\n");
    
    // 添加空指针检查
    if (current_user == NULL) {
        printf("用户信息无效！\n");
        return 0;
    }
    
    if (ticket_index < 0 || ticket_index >= current_user->ticket_count) {
        printf("无效的车票索引！\n");
        return 0;
    }
    
    ticket *cancel_ticket = &current_user->booked_tickets[ticket_index];
    
    // 检查是否已退票 - 修复逻辑：检查是否还未退票
    if (!cancel_ticket->is_booked) {
        printf("该车票已退票，无法重复退票！\n");
        return 0;
    }
    
    // 查找对应的车次信息
    train *corresponding_train = NULL;
    for (int i = 0; i < train_count; i++) {
        if (strcmp(all_trains[i].train_number, cancel_ticket->train_number) == 0) {
            corresponding_train = &all_trains[i];
            break;
        }
    }
    
    if (corresponding_train != NULL) {
        // 恢复余票数量
        corresponding_train->remaining_tickets++;
    }
    
    // 标记车票为已退票状态
    cancel_ticket->is_booked = 0;
    
    printf("退票成功！\n");
    printf("已退车票：%s | %s → %s | 座位：%s\n", 
           cancel_ticket->train_number, cancel_ticket->start_station, cancel_ticket->end_station,
           cancel_ticket->seat_number);
    
    // 保存用户信息到文件
    save_user_info();
    
    return 1;
}

// 检查车票是否可订
int is_ticket_available(train *train_info) {
    return train_info->remaining_tickets > 0 && train_info->is_active;
}

// 显示单张车票信息
void display_ticket_info(ticket *ticket_info) {
    printf("车次：%s\n", ticket_info->train_number);
    printf("行程：%s → %s\n", ticket_info->start_station, ticket_info->end_station);
    printf("时间：%s - %s\n", ticket_info->departure_time, ticket_info->arrival_time);
    printf("票价：%.2f元\n", ticket_info->price);
    printf("座位：%s\n", ticket_info->seat_number);
    printf("订票日期：%s\n", ticket_info->booking_date);
    printf("状态：%s\n", ticket_info->is_booked ? "已订票" : "未订票");
}

// 显示车次列表
void display_train_tickets(train *trains, int count) {
    printf("\n=== 车次列表 (共%d个车次) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. 车次：%-8s | %s → %s | 出发：%s | 票价：%.2f元 | 余票：%d | 状态：%s\n",
               i+1, trains[i].train_number, trains[i].start_station, trains[i].end_station,
               trains[i].departure_time, trains[i].price, trains[i].remaining_tickets,
               trains[i].is_active ? "启用" : "停用");
    }
}