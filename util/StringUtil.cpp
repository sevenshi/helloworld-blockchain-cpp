//
// Created by 40906 on 2021/9/12.
//

#include <iostream>
#include "StringUtil.h"

bool StringUtil::isEquals(string str1,string str2){
    return str1.compare(str2) == 0;
}

bool StringUtil::isNullOrEmpty(string str){
    return  str.empty() ;
}

string StringUtil::prefixPadding(string rawValue,int targetLength,string paddingValue){
    string target = rawValue;
    while (target.length() < targetLength){
        target = paddingValue + target;
    }
    return target;
}

string StringUtil::concatenate(string str1,string str2){
    return str1 + str2;
}

string StringUtil::concatenate3(string str1, string str2, string str3){
    return str1 + str2 + str3;
}

string StringUtil::valueOfUint64(unsigned long long number){
    return to_string(number);
}

