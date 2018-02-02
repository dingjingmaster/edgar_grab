/*************************************************************************
> FileName: JIO.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 11时17分30秒
 ************************************************************************/

#ifndef _JIO_H
#define _JIO_H
#ifdef __cplusplus
extern "C" {
#endif

int create_dir(const char* dirname);
int write_all(int fd, const char* buf);
int write_buff(int fd, const char* buf, int size);



#ifdef __cplusplus
}
#endif
#endif
