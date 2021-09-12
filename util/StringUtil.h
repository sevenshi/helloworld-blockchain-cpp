//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_STRINGUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_STRINGUTIL_H

#include <string>

using namespace std;


namespace StringUtil {
    const string BLANKSPACE = " ";
    //TODO why can not delete std:: flag ?
    bool isEquals(string string,std::string anotherString);
    bool isNullOrEmpty(string string);
    string prefixPadding(string rawValue,int targetLength,string paddingValue);
    string concatenate(string value1,string value2);
    string concatenate3(string value1, string value2, string value3);
    string concatenate3(string value1, string value2, string value3);
    //TODO unsigned long long?64位无符号整数?
    string valueOfUint64(unsigned long long number);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_STRINGUTIL_H
