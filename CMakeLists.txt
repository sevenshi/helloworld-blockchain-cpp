cmake_minimum_required(VERSION 3.0)
project(helloworld_blockchain_cpp)

set(CMAKE_CXX_STANDARD 14)
set(project_name "helloworld_blockchain_cpp")
set(openssl_path "D:\\libs\\openssl\\openssl-1.1.1-win32-debug")

#mac
#set(openssl_path "/usr/local/opt/openssl@1.1")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${project_name} main.cpp crypto/Sha256Util.cpp crypto/Sha256Util.h crypto/Ripemd160Util.cpp crypto/Ripemd160Util.h crypto/ByteUtil.cpp crypto/ByteUtil.h crypto/Base58Util.cpp crypto/Base58Util.h crypto/AccountUtil.cpp crypto/AccountUtil.h util/FileUtil.cpp util/FileUtil.h util/NetUtil.cpp util/NetUtil.h util/OperateSystemUtil.cpp util/OperateSystemUtil.h util/SystemUtil.cpp util/SystemUtil.h util/ThreadUtil.cpp util/ThreadUtil.h util/TimeUtil.cpp util/TimeUtil.h util/StringUtil.cpp util/StringUtil.h util/LogUtil.cpp util/LogUtil.h util/JsonUtil.cpp util/JsonUtil.h util/KvDbUtil.cpp util/KvDbUtil.h)

include_directories(${openssl_path}\\include)
target_link_libraries(${project_name} ${openssl_path}\\lib\\libcrypto.lib ${openssl_path}\\lib\\libssl.lib)

#mac
#target_link_libraries(${project_name} ${openssl_path}/lib/libcrypto.dylib ${openssl_path}/lib/libssl.dylib)