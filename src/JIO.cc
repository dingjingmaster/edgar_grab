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
#include <fcntl.h>
#include "JFlag.h"
#include "JIO.h"
#include "JLog.h"

int read_line(int fd, char* line) {
    int         ret = 0;
    char        tmp = 0;

    while(read(fd, &tmp, 1) >= 0) {
        if(tmp == '\n') {
            break;
        }
        puts(&tmp);
        puts("|");
        puts("\n");
        //strcat(line, &tmp);
    }

    return J_OK;
}

int create_fifo(const char* filename) {
    if(mkfifo(filename, O_CREAT | O_EXCL) < 0) {
        return J_ERR;
    }

    return J_OK;
}

int create_dirs(const char* dirname) {
    if(NULL == dirname) {
        return J_ERR;
    }
    char                        dir[256] = {0};
    int                         hLen = 0;
    int                         eLen = 0;
    int                         len = strlen(dirname);

    while(eLen <= len) {
        if(*(dirname + eLen) == '/' || *(dirname + eLen) == '\\') {
            //while(*(dirname + eLen) == '/' || *(dirname + eLen) == '\\') {
            //}
            memset(dir, 0, 256);
            strncpy(dir, dirname + hLen, eLen - hLen);
            create_dir(dir);
            chdir(dir);
            puts("1");
            hLen = eLen;
            while(*(dirname + hLen) == '/' || *(dirname + hLen) == '\\') {
                ++hLen;
            }
            eLen = hLen;
        }
        ++ eLen; 
    }

    return J_OK;
}

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
