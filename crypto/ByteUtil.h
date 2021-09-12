//
// Created by 40906 on 2021/9/12.
//

#ifndef UNTITLED_BYTEUTIL_H
#define UNTITLED_BYTEUTIL_H

#include <string>
#include <vector>
using namespace std;

namespace ByteUtil {
    string uchar2hex(unsigned char inchar);
    string uchars2hex(unsigned char* uchars,int length);
    vector<unsigned char> HexToBytes(const string& hex);
};


#endif //UNTITLED_BYTEUTIL_H