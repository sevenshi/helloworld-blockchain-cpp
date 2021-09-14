//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_TIMEUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_TIMEUTIL_H

#include <string>
using namespace std;

namespace TimeUtil {
    unsigned long long millisecondTimestamp();
    string formatMillisecondTimestamp(unsigned long long millisecondTimestamp);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_TIMEUTIL_H
