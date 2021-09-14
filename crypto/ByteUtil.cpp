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
vector<unsigned char> ByteUtil::hexStringToBytes(const string& hex) {
    vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}
string ByteUtil::bytesToHexString(vector<unsigned char> bytes) {
    return ByteUtil::uchars2hex(&bytes[0],bytes.size());
}

//TODO TEST
vector<unsigned char> ByteUtil::uint64ToBytes(uint64_t number){
    vector<unsigned char> bytes;
    bytes.push_back((unsigned char)(number >> 8*7));
    bytes.push_back((unsigned char)(number >> 8*6));
    bytes.push_back((unsigned char)(number >> 8*5));
    bytes.push_back((unsigned char)(number >> 8*4));
    bytes.push_back((unsigned char)(number >> 8*3));
    bytes.push_back((unsigned char)(number >> 8*2));
    bytes.push_back((unsigned char)(number >> 8*1));
    bytes.push_back((unsigned char)(number >> 8*0));
    return bytes;
}
//TODO TEST
uint64_t ByteUtil::bytesToUint64(vector<unsigned char> bytes){
    return
            (uint64_t(bytes[7]) << 8*7) |
            (uint64_t(bytes[6]) << 8*6) |
            (uint64_t(bytes[5]) << 8*5) |
            (uint64_t(bytes[4]) << 8*4) |
            (uint64_t(bytes[3]) << 8*3) |
            (uint64_t(bytes[2]) << 8*2) |
            (uint64_t(bytes[1]) << 8*1) |
            (uint64_t(bytes[0]) << 8*0);
}

vector<unsigned char> ByteUtil::copy(vector<unsigned char> sourceBytes, int startPosition, int length){
    vector<unsigned char> bytes;
    for(int i=startPosition;i<startPosition+length;i++){
        bytes.push_back(sourceBytes[startPosition+length]);
    }
    return bytes;
}
void ByteUtil::copyTo(vector<unsigned char> sourceBytes, int sourceStartPosition, int length, vector<unsigned char> destinationBytes, int destinationStartPosition){
    //TODO
}
vector<unsigned char> ByteUtil::concatenate(vector<unsigned char> bytes1,vector<unsigned char> bytes2){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    return bytes;
}
vector<unsigned char> ByteUtil::concatenate3(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    bytes.insert(bytes.end(), bytes3.begin(), bytes3.end());
    return bytes;
}
vector<unsigned char> ByteUtil::concatenate4(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3,vector<unsigned char> bytes4){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    bytes.insert(bytes.end(), bytes3.begin(), bytes3.end());
    bytes.insert(bytes.end(), bytes4.begin(), bytes4.end());
    return bytes;
}

vector<unsigned char> ByteUtil::stringToUtf8Bytes(string stringValue){
    //TODO make sure really utf8 bytes?
    vector<unsigned char> bytes(stringValue.begin(), stringValue.end());
    return bytes;
}
string ByteUtil::utf8BytesToString(vector<unsigned char> bytesValue){
    string value(bytesValue.begin(), bytesValue.end());
    return value;
}
vector<unsigned char> ByteUtil::booleanToUtf8Bytes(bool booleanValue){
    return ByteUtil::stringToUtf8Bytes(booleanValue ? "t" : "f");
}
bool ByteUtil::utf8BytesToBoolean(vector<unsigned char> bytesValue){
    return ByteUtil::utf8BytesToString(bytesValue)=="t"?true:false;
}
vector<unsigned char> ByteUtil::random32Bytes(){
    vector<unsigned char> bytes;
    for(int i=0;i<32;i++){
        bytes.push_back((unsigned char)rand());
    }
    return bytes;
}

vector<unsigned char> ByteUtil::concatenateLength(vector<unsigned char> value){
    return ByteUtil::concatenate(ByteUtil::uint64ToBytes(value.size()),value);
}
vector<unsigned char> ByteUtil::flat(vector<vector<unsigned char>> values){
    vector<unsigned char> concatBytes;
    for(vector<unsigned char> value:values){
        concatBytes = ByteUtil::concatenate(concatBytes,value);
    }
    return concatBytes;
}
vector<unsigned char> ByteUtil::flatAndConcatenateLength(vector<vector<unsigned char>> values){
    vector<unsigned char> flatBytes = flat(values);
    return concatenateLength(flatBytes);
}
bool ByteUtil::isEquals(vector<unsigned char> bytes1, vector<unsigned char> bytes2){
    if(bytes1.size() != bytes2.size()){
        return false;
    }
    return std::equal(bytes1.begin(), bytes1.begin() + bytes1.size(), bytes2.begin());
}
