//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_FILEUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_FILEUTIL_H

#include <string>

using namespace std;

namespace FileUtil {
    string newPath(string parent, string child);
    void makeDirectory(string path);
    void deleteDirectory(string path);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_FILEUTIL_H
