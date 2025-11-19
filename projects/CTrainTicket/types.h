#ifndef TYPES_H
#define TYPES_H

// 用户结构体
typedef struct USER {
    char username[50];//用户名
    char password[50];//密码
    char id_card[20];//身份证号码
    //车票信息
}user;

user user_info[10];
#endif