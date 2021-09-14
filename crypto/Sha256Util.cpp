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



vector<unsigned char> Sha256Util::digest(vector<unsigned char> input)
{
    vector<unsigned char> result(32);
    SHA256(&input[0], input.size(), &result[0]);
    return result;
}
vector<unsigned char> Sha256Util::doubleDigest(vector<unsigned char> input)
{
    return digest(digest(input));
}