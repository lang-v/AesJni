#include "com_sl_web_server_code_Aes.h"
#include "utils.h"

JNIEXPORT jstring JNICALL Java_com_sl_web_server_code_Aes_version
        (JNIEnv * env, jobject){
    jstring str = env->NewStringUTF("version:0.0.1 \nbuild time: 2022/03/21 \nby Frontman.");
    return str;
}

/**
 * java使用的宽字符，jchar 直接转换成 char 导致精度丢失
 *     WideCharToMultiByte();
 * */
JNIEXPORT jcharArray JNICALL Java_com_sl_web_server_code_Aes_encrypt
        (JNIEnv * env, jobject, jcharArray word, jcharArray key){
//    return nullptr;
    int wordLength = env->GetArrayLength(word)+1;
    int keyLength = env->GetArrayLength(key)+1;

    jboolean isCopy = true;
    jchar* jwordArray = env->GetCharArrayElements(word, &isCopy);
    jchar* jkeyArray = env->GetCharArrayElements(key, &isCopy);

    char* wordArray = (char*) malloc(wordLength);
    char* keyArray = (char*) malloc(keyLength);

    for (int i = 0; i < wordLength; ++i) {
        wordArray[i] = jwordArray[i];
    }
    wordArray[wordLength-1] = '\0';
    for (int i = 0; i < keyLength; ++i) {
        keyArray[i] = jkeyArray[i];
    }
    keyArray[keyLength-1] = '\0';

    char* layer_one = (char*) malloc(wordLength);
    layer_one[wordLength-1] = '\0';
    // 第一层 逐字节 按位异或
    for (int i = 0; i < wordLength - 1; i++) {
        char temp = keyArray[i % (keyLength-2)];
        char temp_2 = wordArray[i];
        // fixed 相同字符异或得到的 '\0' 导致字符串被截断
        if (temp_2 == temp) {
            layer_one[i] = temp_2;
            continue;
        }
        layer_one[i] = temp_2 ^ temp ;
    }

    // 第二层打乱顺序
    int range = wordLength - 1;
    if (range % 2 == 1) {
        range--;
    }
    for (int i = 0; i < range; i += 2) {
        char t = layer_one[i];
        layer_one[i] = layer_one[i+1];
        layer_one[i+1] = t;
    }

//     第三层 编码Base64 方便传输
    base64_bean bean = base64_encode(layer_one, 2 * wordLength);
    jchar* jp = (jchar*)calloc(sizeof(jchar), bean.length);
    for (int i = 0; i < bean.length; ++i) {
        jp[i] = bean.str[i];
    }

    // 准备最后的输出
    // wordLength -1； c++ 将\0 作为字符串终止符
    jcharArray result = env->NewCharArray(bean.length-1);
    env->SetCharArrayRegion(result,0,bean.length-1,jp);

    // 方法结束前回收内存
    free(keyArray);
    free(wordArray);
    keyArray = nullptr;
    wordArray = nullptr;

//    free(jkeyArray);
//    free(jwordArray);
//    jkeyArray = nullptr;
//    jwordArray = nullptr;

    free(bean.str);
    bean.str = nullptr;

    free(jp);
    jp = nullptr;

    return result;
}

/*
 * Class:     com_sl_web_server_encrypt_AesEncrypt
 * Method:    decrypt
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jcharArray JNICALL Java_com_sl_web_server_code_Aes_decrypt
        (JNIEnv * env, jobject obj, jcharArray word, jcharArray key){

    int wordLength = env->GetArrayLength(word) + 1;
    int keyLength = env->GetArrayLength(key) + 1;

    jchar* jwordArray = env->GetCharArrayElements(word, nullptr);
    jchar* jkeyArray = env->GetCharArrayElements(key, nullptr);

    char* wordArray = (char*) malloc(wordLength);
    char* keyArray = (char*) malloc(keyLength);
    for (int i = 0; i < wordLength; ++i) {
        wordArray[i] = jwordArray[i];
    }
    wordArray[wordLength-1] = '\0';
    for (int i = 0; i < keyLength; ++i) {
        keyArray[i] = jkeyArray[i];
    }
    keyArray[keyLength-1] = '\0';

    // 第三层 base64 解码
    base64_bean bean = base64_decode(reinterpret_cast<const char *>(wordArray), wordLength);

    wordLength = bean.length;
    char *layer_two = bean.str;

    // 第二层 恢复顺序
    int range = wordLength - 1;
    if (range % 2 == 1) {
        range--;
    }
    for (int i = 0; i < range; i += 2) {
        char t = layer_two[i];
        layer_two[i] = layer_two[i+1];
        layer_two[i+1] = t;
    }

    char* layer_one = (char*)malloc(wordLength);
    layer_one[wordLength - 1] = '\0';

    // 第一层 相异或
    for (int i = 0; i < wordLength - 1; ++i) {
        char temp = keyArray[i % (keyLength-2)] ;
        char temp_2 = layer_two[i] ;
        if (temp == temp_2){
            layer_one[i] = temp;
            continue;
        }
        layer_one[i] = temp ^ temp_2;
    }

    jchar* jp = (jchar*)calloc(sizeof(jchar), wordLength);
    for (int i = 0; i < wordLength; ++i) {
        jp[i] = layer_one[i];
    }
    // 准备最后的输出
    // wordLength -1； c++ 将\0 作为字符串终止符
    jcharArray result = env->NewCharArray(wordLength-1);
    env->SetCharArrayRegion(result,0,wordLength-1,jp);

    // 方法前回收内存
    free(keyArray);
    free(wordArray);
    keyArray = nullptr;
    wordArray = nullptr;

//    free(jkeyArray);
//    free(jwordArray);
//    jkeyArray = nullptr;
//    jwordArray = nullptr;

    free(bean.str);
    bean.str = nullptr;

    free(jp);
    jp = nullptr;

    return result;
}


