#include <iostream>
#include <queue>
#include <list>
#define BUFFER_SIZE 1024
enum valtype{
    _string =1,
    _int,
    _longlong,
    _array,
    _char
    

};

enum returntype{
    _quit =1,
    
    

};

struct cpureg
{
    long long rax;
    long long rbx;
    long long rcx;
    long long rdx;
    long long rsi;
    long long rdi;
    long long rbp;
    long long rsp;
    long long r8;
    long long r9;
    long long r10;
    long long r11;
    long long r12;
    long long r13;
    long long r14;
    long long r15;

    long long rip;
    long long eflags;
    long long cs;
    long long ss;
    long long ds;    
    long long es;
    long long fs;
    long long gs;

};
struct  kval
{
    std::string key;
    std::string val;

};

using kval=struct kval;

using cpureg =struct cpureg;

class gdbprocess{
    public:
        gdbprocess();
        ~gdbprocess();
        
        std::string fromgdb();
        std::string getreginfo();
        std::string getlocalinfo();
        int togdb(std::string cmd);
        int _togdb(std::string cmd);


        
        int parsegdbinfo(std::string cmd);

        void addwacth(std::string);

    private:
        int initpipe();
        int creatgdbprocess();
        void startgdbinfo();
    private:
        int to_gdb[2];    // 管道用于父进程向子进程写入命令
        int from_gdb[2];  // 管道用于子进程向父进程传递输出
        std::queue<std::string> gdballinfo;
        std::string newinfo;
        std::string reginfo;
        std::string localvalinfo;
        std::string breakpinfo;
        std::list<std::string> wacthvalname;
        std::list<std::string> wacthval;

        cpureg reg;
        int first;

};

