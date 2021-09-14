//
// Created by 40906 on 2021/9/12.
//
#include <iostream>
#include "SystemUtil.h"

#ifdef _WIN32
#else
#include <unistd.h>
#endif

void SystemUtil::errorExit(string message, exception exception){

}
string SystemUtil::systemRootDirectory(){
    string path;
    #ifdef _WIN32
        //TODO
        throw exception();
    #else
        path = getcwd(NULL,0);
    #endif
    return path;
}
