# 编译器设置
CC = gcc
CFLAGS = -Wall -g -std=c99
SOURCES = main.c menu.c auth.c control.c 
OBJECTS = $(SOURCES:.c=.o)

# 检测操作系统
ifeq ($(OS),Windows_NT)
    RM = rm -f
    EXE_EXT =
    RUN_CMD = ./
else
	RM = del /Q
    EXE_EXT = .exe
    RUN_CMD = .\\
   
endif

TARGET = train_ticket$(EXE_EXT)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# 编译每个.c文件为.o文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	$(RM) *.o $(TARGET)

# 运行程序
run: $(TARGET)
	$(RUN_CMD)$(TARGET)

# 伪目标
.PHONY: all clean run