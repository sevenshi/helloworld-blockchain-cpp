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

string encodePrivateKey0(BIGNUM const* bignumPrivateKey) {
    char* stringPrivateKey = BN_bn2hex(bignumPrivateKey);
    return AccountUtil::formatPrivateKey(stringPrivateKey);
}
BIGNUM *decodePrivateKey0(string privateKey) {
    BIGNUM *bignumPrivateKey;
    bignumPrivateKey = BN_new();
    BN_hex2bn(&bignumPrivateKey,privateKey.c_str());
    return bignumPrivateKey;
}
string encodePublicKey0(EC_POINT const* ecPointPublicKey) {
    if(!ecPointPublicKey)
    {
        std::cerr << "Error getting public key" << '\n';
    }
    EC_GROUP *ecGroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
    char* stringPublicKey =  EC_POINT_point2hex(ecGroup, ecPointPublicKey,POINT_CONVERSION_COMPRESSED,NULL);
    return stringPublicKey;
}
string base58AddressFromPublicKeyHash0(vector<unsigned char> bytesPublicKeyHash) {
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

Account AccountUtil::randomAccount() {
    EC_KEY* ecKey = EC_KEY_new_by_curve_name(NID_secp256k1);
    if(!ecKey)
    {
        std::cerr << "Error creating curve key" << '\n';
        //return EXIT_FAILURE;
    }
    if(!EC_KEY_generate_key(ecKey))
    {
        std::cerr << "Error generating curve key" << '\n';
        EC_KEY_free(ecKey);
        //return EXIT_FAILURE;
    }

    BIGNUM const* bignumPrivateKey = EC_KEY_get0_private_key(ecKey);
    if(!bignumPrivateKey)
    {
        std::cerr << "Error getting private key" << '\n';
        EC_KEY_free(ecKey);
        //return EXIT_FAILURE;
    }

    EC_POINT const* ecPointPublicKey = EC_KEY_get0_public_key(ecKey);
    if(!ecPointPublicKey)
    {
        std::cerr << "Error getting public key" << '\n';
        EC_KEY_free(ecKey);
        //return EXIT_FAILURE;
    }

    Account a;
    a.privateKey = encodePrivateKey0(bignumPrivateKey);
    a.publicKey = encodePublicKey0(ecPointPublicKey);
    a.publicKeyHash = publicKeyHashFromPublicKey(a.publicKey );
    a.address = addressFromPublicKey(a.publicKey );
    EC_KEY_free(ecKey);
    return a;
}

EC_POINT * publicKeyFromPrivateKey0(BIGNUM *bignumPrivateKey) {
    EC_GROUP *ecGroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_KEY *ecKey = EC_KEY_new();
    EC_POINT *ecPointPublicKey = EC_POINT_new(ecGroup);

    EC_KEY_set_group(ecKey, ecGroup);
    EC_KEY_set_private_key(ecKey, bignumPrivateKey);
    EC_POINT_mul(ecGroup, ecPointPublicKey, bignumPrivateKey, NULL, NULL, NULL);
    EC_KEY_set_public_key(ecKey, ecPointPublicKey);
    return ecPointPublicKey;
}

Account AccountUtil::accountFromPrivateKey(string privateKey) {
    BIGNUM *bignumPrivateKey = decodePrivateKey0(privateKey);
    EC_POINT *ecPointPublicKey = publicKeyFromPrivateKey0(bignumPrivateKey);

    Account account;
    account.privateKey = privateKey;
    account.publicKey = encodePublicKey0(ecPointPublicKey);
    account.publicKeyHash = publicKeyHashFromPublicKey(account.publicKey);
    account.address = addressFromPublicKey(account.publicKey);
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
    BIGNUM *bignumPrivateKey = BN_new();
    BN_hex2bn(&bignumPrivateKey, privateKey.c_str());

    EC_GROUP *ecGroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *ecPointPublicKey = EC_POINT_new(ecGroup);
    EC_POINT_mul(ecGroup, ecPointPublicKey, bignumPrivateKey, NULL, NULL, NULL);

    EC_KEY *ecKey = EC_KEY_new();
    EC_KEY_set_group(ecKey, ecGroup);
    EC_KEY_set_private_key(ecKey, bignumPrivateKey);
    EC_KEY_set_public_key(ecKey, ecPointPublicKey);

    vector<unsigned char> sig(100);
    unsigned int siglen;
    ECDSA_sign(0,&bytesMessage[0],bytesMessage.size(),&sig[0],&siglen,ecKey);
    vector<unsigned char> ret = ByteUtil::copy(sig,0,siglen);
    return ret;
}
bool AccountUtil::verifySignature(string publicKey, vector<unsigned char> bytesMessage, vector<unsigned char> bytesSignature){
    EC_GROUP *ecGroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *ecPointPublicKey = EC_POINT_new(ecGroup);
    EC_POINT_hex2point(ecGroup, reinterpret_cast<const char *>(&publicKey[0]), ecPointPublicKey, NULL);

    EC_KEY *ecKey = EC_KEY_new();
    EC_KEY_set_group(ecKey, ecGroup);
    EC_KEY_set_public_key(ecKey,ecPointPublicKey);
    int verifyFlag = ECDSA_verify(0,&bytesMessage[0],bytesMessage.size(),&bytesSignature[0],bytesSignature.size(),ecKey);
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
