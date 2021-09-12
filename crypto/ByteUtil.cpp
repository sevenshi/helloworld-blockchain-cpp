//
// Created by 40906 on 2021/9/12.
//

#include "ByteUtil.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;


string ByteUtil::uchar2hex(unsigned char inchar)
{
    ostringstream oss (ostringstream::out);
    oss << setw(2) << setfill('0') << hex << (int)(inchar);
    return oss.str();
}
string ByteUtil::uchars2hex(unsigned char* uchars,int length)
{
    string hexString = "";
    for (int i = 0; i < length; i++) {
        hexString += uchar2hex(uchars[i]);
    }
    return hexString;
}
vector<unsigned char> ByteUtil::HexToBytes(const string& hex) {
    vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}