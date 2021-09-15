//
// Created by 40906 on 2021/9/12.
//

#ifndef HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
#define HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
#include <string>
#include <vector>
using namespace std;

class Account{
    public:
        string privateKey;
        string publicKey;
        string publicKeyHash;
        string address;
};

namespace AccountUtil {
    Account randomAccount();
    Account accountFromPrivateKey(string privateKey);

    string publicKeyHashFromPublicKey(string publicKey);
    string publicKeyHashFromAddress(string address);

    string addressFromPrivateKey(string privateKey);
    string addressFromPublicKey(string privateKey);
    string addressFromPublicKeyHash(string publicKeyHash);

    vector<unsigned char> signature(string privateKey, vector<unsigned char> bytesMessage);
    bool verifySignature(string publicKey, vector<unsigned char> bytesMessage, vector<unsigned char> bytesSignature);

    string formatPrivateKey(string privateKey);
    bool isPayToPublicKeyHashAddress(string address);

    //TODO private scope can delete?
    string base58AddressFromPublicKeyHash0(vector<unsigned char> bytesPublicKeyHash);
};


#endif //HELLOWORLD_BLOCKCHAIN_CPP_ACCOUNTUTIL_H
