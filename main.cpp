#include <iostream>
#include "crypto/Sha256Util.h"
#include "crypto/Ripemd160Util.h"
#include "crypto/Base58Util.h"
#include "crypto/AccountUtil.h"
#include "crypto/ByteUtil.h"
#include "util/ThreadUtil.h"
#include "util/TimeUtil.h"
#include <string>


using namespace std;

int main()
{
    cout << ByteUtil::bytesToHexString(Sha256Util::digest(ByteUtil::hexStringToBytes("00"))) << endl;
    cout << ByteUtil::bytesToHexString(Sha256Util::digest(ByteUtil::hexStringToBytes("01"))) << endl;
    cout << ByteUtil::bytesToHexString(Sha256Util::digest(ByteUtil::hexStringToBytes("02"))) << endl;
    cout << ByteUtil::bytesToHexString(Ripemd160Util::digest(ByteUtil::hexStringToBytes("00"))) << endl;
    cout << ByteUtil::bytesToHexString(Ripemd160Util::digest(ByteUtil::hexStringToBytes("01"))) << endl;
    cout << ByteUtil::bytesToHexString(Ripemd160Util::digest(ByteUtil::hexStringToBytes("02"))) << endl;
    cout << Base58Util::encode(ByteUtil::hexStringToBytes("18EFBA81F02B8BFF148118BB58F38820642CCCC159E32254AEC4606CE6C71CC4FC124A1C7B61122BABE0576669F515A77568EED494F1E60B65DF3284269A153C36EC8D5911D77998FA530C689531")) << endl;
    cout << ByteUtil::bytesToHexString(Base58Util::decode("ovT8b5DW8RXymPeAzFPVLvMHq7rxMbHmtdUkaEHPPbMeWXqqWXBPbYwSpJF1tLefTyKkQwwMxDdgZNxxiYxqWe22SJt3LiEywZW8J7gSBJ")) << endl;
    Account account = AccountUtil::randomAccount();
    cout << "---------------------account" << endl;
    cout << account.privateKey << endl;
    cout << account.publicKey << endl;
    cout << account.publicKeyHash << endl;
    cout << account.address << endl;
    Account account2 = AccountUtil::accountFromPrivateKey(account.privateKey);
    cout << "---------------------account2" << endl;
    cout << account2.privateKey << endl;
    cout << account2.publicKey << endl;
    cout << account2.publicKeyHash << endl;
    cout << account2.address << endl;


    cout << TimeUtil::millisecondTimestamp() << endl;
    cout << TimeUtil::formatMillisecondTimestamp( TimeUtil::millisecondTimestamp()) << endl;


    return 0;
}