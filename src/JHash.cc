/*************************************************************************
> FileName: ./JHash.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 10时50分34秒
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "JIO.h"
#include "JHash.h"

JHash::JHash(unsigned int size, char* initFile, bool scratch) {
    this ->size = size;
    this ->file = initFile;
    this ->table = new char[size / 8];
    if(NULL == initFile || scratch) {
        for(unsigned int i = 0; i < size / 8; ++ i) {
            table[i] = 0;
        }
    } else {
        int fds = open(initFile, O_RDONLY);
        if(fds < 0) {
            // errlog
            for(unsigned int i = 0; i < size / 8; ++ i) {
                table[i] = 0;
            }
        } else {
            unsigned sr = 0;
            while (sr < size) {
                unsigned int tmp = read(fds, table + sr, size - sr);
                if(tmp <= 0) {
                    // err log
                    exit(1);
                } else {
                    sr += 8 * tmp;
                }
            }
        }
        close(fds);
    }
}

JHash::~JHash() {
    delete[] table;
}

bool JHash::addDoc(char* doc) {
    unsigned int code = 0;
    char c;
    for(unsigned int i = 0; (c = doc[i]) != 0; ++ i) {
        if(c > 'A' && c < 'z') {
            code = (code * 23 + c) % size;
        }
    }
    unsigned int pos = code / 8;
    unsigned int bits = 1 << (code % 8);
    int res = table[pos] & bits;
    table[pos] |= bits;

    return !res;
}

void JHash::save() {
    int fds = creat(file, 0060);
    if(fds >= 0) {
        //写入
        write_buff(fds, table, size / 8);
        close(fds);
    }
}

















