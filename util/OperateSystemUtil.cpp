//
// Created by 40906 on 2021/9/12.
//

#include "OperateSystemUtil.h"

#ifdef _WIN32
# define PLATFORM_ID "Windows"
#elif __APPLE__
# define PLATFORM_ID "Mac"
#elif __linux
# define PLATFORM_ID "Linux"
#else
# define PLATFORM_ID "Unknow"
#endif


bool OperateSystemUtil::isWindowsOperateSystem(){
     return PLATFORM_ID ==  "Windows";
}

bool OperateSystemUtil::isMacOperateSystem(){
    return PLATFORM_ID ==  "Mac";
}

bool OperateSystemUtil::isLinuxOperateSystem(){
    return PLATFORM_ID == "Linux";
}

