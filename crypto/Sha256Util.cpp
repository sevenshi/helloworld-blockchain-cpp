//
// Created by 40906 on 2021/9/11.
//
#include <iostream>
#include <string>
#include <openssl/sha.h>
#include "Sha256Util.h"
#include "ByteUtil.h"
#include <vector>

typedef unsigned char byte;

using namespace std;



string Sha256Util::digest(string input)
{
    std::vector<unsigned char> bytes = ByteUtil::HexToBytes(input);
    unsigned char result[32];
    SHA256(&bytes[0], bytes.size(), result);
    string sha256 = ByteUtil::uchars2hex(result,sizeof result);
    return sha256;
}