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
#include "JFlag.h"
#include "JIO.h"

int write_all(int fd, char* buf) {
    int pos = 0;
    int count = strlen(buf);
    while (pos < count) {
        int i = write(fd, buf + pos, count - pos);
        if (-1 == i) {
            if(EINTR != errno) {                                        // 信号中断,没写成功
                pos = count + 1;
            }
        } else {
            pos += 1;
        }
    }

    return pos != count ? J_ERR : J_OK;
}

int write_buff(int fd, char* buf, int size) {
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
