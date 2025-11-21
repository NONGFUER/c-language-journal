# 火车订票系统 (CTrainTicket)

## 项目简介

CTrainTicket 是一个基于C语言开发的命令行火车订票系统，具有用户注册登录、车票查询、订票、退票以及管理员管理等功能。该系统采用模块化设计，具有良好的可扩展性和可维护性。

## 功能特性

### 旅客功能
1. **用户注册与登录**
   - 新用户注册（用户名、身份证号、密码验证）
   - 旅客登录（3次错误机会限制）
   
2. **个人信息维护**
   - 修改登录密码
   - 查看个人详细信息

3. **车票查询**
   - 查询已订车票信息
   - 按车次查询车票信息
   - 按始发站查询车票信息
   - 按终点站查询车票信息

4. **订票操作**
   - 浏览可订车次列表
   - 选择车次进行订票
   - 自动生成座位号

5. **退票操作**
   - 查看已订车票列表
   - 选择车票进行退票

### 管理员功能
1. **旅客用户管理**
   - 查询旅客用户信息
   - 显示旅客用户列表
   - 增加新用户
   - 删除用户
   - 修改用户信息（密码、身份证号）

2. **车次信息管理**
   - 查询车次信息
   - 显示车次列表
   - 增加新车次
   - 删除车次
   - 修改车次信息
   - 启用/停用车次

## 项目结构

CTrainTicket/ 
├── main.c # 主程序入口 
├── menu.c # 菜单相关功能实现 
├── auth.c # 认证相关功能（登录、注册） 
├── user.c # 旅客功能模块实现 
├── admin.c # 管理员功能模块实现 
├── ticket.c # 车票相关功能实现 
├── control.c # 控制函数和工具函数实现 
├── menu.h # 菜单相关函数声明 
├── auth.h # 认证相关函数声明 
├── user.h # 旅客相关函数声明 
├── admin.h # 管理员相关函数声明 
├── ticket.h # 车票相关函数声明 
├── types.h # 数据结构定义 
├── global.h # 全局变量声明 
├── Makefile # 构建配置文件 
├── train_info.txt # 车次信息数据文件 
├── user_info.txt # 用户信息数据文件 
└── train_ticket.exe# 可执行文件

## 数据结构

### 用户信息 (user)
- 用户名 (username)
- 密码 (password)
- 身份证号 (id_card)
- 已订车票数组 (booked_tickets)
- 已订票数量 (ticket_count)

### 车次信息 (train)
- 车次 (train_number)
- 始发站 (start_station)
- 终点站 (end_station)
- 出发时间 (departure_time)
- 到达时间 (arrival_time)
- 票价 (price)
- 总座位数 (total_seats)
- 余票数量 (remaining_tickets)
- 启用状态 (is_active)

### 车票信息 (ticket)
- 车次 (train_number)
- 起点站 (start_station)
- 终点站 (end_station)
- 出发时间 (departure_time)
- 到达时间 (arrival_time)
- 票价 (price)
- 座位号 (seat_number)
- 订票日期 (booking_date)
- 订票状态 (is_booked)

## 编译与运行

### 编译项目
```bash
make
```

### 运行程序
```bash
./train_ticket.exe
```

### 清理编译文件
```bash
make clean
```

## 使用说明

### 主菜单
程序启动后显示主菜单，用户可选择以下操作：
1. 旅客登录
2. 管理员登录（默认账号：admin，密码：123456）
3. 新用户注册
4. 退出程序

### 旅客操作流程
1. 注册/登录后进入旅客功能菜单
2. 可进行个人信息维护、车票查询、订票、退票等操作
3. 每项操作完成后自动返回旅客功能菜单

### 管理员操作流程
1. 使用管理员账号登录后进入管理员功能菜单
2. 可管理旅客用户信息和车次信息
3. 每项操作完成后自动返回相应上级菜单

## 验证规则

### 用户名验证
- 长度必须在3-20个字符之间

### 身份证验证
- 必须为18位数字

### 密码验证
- 长度必须在6-20个字符之间

## 数据存储

系统使用二进制文件存储数据：
- `user_info.txt`：存储用户信息
- `train_info.txt`：存储车次信息

## 开发环境

- 编程语言：C语言
- 开发平台：Windows/Linux
- 编译器：GCC
- 构建工具：Make

## 注意事项

1. 系统限制最多10个用户
2. 系统限制最多50个车次
3. 每个用户最多可订10张车票
4. 连续3次输入错误密码将自动退出系统
5. 车次信息在程序启动时自动加载


## 项目菜单结构

### 主菜单 (menu_choice)
├── 1. 旅客登录 → 用户菜单 (user_menu_choice)
│   ├── 1. 用户基本信息维护 (user_info_maintenance)
│   │   ├── 1. 修改密码 (user_change_password)
│   │   └── 2. 查看详细信息 (view_user_details)
│   │   └── 0. 返回上级菜单 (user_menu_choice)
│   ├── 2. 查询操作(user_query_operation)
│   │   ├── 1. 查询已订的车票信息 (user_query_booked_tickets)
│   │   └── 2. 查询火车的车票信息 (user_train_ticket_submenu)
│   │       ├── a. 按车次查询车票信息 (user_query_train_tickets_by_number)
│   │       ├── b. 按始发站查询车票信息 (user_query_train_tickets_by_start)
│   │       └── c. 按终点站查询车票信息 (user_query_train_tickets_by_end)
│   │   └── 0. 返回上级菜单 (user_query_operation)
│   ├── 3. 退票操作 (user_cancel_ticket_operation)
│   ├── 4. 订票操作 (user_book_ticket_operation)
│   └── 5. 返回主菜单(menu_choice)
├── 2. 管理员登录 → 管理员菜单 (admin_menu_choice)
│   ├── 1. 管理旅客用户信息(admin_manage_users)
│   │   ├── 1. 旅客用户查询(admin_user_query)
│   │   ├── 2. 旅客用户信息列表显示(admin_user_list)
│   │   ├── 3. 旅客用户增加(admin_user_add)
│   │   ├── 4. 旅客用户删除(admin_user_delete)
│   │   ├── 5. 旅客用户修改 (admin_user_modify)
│   │   └── 0. 返回上级菜单 (admin_menu_choice)
│   ├── 2. 管理车次信息(admin_manage_trains)
│   │   ├── 1. 车次查询(admin_train_query)
│   │   ├── 2. 车次列表信息显示(admin_train_list)
│   │   ├── 3. 车次增加(admin_train_add)
│   │   ├── 4. 车次删除(admin_train_delete)
│   │   ├── 5. 车次修改 (admin_train_modify)
│   │   └── 0. 返回上级菜单 (admin_menu_choice)
│   └── 3. 返回主菜单 (menu_choice)
├── 3. 新用户注册 → 注册菜单 (register_user)
└── 4. 退出程序 (exit_program)
