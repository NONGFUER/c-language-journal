//用户相关头文件
#ifndef USER_H
#define USER_H

#include "types.h"

// 用户相关函数声明
void user_menu_choice(user *current_user);  // 修改函数签名，添加参数

// 用户查询操作函数
void user_query_operation(user *current_user);
void user_train_ticket_submenu(user *current_user);
void user_query_train_tickets_by_number();
void user_query_train_tickets_by_start();
void user_query_train_tickets_by_end();

// 用户订票退票操作
void user_book_ticket_operation(user *current_user);
void user_cancel_ticket_operation(user *current_user);

// 用户基本信息维护函数
void user_info_maintenance(user *current_user);
void user_change_password(user *current_user);
void user_view_details(user *current_user);

// 原有用户管理函数
int load_user_info(user *users);
void save_new_user(user *user_info);
user* find_user_by_username(char *username);
int is_username_exists(char *username);

#endif