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

int write_all(int fd, char* buf);
int write_buff(int fd, char* buf, int size);



#ifdef __cplusplus
}
#endif
#endif
