/*************************************************************************
> FileName: strings.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月30日 星期二 15时56分08秒
 ************************************************************************/

#ifndef _STRINGS_H
#define _STRINGS_H
#include <iostream>

#define     STRING_SIZE     1024                                        // 默认内存大小
#define     STRING_STEP     2                                           // 扩展倍数

class EdgarString {
public:
    EdgarString(unsigned int size = STRING_SIZE);
    EdgarString(char* str);
    void recycle(unsigned int size);                                    // 最多只分配size内存,其它回收,且删除数据
    void addChar(char c);
    void setChar(unsigned int i, char c);
    void addString(char* s);
    char* copyString();
    unsigned int len();
    char& operator[](unsigned int i);
    ~EdgarString();

private:
    char* str;                                                          // 头指针
    unsigned int pos;                                                   // 已用内存位置
    unsigned int size;
};
#endif
