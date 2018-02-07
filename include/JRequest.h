/*************************************************************************
> FileName: JRequest.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 18时15分24秒
 ************************************************************************/

#ifndef _JREQUEST_H
#define _JREQUEST_H
#include <set>
#include <queue>
#include <mutex>
#include <string>
#include <stdio.h>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "curl/curl.h"
#include "htmlcxx/html/ParserDom.h"

using namespace std;

class JRequest {
public:
    JRequest();
    ~JRequest();
    void setHead(string key, string value);
    void addUrl(string url, bool priority);
    void run();

protected:
    virtual void parseUrl();
    virtual void requestLoop();

private:
    void saveFile();
    void setUrl(string url);

private:
    CURL*                               curlHandle;                     // curl handle
    unsigned int                        getUrlNum;                      // 获取到的url数量

    bool                                canExit;                        // 是否可以退出
    bool                                exited;                         // 是否已经退出

    unsigned int                        seriesNum;                      // 编号
    string                              tempDir;                        // 临时文件存储

    string                              url;                            // 正在使用的url

    string*                             resHtml;                        // 返回的html
    map<string, string>                 reqHead;                        // 设置请求头
    set<string>*                        filter;                         // 过滤器


    queue<string>*                      priUrl;                         // 优先队列
    queue<string>*                      secUrl;                         // 第二优先队列
    mutex                               urlLock;                        // 队列锁

    map<string, string>*                urlPair;                        // 请求

    friend class JSchedule;
};
#endif
