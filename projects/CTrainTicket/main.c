#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "auth.h"
#include "user.h"
#include "control.h"
#include "types.h"

// 定义全局变量all_users和adm
user all_users[10];
int user_count = 0;

admin adm = { "admin", "123456" };



int main()
{
    user_count = load_user_info(all_users);//加载用户信息
    //clear_file("user_info.txt");//手动清空
    menu_choice();//主菜单选择功能
    return 0;
}