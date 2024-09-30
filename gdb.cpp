#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    int to_gdb[2];    // 管道用于父进程向子进程写入命令
    int from_gdb[2];  // 管道用于子进程向父进程传递输出

    // 创建两个管道
    if (pipe(to_gdb) == -1 || pipe(from_gdb) == -1) {
        perror("pipe failed");
        return 1;
    }

    // 创建子进程
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // 子进程：执行GDB

        // 关闭父进程的写管道和子进程的读管道
        close(to_gdb[1]);
        close(from_gdb[0]);

        // 将标准输入重定向到管道的读端
        dup2(to_gdb[0], STDIN_FILENO);
        close(to_gdb[0]);

        // 将标准输出和标准错误重定向到管道的写端
        dup2(from_gdb[1], STDOUT_FILENO);
        dup2(from_gdb[1], STDERR_FILENO);
        close(from_gdb[1]);

        // 执行gdb，使用"-q"选项（安静模式）
        char *args[] = {(char *)"gdb", (char *)"-q", NULL};
        execvp("gdb", args);

        // 如果execvp失败，打印错误
        perror("execvp failed");
        return 1;
    } else {
        // 父进程：与GDB交互

        // 关闭子进程的读管道和写管道
        close(to_gdb[0]);
        close(from_gdb[1]);

        char command[BUFFER_SIZE];
        char output[BUFFER_SIZE];
        std::string buffer;

        // 读取并丢弃GDB的初始输出（版权信息等）
        while (true) {
            ssize_t bytesRead = read(from_gdb[0], output, sizeof(output) - 1);
            if (bytesRead <= 0) {
                break;
            }
            output[bytesRead] = '\0';  // 添加字符串结束符
            buffer.append(output);
            if (buffer.find("(gdb)") != std::string::npos) {
                break;
            }
        }

        std::cout << "Welcome to the GDB TUI!\n";

        // 循环读取用户输入的命令并发送给gdb
        while (true) {
            std::cout << "(gdb-tui) ";
            std::cin.getline(command, BUFFER_SIZE);

            // 如果用户输入的是"quit"，则退出程序
            if (strncmp(command, "quit", 4) == 0) {
                break;
            }

            // 将用户命令写入GDB管道，并添加换行符
            strcat(command, "\n");
            write(to_gdb[1], command, strlen(command));

            // 从GDB读取输出并显示，直到提示符出现
            buffer.clear();
            while (true) {
                ssize_t bytesRead = read(from_gdb[0], output, sizeof(output) - 1);
                if (bytesRead <= 0) {
                    break;
                }
                output[bytesRead] = '\0';  // 添加字符串结束符
                buffer.append(output);
                std::cout << output;

                // 检查是否到了(gdb)提示符，若是则退出读取
                if (buffer.find("(gdb)") != std::string::npos) {
                    break;
                }
            }
        }

        // 关闭管道
        close(to_gdb[1]);
        close(from_gdb[0]);

        // 等待子进程结束
        wait(NULL);
    }

    return 0;
}