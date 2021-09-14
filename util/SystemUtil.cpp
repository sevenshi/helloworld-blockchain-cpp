//
// Created by 40906 on 2021/9/12.
//
#include <iostream>
#include "SystemUtil.h"

#if defined _WIN32 || defined _WIN64
#else
#include <unistd.h>
#endif

void SystemUtil::errorExit(string message, exception exception){

}
string SystemUtil::systemRootDirectory(){
    string path;
    #if defined _WIN32 || defined _WIN64
        //TODO
        throw exception();
    #else
        path = getcwd(NULL,0);
    #endif
    return path;
}
