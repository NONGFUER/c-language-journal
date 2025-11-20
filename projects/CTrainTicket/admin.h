//管理员相关头文件
#ifndef ADMIN_H
#define ADMIN_H

#include "types.h"

// 管理员主功能选择
void admin_menu_choice();

// 管理旅客用户信息功能
void admin_manage_users();
void admin_user_query();
void admin_user_list();
void admin_user_add();
void admin_user_delete();
void admin_user_modify();

// 管理车次信息功能
void admin_manage_trains();
void admin_train_query();
void admin_train_list();
void admin_train_add();
void admin_train_delete();
void admin_train_modify();

// 车次信息文件操作
void load_train_info();
void save_train_info();

#endif