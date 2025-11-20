//用户相关头文件
#include "types.h"
#ifndef USER_H
#define USER_H
// 用户功能选择
void user_menu_choice();

int load_user_info(user *users);
void save_new_user(user *user_info);
user* find_user_by_username(char *username);
int is_username_exists(char *username);
#endif