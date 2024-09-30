#include <bits/stdc++.h>
#include "gdbprocess.hpp"
#include "tui.hpp"
int gg=10;
int main(){

    gdbprocess gp;
    std::cout << "(gdb-tui) ";

    while(1){
        std::string cmd;
        std::getline(std::cin,cmd);

        if(gp.togdb(cmd)==_quit){
            return 0;
        }
        std::cout<<gp.fromgdb()<<std::flush;

        /**
         *showgdbinfo 

         * 
         * 
         * 
         *  
         * * */
    }




    return 0;
}