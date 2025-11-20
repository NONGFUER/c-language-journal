//菜单相关函数实现
#include <stdio.h>
#include <stdlib.h>
//头部菜单样式
void menu_head_style()
{ 
    printf("============================================\n");
    printf("|          火车订票系统                     |\n");
    printf("============================================\n");
    printf("|                                          |\n");
    printf("|  **************************************  |\n");
    printf("|                                          |\n");
}
//尾部菜单样式
void menu_end_style()
{ 
    printf("|                                          |\n");
    printf("|  **************************************  |\n");
    printf("|                                          |\n");
    printf("============================================\n");
}

//程序主界面入口菜单
void menu()
{   
    printf("\n");
    menu_head_style();
    printf("|  请选择用户操作：                         |\n");
    printf("|                                          |\n");
    printf("|  * 1. 旅客登录                           |\n");
    printf("|  * 2. 管理员登录                         |\n");
    printf("|  * 3. 新用户注册                         |\n");
    printf("|  * 4. 退出程序                           |\n");
    menu_end_style();
    printf("\n");
}

//旅客功能菜单
void menu_user()
{   
    menu_head_style();
    printf("|          旅客功能菜单                     |\n");
    printf("|                                          |\n");
    printf("|  * 1. 用户基本信息维护                    |\n");
    printf("|  * 2. 查询操作                           |\n");
    printf("|  * 3. 退票操作                           |\n");
    printf("|  * 4. 订票操作                           |\n");
    printf("|  * 5. 返回主菜单                         |\n");
    menu_end_style();
    printf("\n");
}

//管理员功能菜单
void menu_admin()
{
    menu_head_style();
    printf("|          管理员功能菜单                   |\n");
    printf("|                                          |\n");
    printf("|  * 1. 管理旅客用户信息                   |\n");
    printf("|  * 2. 管理车次信息                       |\n");
    printf("|  * 3. 返回主菜单                         |\n");	
    menu_end_style();
    printf("\n");
}

//管理旅客用户信息-子菜单
void menu_admin_user()
{
    menu_head_style();
    printf("|       管理旅客用户信息                   |\n");
    printf("|                                          |\n");
    printf("|  * 1. 旅客用户查询                       |\n");
    printf("|  * 2. 旅客用户信息列表显示               |\n");
    printf("|  * 3. 旅客用户增加                       |\n");
    printf("|  * 4. 旅客用户删除                       |\n");
    printf("|  * 5. 旅客用户修改                       |\n");
    printf("|  * 0. 返回上级菜单                       |\n");
    menu_end_style();
    printf("\n");
}

//管理车次信息-子菜单
void menu_train(){
    menu_head_style();
    printf("|          管理车次信息                     |\n");
    printf("|                                          |\n");
    printf("|  * 1. 车次查询                           |\n");
    printf("|  * 2. 车次列表信息显示                   |\n");
    printf("|  * 3. 车次增加                           |\n");
    printf("|  * 4. 车次删除                           |\n");
    printf("|  * 5. 车次修改                           |\n");
    printf("|  * 0. 返回上级菜单                       |\n");
    menu_end_style();
    printf("\n");
}