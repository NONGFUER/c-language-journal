#ifndef ADMIN_H
#define ADMIN_H

#include "types.h"

// 管理员功能选择
void admin_menu_choice();

// 管理旅客用户信息功能
void admin_manage_users();
void admin_user_query();        // 旅客用户查询
void admin_user_list();         // 旅客用户信息列表显示
void admin_user_add();          // 旅客用户增加
void admin_user_delete();       // 旅客用户删除
void admin_user_modify();       // 旅客用户修改

// 管理车次信息功能
void admin_manage_trains();
void admin_train_query();       // 车次查询
void admin_train_list();        // 车次列表信息显示
void admin_train_add();         // 车次增加
void admin_train_delete();      // 车次删除
void admin_train_modify();      // 车次修改

#endif