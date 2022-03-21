#include "utils.h"

base64_bean base64_encode(const char* input, int length)
{
    char *output = (char*)malloc(length);
    char* c = output;
    int cnt = 0;
    int code_count = 0;
    base64_encodestate s;

    base64_init_encodestate(&s);
    cnt = base64_encode_block(input, strlen(input), c, &s);
    c += cnt;
    code_count += cnt;
    cnt = base64_encode_blockend(c, &s);
    c += cnt;
    code_count += cnt;
    *c = 0;
    base64_bean bean{};
    bean.str = output;
    bean.length = code_count+1;
    return bean;
}

base64_bean base64_decode(const char* input, int size)
{
    char* output = (char *)malloc(size);
    char* c = output;
    int cnt = 0;
    base64_decodestate s;
    base64_init_decodestate(&s);
    cnt = base64_decode_block(input, strlen(input), c, &s);
    c += cnt;
    *c = 0;

    base64_bean bean{};
    bean.str = output;
    bean.length = cnt + 1;
    return bean;
}


inline void swap_elements(char &a, char &b) {
    char t = a;
    a = b;
    b = t;
}