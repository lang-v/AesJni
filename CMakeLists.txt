cmake_minimum_required(VERSION 3.21)
project(aes)

if(CMAKE_CL_64)    #CMAKE的内建变量，如果是true，就说明编译器的64位的，自然可以编译64bit的程序
    set(ADDRESS_MODEL 64)
    set(NODE_TARGET x64)
else()
    set(ADDRESS_MODEL 32)
    set(NODE_TARGET x86)
endif()
set(BUILD_USE_64BITS on)
set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. ll)


#base64/cdecode.h base64/cencode.h base64/encode.h base64/decode.h base64/cencode.cpp base64/cdecode.cpp com_sl_web_server_encrypt_AesEncrypt.cpp
add_library(aes SHARED aes.cpp utils.cpp cdecode.cpp cencode.cpp cencode.h cdecode.h encode.h decode.h utils.h com_sl_web_server_code_Aes.h)
