//
// Created by 40906 on 2021/9/12.
//

#include "LogUtil.h"
#include <iostream>

using namespace std;

void LogUtil::log(string file, string function, long line, unsigned int level, string message) {
	if (level == LOG_DEBUG) {
		cout << "[D] ";
	}
	else if (level == LOG_ERROR) {
		cout << "[E] ";
	}

	cout << message;
	cout << " [" << file << ":" << function << ", " << line << "]" << endl;	
}


