//
// Created by 40906 on 2021/9/12.
//

#include <iomanip>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include "TimeUtil.h"


long TimeUtil::millisecondTimestamp(){
    long ms = duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    return ms ;
}

string TimeUtil::formatMillisecondTimestamp(long millisecondTimestamp){
    time_t t = time_t (millisecondTimestamp/1000);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&t) );
    return tmp;
}


