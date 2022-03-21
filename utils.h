//
// Created by Frontman on 2022/3/20.
//

#ifndef AES_UTILS_H
#define AES_UTILS_H
#include <cstring>
#include <iostream>
#include "cencode.h"
#include "cdecode.h"

struct base64_bean{
    char* str;
    int length;
};

base64_bean base64_encode(const char* , int );
base64_bean base64_decode(const char* , int );
#endif //AES_UTILS_H
