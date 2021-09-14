//
// Created by 40906 on 2021/9/12.
//

#include "FileUtil.h"
#if defined _WIN32 || defined _WIN64
#include <iostream>
#include <direct.h>
#include <io.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#endif

static bool isExist(char *path) {
#if defined _WIN32 || defined _WIN64
	if (_access(path, 0) == 0) {
#else
	if (access(path, 0) == 0) {
#endif
		return true;
	}

	return false;
}

static void removeDirectory() {
#if defined _WIN32 || defined _WIN64
#else
	DIR* curDir = opendir(".");
	struct dirent* ent = NULL;
	struct stat st;

	if (!curDir) {
		cout << "opendir : . " << " fail !" << endl;
		exit(-1);
	}

	while ((ent = readdir(curDir)) != NULL) {
		stat(ent->d_name, &st);

		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
			continue;
		}

		if (S_ISDIR(st.st_mode)) {
			chdir(ent->d_name);
			removeDirectory();
			chdir("..");
		}

		if (remove(ent->d_name) == -1) {
			cout << "delete : " << ent->d_name << " fail !" << endl;
			exit(-1);
		}
	}

	closedir(curDir);
#endif
}

string FileUtil::newPath(string parent, string child) {
#if defined _WIN32 || defined _WIN64
	return parent + "\\" + child;
#else
	return parent + "/" + child;
#endif
}


void FileUtil::makeDirectory(string path) {
	char *tmpPath = new char[path.length() + 1];
#if defined _WIN32 || defined _WIN64
	sprintf_s(tmpPath, path.length() + 1, "%s", path.c_str());
#else
	snprintf(tmpPath, path.length() + 1, "%s", path.c_str());
#endif

	for (unsigned int i = 1; i < path.length() + 1; i++) {
		if ((tmpPath[i] == '/') || (tmpPath[i] == '\\') || (tmpPath[i] == 0)) {
			char tmp = tmpPath[i];
			tmpPath[i] = 0;

			if (!isExist(tmpPath)) {
#if defined _WIN32 || defined _WIN64
				if (_mkdir(tmpPath) == -1) {
#else
				if (mkdir(tmpPath, 0) == -1) {
#endif
					cout << "mkdir : " << tmpPath  << "fail !" << endl;
					exit(-1);
				}
			}

			tmpPath[i] = tmp;
		}
	}
}

void FileUtil::deleteDirectory(string path) {
#if defined _WIN32 || defined _WIN64
	HANDLE hFind;
	WIN32_FIND_DATAA findData;
	hFind = FindFirstFileA((path + "\\*").c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		cout << "open : " << path << " fail !" << endl;
		exit(-1);
	}

	do {
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;

		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			deleteDirectory((path + "\\" + findData.cFileName).c_str());
		}
		else {
			if (DeleteFileA((path + "\\" + findData.cFileName).c_str())) {
				cout << "delete : " << path + "\\" + findData.cFileName << " fail !" << endl;
				exit(-1);
			}
		}
	} while (FindNextFileA(hFind, &findData));

	if (hFind) {
		FindClose(hFind);
	}

	if (RemoveDirectoryA(path.c_str())) {
		cout << "delete : " << path << " fail !" << endl;
		exit(-1);
	}
#else
	char oldPath[4096];
	getcwd(oldPath, sizeof(oldPath));

	if (chdir(path.c_str()) == -1) {
		cout << "chdir : " << path << " fail !" << endl;
		exit(-1);
	}

	removeDirectory();
	chdir(oldPath);

	if (remove(path.c_str()) == -1) {
		cout << "delete : " << path << " fail !" << endl;
		exit(-1);
	}
#endif
}

#if 0
int main(int argc, char* argv[])
{
	string path = FileUtil::newPath("/home/zcr/helloworld-blockchain-cpp/trunk/util", "child");
	cout << "path = " << path << endl;

	FileUtil::makeDirectory(path);

	FileUtil::deleteDirectory("/home/zcr/helloworld-blockchain-cpp/trunk/util/openssl-1.1.1l/test");
	return 0;
}
#endif
