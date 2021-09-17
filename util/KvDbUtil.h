//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_KVDBUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_KVDBUTIL_H

#include <string>
#include <vector>

using namespace std;

enum KvWriteActionEnum {
    ADD,DELETE
};
class KvWrite{
    private:
        KvWriteActionEnum kvWriteActionEnum;
        vector<unsigned char> key;
        vector<unsigned char> value;
};
class KvWriteBatch{
    private:
        vector<KvWrite> kvWrites;
    public:
        void put(vector<unsigned char> key, vector<unsigned char> value);
        void delete0(vector<unsigned char> key);
};

namespace KvDbUtil {
    void put(string dbPath, vector<unsigned char> bytesKey, vector<unsigned char> bytesValue);
    // TODO delete is cpp keyword , so named delete0
    void delete0(string dbPath, vector<unsigned char> bytesKey);
    string get(string dbPath, vector<unsigned char> bytesKey);
    vector<string> gets(string dbPath, long from, long size) ;
    void put(string dbPath, vector<unsigned char> bytesKey, vector<unsigned char> bytesValue);
    void write(string dbPath, KvWriteBatch kvWriteBatch);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_KVDBUTIL_H
