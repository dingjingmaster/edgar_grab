/*************************************************************************
> FileName: JIO.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 11时25分49秒
 ************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "JFlag.h"
#include "JIO.h"

int create_dir(const char* dirName) {
    if(access(dirName, 0) == -1) {
        if(mkdir(dirName, 0770)) {
            // 创建失败
            return J_ERR;
        }
    }

    return J_OK;
}

int write_all(int fd, const char* buf) {
    int pos = 0;
    int count = strlen(buf);
    int ret = write(fd, buf + pos, count - pos);
    if (ret < 0) {
        return J_ERR;
    }

    return J_OK;
}

int write_buff(int fd, const char* buf, int size) {
    int pos = 0;
    while(pos < size) {
        int i = write(fd, buf + pos, size - pos);
        if(-1 == i) {
            switch(errno) {
                case EINTR :
                    break;
                default:
                    pos = size + 1;
                    //
                    break;
            }
        } else {
            pos += i;
        }
    }
    return pos != size ? J_ERR : J_OK;
}
