//
// Created by 40906 on 2021/9/12.
//
#include <iostream>
#include <unistd.h>
#include "SystemUtil.h"

void SystemUtil::errorExit(string message, exception exception){

}
string SystemUtil::systemRootDirectory(){
    string path;
    path = getcwd(NULL,0);
    return path;
}
