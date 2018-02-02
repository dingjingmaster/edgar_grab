/*************************************************************************
> FileName: JSchedule.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 17时39分59秒
 ************************************************************************/
#include "JSchedule.h"

JSchedule::JSchedule() {
    if(fdNum > 500 || fdNum <= 0) {
        fdNum = 500;
    }

    /*
    fds = new int[fdNum];                                               // 创建文件描述符数量
    filter = new set<string>;                                           // url 过滤器
    priorUrl = new queue<pair<string, int>>;                            // 高优先队列
    secUrl = new queue<string>;                                         // 低优先队列
    */
}

JSchedule::~JSchedule() {
    /*
    for(int i = 0; i < fdNum; ++i) {                                    // 释放文件描述符
        close(fds[i]);
    }
    delete[] fds;                                                       // 文件描述符
    delete[] filter;                                                    // url过滤器
    delete[] priorUrl;                                                  // 高优先队列
    delete[] secUrl;                                                    // 低优先队列
    */
}







