cmake_minimum_required(VERSION 3.0)
project(helloworld_blockchain_cpp)

set(CMAKE_CXX_STANDARD 14)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(helloworld_blockchain_cpp main.cpp crypto/Sha256Util.cpp crypto/Sha256Util.h crypto/Ripemd160Util.cpp crypto/Ripemd160Util.h crypto/ByteUtil.cpp crypto/ByteUtil.h crypto/Base58Util.cpp crypto/Base58Util.h crypto/AccountUtil.cpp crypto/AccountUtil.h main2.cpp)

include_directories(D:\\libs\\openssl\\openssl-1.1.1-win32-debug\\include)
target_link_libraries(helloworld_blockchain_cpp D:\\libs\\openssl\\openssl-1.1.1-win32-debug\\lib\\libcrypto.lib D:\\libs\\openssl\\openssl-1.1.1-win32-debug\\lib\\libssl.lib)
