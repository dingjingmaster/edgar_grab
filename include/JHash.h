/*************************************************************************
> FileName: ../include/JHash.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 10时50分45秒
 ************************************************************************/

#ifndef _JHASH_H
#define _JHASH_H
class JHash {
public:
    JHash(unsigned int size, char* initFile, bool scratch);
    ~JHash();

    bool addDoc(char* doc);
    void save();

private:
    unsigned int        size;
    char*               table;
    char*               file;

};
#endif
