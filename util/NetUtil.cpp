//
// Created by 40906 on 2021/9/12.
//

#include "NetUtil.h"
#include "../thirdpart/httplib/httplib.h"


string  NetUtil::get(string requestUrl, string requestBody){
    // HTTP
    httplib::Client cli(requestUrl);
    if (auto res = cli.Post("/" ,requestBody,"application/json")) {
        if (res->status == 200) {
            return res->body ;
        }
    } else {
        auto err = res.error();
        return to_string(err);
    }
}


