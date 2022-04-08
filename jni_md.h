/*
 * Copyright (c) 1996, 1998, Oracle and/or its affiliates. All rights reserved.
 * ORACLE PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#ifndef _JAVASOFT_JNI_MD_H_
#define _JAVASOFT_JNI_MD_H_

//#define JNIEXPORT __declspec(dllexport)
//#define JNIIMPORT __declspec(dllimport)
//#define JNICALL __stdcall
#ifdef _WIN32
#define JNIEXPORT __declspec(dllexport)
    #define JNIIMPORT __declspec(dllimport)
    #define JNICALL __stdcall
    typedef __int64 jlong;

#else
#define JNIEXPORT
#define JNIIMPORT
#define JNICALL
typedef __int64_t jlong;
#endif
typedef long jint;
typedef signed char jbyte;

#endif /* !_JAVASOFT_JNI_MD_H_ */
