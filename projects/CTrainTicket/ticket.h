#ifndef TICKET_H
#define TICKET_H

#include "types.h"

// 车票操作函数声明

// 旅客车票查询功能
void user_query_booked_tickets(user *current_user);  // 查询已订车票
void user_query_train_tickets();                     // 查询车票信息

// 车票操作功能
int book_ticket(user *current_user, train *selected_train);  // 订票
int cancel_ticket(user *current_user, int ticket_index);     // 退票

// 车票信息显示功能
void display_ticket_info(ticket *ticket_info);               // 显示单张车票信息
void display_train_tickets(train *trains, int count);        // 显示车次列表

// 车票验证功能
int is_ticket_available(train *train_info);                 // 检查车票是否可订
int has_user_booked_ticket(user *current_user, char *train_number); // 检查是否已订该车票

// 车票文件操作
int load_ticket_data();                                     // 加载车票数据
void save_ticket_data();                                    // 保存车票数据

#endif