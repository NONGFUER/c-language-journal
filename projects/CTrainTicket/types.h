#ifndef TYPES_H
#define TYPES_H

#define MAX_USERS 10
#define MAX_TRAINS 50
#define MAX_TICKETS_PER_USER 10
#define MAX_TICKETS 100

// 车票结构体
typedef struct TICKET {
    char train_number[10];       // 车次
    char start_station[30];      // 起点站
    char end_station[30];        // 终点站
    char departure_time[10];     // 出发时间 (格式: HH:MM)
    char arrival_time[10];       // 到达时间 (格式: HH:MM)
    float price;                 // 票价
    int remaining_tickets;       // 余票数量
    int total_seats;             // 总座位数
    char seat_number[10];        // 座位号 (格式: 车厢-座位)
    char booking_date[20];       // 订票日期 (格式: YYYY-MM-DD)
    int is_booked;               // 是否已订票 (0: 未订, 1: 已订)
} ticket;

// 用户结构体
typedef struct USER {
    char username[50];           // 用户名
    char password[50];           // 密码
    char id_card[20];            // 身份证号码
    ticket booked_tickets[MAX_TICKETS_PER_USER]; // 已订车票信息
    int ticket_count;            // 已订票数量
} user;

// 管理员结构体
typedef struct ADMIN {
    char username[50];           // 用户名
    char password[50];           // 密码
} admin;

// 车次信息结构体
typedef struct TRAIN {
    char train_number[10];       // 车次
    char start_station[30];      // 始发站
    char end_station[30];        // 终点站
    char departure_time[10];     // 出发时间
    char arrival_time[10];       // 到达时间
    float price;                 // 票价
    int total_seats;             // 总座位数
    int remaining_tickets;       // 余票
    // char train_type[10];      // 车型 (如: 高铁, 动车, 普通) - 已删除
    int is_active;               // 是否启用 (1:启用, 0:停用)
} train;

#endif