/*************************************************************************
> FileName: JRequest.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 18时15分24秒
 ************************************************************************/

#ifndef _JREQUEST_H
#define _JREQUEST_H
#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <list>
#include <map>
#include "JIO.h"
#include "JFlag.h"
#include "curl/curl.h"

using namespace std;

class JRequest {
public:
    JRequest();
    ~JRequest();
    void setHead(string key, string value);
    void addUrl(string url, bool priority);
    void run();

protected:
    //virtual void parseUrl();
    virtual void requestLoop();

private:
    void saveFile();
    void setUrl(string url);

private:
    CURL*                               curlHandle;                     // curl handle

    int                                 toSchedule;                     // 管道
    string                              toSchFIFO;                      // 管道

    unsigned int                        seriesNum;                      // 编号
    string                              tempDir;                        // 临时文件存储

    bool                                canExit;                        // 是否可以退出
    bool                                exited;                         // 是否已经退出

    string                              url;                            // 正在使用的url
    queue<string>*                      priUrl;                         // 优先队列
    queue<string>*                      secUrl;                         // 第二优先队列
    mutex                               urlLock;                        // url队列锁

    string*                             resHtml;                        // 返回的html
    map<string, string>                 reqHead;                        // 设置请求头
};
#endif
