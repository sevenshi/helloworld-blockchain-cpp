//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
#include <string>

using namespace std;

typedef enum LogLevel {
    LOG_DEBUG,
    LOG_ERROR,
}LogLevel;

namespace LogUtil {
    void log(string file, string function, long line, unsigned int level, string message);

#define debug(message) log(__FILE__, __FUNCTION__, __LINE__, LOG_DEBUG, message)
#define error(message) log(__FILE__, __FUNCTION__, __LINE__, LOG_ERROR, message)

}

#endif //HELLOWORLD_BLOCKCHAIN_CPP_LOGUTIL_H
