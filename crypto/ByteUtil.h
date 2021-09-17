//
// Created by 40906 on 2021/9/12.
//

#ifndef UNTITLED_BYTEUTIL_H
#define UNTITLED_BYTEUTIL_H

#include <string>
#include <vector>
using namespace std;

namespace ByteUtil {
    string bytesToHexString(vector<unsigned char> bytes);
    vector<unsigned char> hexStringToBytes(const string& hex);

    //TODO uint64_t跨平台吗?64位吗?
    vector<unsigned char> uint64ToBytes(uint64_t number);
    uint64_t bytesToUint64(vector<unsigned char> bytes);

    vector<unsigned char> stringToUtf8Bytes(string stringValue);
    string utf8BytesToString(vector<unsigned char> bytesValue);

    vector<unsigned char> booleanToUtf8Bytes(bool booleanValue);
    bool utf8BytesToBoolean(vector<unsigned char> bytesValue);

    vector<unsigned char> concatenate(vector<unsigned char> bytes1,vector<unsigned char> bytes2);
    vector<unsigned char> concatenate3(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3);
    vector<unsigned char> concatenate4(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3,vector<unsigned char> bytes4);

    vector<unsigned char> concatenateLength(vector<unsigned char> value);
    vector<unsigned char> flat(vector<vector<unsigned char>> values);
    vector<unsigned char> flatAndConcatenateLength(vector<vector<unsigned char>> values);
    bool isEquals(vector<unsigned char> bytes1, vector<unsigned char> bytes2);

    vector<unsigned char> copy(vector<unsigned char> sourceBytes, int startPosition, int length);
    void copyTo(vector<unsigned char> sourceBytes, int sourceStartPosition, int length, vector<unsigned char> &destinationBytes, int destinationStartPosition);

    vector<unsigned char> random32Bytes();
};


#endif //UNTITLED_BYTEUTIL_H
