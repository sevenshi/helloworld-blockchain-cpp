//
// Created by 40906 on 2021/9/12.
//

#include "Ripemd160Util.h"
#include <iostream>
#include <string>
#include <openssl/ripemd.h>
#include "Sha256Util.h"
#include "ByteUtil.h"
#include <vector>
using namespace std;

vector<unsigned char> Ripemd160Util::digest(vector<unsigned char> input)
{
    vector<unsigned char> result(20);
    RIPEMD160(&input[0], input.size(), &result[0]);
    return result;
}