//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
#include <string>
using namespace std;


class Account{
    public:
        string privateKey;
        string publicKey;
        string publicKeyHash;
        string address;
};

namespace AccountUtil {
    Account randomAccount() ;
    Account accountFromPrivateKey(string privateKey);
    string addressFromPublicKey(string privateKey);
    string base58AddressFromPublicKeyHash0(string bytesPublicKeyHash);
    string publicKeyHashFromPublicKey(string publicKey);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
