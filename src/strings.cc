/*************************************************************************
> FileName: strings.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月30日 星期二 16时11分55秒
 ************************************************************************/
#include <iostream>
#include <string.h>
#include <assert.h>
#include "strings.h"

EdgarString::EdgarString(unsigned int size) {
    this ->size = size > 0 ? size : STRING_SIZE;
    this ->str = new char[this ->size];
    this ->pos = 0;
    this ->str[0] = 0;
}

EdgarString::EdgarString(char* str) {
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

void EdgarString::recycle(unsigned int size) {
    if(this ->size > size) {
        delete[] str;
        str = new char[size];
        this ->size = size;
    }
    pos = 0;
    str[0] = 0;
}

void EdgarString::addChar(char c) {
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

void EdgarString::addString(char* s) {
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

char* EdgarString::copyString() {
    char* tmp = new char[pos + 1];
    memcpy(tmp, str, pos);
    tmp[pos] = 0;
    return tmp;
}

unsigned int EdgarString::len() {
    return pos;
}

void EdgarString::setChar(unsigned int i, char c) {
    str[i] = c;
}

char& EdgarString::operator[](unsigned int i) {
    assert(i <= pos);
    return this ->str[i];
}

EdgarString::~EdgarString() {
    delete[] str;
}
