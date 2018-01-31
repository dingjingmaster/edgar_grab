/*************************************************************************
> FileName: JString.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月30日 星期二 16时11分55秒
 ************************************************************************/
#include <iostream>
#include <string.h>
#include <assert.h>
#include "JString.h"

JString::JString(unsigned int size) {
    this ->size = size > 0 ? size : STRING_SIZE;
    this ->str = new char[this ->size];
    this ->pos = 0;
    this ->str[0] = 0;
}

JString::JString(char* str) {
    size = STRING_SIZE;
    unsigned int msize = strlen(str);
    while(msize >= size) {
        size *= STRING_STEP;
    }
    this ->str = new char[size];
    memcpy(this ->str, str, msize);
    this ->pos = msize;
    this ->str[msize] = 0;
}

void JString::recycle(unsigned int size) {
    if(this ->size > size) {
        delete[] str;
        str = new char[size];
        this ->size = size;
    }
    pos = 0;
    str[0] = 0;
}

void JString::addChar(char c) {
    str[pos] = c;
    ++ pos;
    if (pos >= size) {
        size *= STRING_STEP;
        char* tmp = new char[size];
        memcpy(tmp, str, pos);
        delete[] str;
        str = tmp;
    }
    str[pos] = 0;
}

void JString::addString(char* s) {
    unsigned int ssize = strlen(s);
    unsigned int tsize = size;
    unsigned int msize = ssize + pos;
    while(msize >= tsize) {
        tsize *= STRING_STEP;
    }
    if(tsize != size) {
        char* tmp = new char[tsize];
        memcpy(tmp, str, pos);
        delete[] str;
        str = tmp;
        size = tsize;
    }
    memcpy(str + pos, s, ssize);
    pos += ssize;
    str[pos] = 0;
}

char* JString::copyString() {
    char* tmp = new char[pos + 1];
    memcpy(tmp, str, pos);
    tmp[pos] = 0;
    return tmp;
}

unsigned int JString::len() {
    return pos;
}

void JString::setChar(unsigned int i, char c) {
    str[i] = c;
}

char& JString::operator[](unsigned int i) {
    assert(i <= pos);
    return this ->str[i];
}

JString::~JString() {
    delete[] str;
}
