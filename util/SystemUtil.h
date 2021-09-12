//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_SYSTEMUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_SYSTEMUTIL_H

#include <string>

using namespace std;

namespace SystemUtil {
    void errorExit(string message, exception exception);
    string systemRootDirectory();
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_SYSTEMUTIL_H
