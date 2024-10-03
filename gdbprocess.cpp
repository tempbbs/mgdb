#include "gdbprocess.hpp"

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

gdbprocess::gdbprocess() {
  initpipe();
  creatgdbprocess();
  first = 0;
}

gdbprocess::~gdbprocess() {
  // 关闭管道
  close(to_gdb[1]);
  close(from_gdb[0]);

  // 等待子进程结束
  wait(NULL);
}

std::string gdbprocess::fromgdb() { return newinfo; }

int gdbprocess::togdb(std::string cmd) {
  _togdb(cmd);

  parsegdbinfo(cmd);
}

int gdbprocess::_togdb(std::string cmd) {
  // 父进程：与GDB交互

  // 关闭子进程的读管道和写管道
  close(to_gdb[0]);
  close(from_gdb[1]);

  char command[BUFFER_SIZE];
  memset(command, 0, BUFFER_SIZE);

  char output[BUFFER_SIZE];
  memset(output, 0, BUFFER_SIZE);

  std::string buffer;
  if (first) {
    first = 0;

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
  }

  // 循环读取用户输入的命令并发送给gdb

  // 如果用户输入的是"quit"，则退出程序
  if (strncmp(command, "quit", 4) == 0) {
    return _quit;
  }

  // 将用户命令写入GDB管道，并添加换行符
  //   strcat(command, "\n");
  cmd += "\n";
  strncpy(command, cmd.c_str(), cmd.size());
  int strl = strlen(command);

  write(to_gdb[1], command, strlen(command));
  usleep(2000);

  // 从GDB读取输出并显示，直到提示符出现
  buffer.clear();
  while (true) {
    ssize_t bytesRead = read(from_gdb[0], output, sizeof(output) - 1);
    if (bytesRead <= 0) {
      break;
    }
    output[bytesRead] = '\0';  // 添加字符串结束符
    buffer.append(output);
    int bufsize=buffer.size();
    // 检查是否到了(gdb)提示符，若是则退出读取
    if (buffer.find("(gdb)") != std::string::npos) {
      gdballinfo.push(buffer);
      break;
    }
  }
}

// std::string gdbprocess::getnewinfo() {
//     std::string tmp=gdballinfo.front();
//     // gdballinfo.pop();
//      return gdballinfo.front();
// }

int gdbprocess::parsegdbinfo(std::string cmd) {
  newinfo = gdballinfo.front();
  gdballinfo.pop();

  if (cmd == "n" || cmd == "s" || cmd == "c") {
    _togdb("info registers");
    _togdb("info local");
    if (wacthvalname.size() != 0) {
      for (auto i : wacthvalname) {
        std::string name = "p " + i;
        _togdb(name);
      }
    }

    reginfo = gdballinfo.front();
    gdballinfo.pop();

    localvalinfo = gdballinfo.front();
    gdballinfo.pop();
    for (int i = 0; i < wacthvalname.size(); i++) {
      wacthval.push_back(gdballinfo.front());
      gdballinfo.pop();
    }
  }

  return 0;
}

void gdbprocess::addwacth(std::string cmd) { wacthval.push_back(cmd); }

int gdbprocess::initpipe() {
  // 创建两个管道
  if (pipe(to_gdb) == -1 || pipe(from_gdb) == -1) {
    perror("pipe failed");
    return 1;
  }
}

int gdbprocess::creatgdbprocess() {
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
  }
}

std::string gdbprocess::getreginfo() {
    return reginfo;
}

std::string gdbprocess::getlocalinfo() {
    return localvalinfo;
}
