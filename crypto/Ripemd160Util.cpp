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

string Ripemd160Util::digest(string input)
{
    std::vector<unsigned char> bytes = ByteUtil::HexToBytes(input);
    unsigned char result[20];
    RIPEMD160(&bytes[0], bytes.size(), result);
    string sha256 = ByteUtil::uchars2hex(result,sizeof result);
    return sha256;
}