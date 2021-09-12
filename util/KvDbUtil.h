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
        string key;
        string value;
};
class KvWriteBatch{
    private:
        vector<KvWrite> kvWrites;
    // TODO
    void put(string key, string value);
    void delete0(string key);
};

namespace KvDbUtil {
    void put(string dbPath, string bytesKey, string bytesValue);
    // TODO delete is cpp keyword
    void delete0(string dbPath, string bytesKey);
    string get(string dbPath, string bytesKey);
    vector<string> gets(string dbPath, long from, long size) ;
    void put(string dbPath, string bytesKey, string bytesValue);
    void write(string dbPath, KvWriteBatch kvWriteBatch);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_KVDBUTIL_H
