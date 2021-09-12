//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
#include <string>

using namespace std;

namespace LogUtil {
    void error(string message, exception exception);
    void debug(string message);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
