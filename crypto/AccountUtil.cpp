//
// Created by 40906 on 2021/9/12.
//

#include "AccountUtil.h"
#include "ByteUtil.h"
#include "Ripemd160Util.h"
#include "Sha256Util.h"
#include "Base58Util.h"
#include "../util/StringUtil.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <vector>
using namespace std;

const vector<unsigned char> VERSION = {0x00};

Account AccountUtil::randomAccount() {
    EC_KEY* key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if(!key)
    {
        std::cerr << "Error creating curve key" << '\n';
        //return EXIT_FAILURE;
    }

    if(!EC_KEY_generate_key(key))
    {
        std::cerr << "Error generating curve key" << '\n';
        EC_KEY_free(key);
        //return EXIT_FAILURE;
    }

    BIGNUM const* prv = EC_KEY_get0_private_key(key);
    if(!prv)
    {
        std::cerr << "Error getting private key" << '\n';
        EC_KEY_free(key);
        //return EXIT_FAILURE;
    }

    //std::cout << "Private key: " << prv << '\n';
    char* stringPrivateKey = BN_bn2hex(prv);
    //std::cout << "Private key: " << www << '\n';

    EC_POINT const* pub = EC_KEY_get0_public_key(key);
    if(!pub)
    {
        std::cerr << "Error getting public key" << '\n';
        EC_KEY_free(key);
        //return EXIT_FAILURE;
    }

    //std::cout << "Public key: " << pub << '\n';
    EC_GROUP *ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    char* stringPublicKey =  EC_POINT_point2hex(ec_group, pub,POINT_CONVERSION_COMPRESSED,NULL);
    //std::cout << "COMPRESSED public key: " << zzz << '\n';

    // Use keys here ...
    Account a;
    a.privateKey = stringPrivateKey;
    a.publicKey = stringPublicKey;
    a.publicKeyHash = publicKeyHashFromPublicKey(stringPublicKey);
    a.address = addressFromPublicKey(stringPublicKey);
    EC_KEY_free(key);
    return a;
}

Account AccountUtil::accountFromPrivateKey(string privateKey) {
    BIGNUM *priv_key;
    priv_key = BN_new();
    BN_hex2bn(&priv_key,privateKey.c_str());

    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_KEY *key = EC_KEY_new();
    EC_POINT *pub_key = EC_POINT_new(group);

    EC_KEY_set_group(key, group);
    EC_KEY_set_private_key(key, priv_key);
    EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, NULL);
    EC_KEY_set_public_key(key, pub_key);

    char* stringPrivateKey = BN_bn2hex(priv_key);

    EC_GROUP *ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    char* stringPublicKey =  EC_POINT_point2hex(ec_group, pub_key,POINT_CONVERSION_COMPRESSED,NULL);

    Account account;
    account.privateKey = stringPrivateKey;
    account.publicKey = stringPublicKey;
    account.publicKeyHash = publicKeyHashFromPublicKey(stringPublicKey);
    account.address = addressFromPublicKey(stringPublicKey);
    EC_KEY_free(key);
    return account;
}

string AccountUtil::publicKeyHashFromPublicKey(string publicKey) {
    vector<unsigned char> bytesPublicKey = ByteUtil::hexStringToBytes(publicKey);
    vector<unsigned char> bytesPublicKeyHash = Ripemd160Util::digest(Sha256Util::digest(bytesPublicKey));
    return ByteUtil::bytesToHexString(bytesPublicKeyHash);
}
string AccountUtil::publicKeyHashFromAddress(string address){
    vector<unsigned char> bytesAddress = Base58Util::decode(address);
    vector<unsigned char> bytesPublicKeyHash = ByteUtil::copy(bytesAddress, 1, 20);
    return ByteUtil::bytesToHexString(bytesPublicKeyHash);
}


