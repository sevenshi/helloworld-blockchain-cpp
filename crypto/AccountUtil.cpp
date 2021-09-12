//
// Created by 40906 on 2021/9/12.
//

#include "AccountUtil.h"
#include "ByteUtil.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

using namespace std;


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
    EC_KEY_free(key);
    return a;
}

Account AccountUtil::accountFromPrivateKey(string privateKey) {
    BIGNUM *priv_key;
    priv_key = BN_new();
    int a = BN_hex2bn(&priv_key,privateKey.c_str());

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
    EC_KEY_free(key);
    return account;
}