string AccountUtil::addressFromPrivateKey(string privateKey){
    Account account = accountFromPrivateKey(privateKey);
    return addressFromPublicKey(account.publicKey);
}
string AccountUtil::addressFromPublicKey(string publicKey) {
    string publicKeyHash = publicKeyHashFromPublicKey(publicKey);
    return base58AddressFromPublicKeyHash0(ByteUtil::hexStringToBytes(publicKeyHash));
}
string AccountUtil::addressFromPublicKeyHash(string publicKeyHash){
    vector<unsigned char> bytesPublicKeyHash = ByteUtil::hexStringToBytes(publicKeyHash);
    return base58AddressFromPublicKeyHash0(bytesPublicKeyHash);
}
vector<unsigned char> AccountUtil::signature(string privateKey, vector<unsigned char> bytesMessage){
    BIGNUM *priv_key;
    priv_key = BN_new();
    BN_hex2bn(&priv_key,privateKey.c_str());

    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_KEY *key = EC_KEY_new();
    EC_POINT *pub_key = EC_POINT_new(group);

    EC_KEY_set_group(key, group);
    EC_KEY_set_private_key(key, priv_key);
    EC_POINT_mul(group, pub_key, priv_key, NULL, NULL, NULL);
    EC_KEY_set_public_key(key, pub_key);

    vector<unsigned char> sig(100);
    unsigned int siglen;
    ECDSA_sign(0,&bytesMessage[0],bytesMessage.size(),&sig[0],&siglen,key);
    vector<unsigned char> ret = ByteUtil::copy(sig,0,siglen);
    return ret;
}
bool AccountUtil::verifySignature(string publicKey, vector<unsigned char> bytesMessage, vector<unsigned char> bytesSignature){
    EC_GROUP *ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *pub = EC_POINT_new(ec_group);
    EC_POINT_hex2point(ec_group, reinterpret_cast<const char *>(&publicKey[0]), pub, NULL);

/*    char* stringPublicKey =  EC_POINT_point2hex(ec_group, pub,POINT_CONVERSION_COMPRESSED,NULL);
    std::cout << "COMPRESSED public key: " << stringPublicKey << '\n';*/

    EC_KEY *key = EC_KEY_new();
    EC_POINT *pub_key = EC_POINT_new(ec_group);
    EC_KEY_set_group(key, ec_group);
    EC_KEY_set_public_key(key, pub_key);

    EC_KEY_set_public_key(key,pub);
    int verifyFlag = ECDSA_verify(0,&bytesMessage[0],bytesMessage.size(),&bytesSignature[0],bytesSignature.size(),key);
    return verifyFlag == 1;
}
string AccountUtil::formatPrivateKey(string privateKey){
    return StringUtil::prefixPadding(privateKey,64,"0");
}
bool AccountUtil::isPayToPublicKeyHashAddress(string address){
    vector<unsigned char> bytesAddress = Base58Util::decode(address);
    vector<unsigned char> bytesPublicKeyHash(20);
    ByteUtil::copyTo(bytesAddress, 1, 20, bytesPublicKeyHash, 0);
    string base58Address = addressFromPublicKeyHash(ByteUtil::bytesToHexString(bytesPublicKeyHash));
    return StringUtil::isEquals(base58Address,address);
}

string AccountUtil::base58AddressFromPublicKeyHash0(vector<unsigned char> bytesPublicKeyHash) {
    //地址版本号(1个字节)与公钥哈希(20个字节)
    vector<unsigned char> bytesVersionAndPublicKeyHash = ByteUtil::concatenate(VERSION,bytesPublicKeyHash);
    //地址校验码(4个字节)
    vector<unsigned char> bytesCheckCode = ByteUtil::copy(Sha256Util::doubleDigest(bytesVersionAndPublicKeyHash), 0, 4);

    //地址(25个字节)=地址版本号(1个字节)+公钥哈希(20个字节)+地址校验码(4个字节)
    vector<unsigned char> bytesAddress = ByteUtil::concatenate(bytesVersionAndPublicKeyHash,bytesCheckCode);

    //用Base58编码地址
    string base58Address = Base58Util::encode(bytesAddress);
    return base58Address;
}