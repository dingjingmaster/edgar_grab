/*************************************************************************
> FileName: JSchedule.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 16时54分19秒
 ************************************************************************/
#ifndef _JSCHEDULE_H
#define _JSCHEDULE_H
#include <map>
#include <list>
#include <mutex>
#include <queue>
#include <thread>
#include <string>
#include <iostream>
#include <condition_variable>
#include "JRequest.h"

using namespace std;

class JSchedule {
public:
    JSchedule();
    ~JSchedule();
    void run();
    void setStartUrl(string url);

protected:
    virtual void request_init();

private:
    string                                  startUrl;
    JRequest*                               request;
};

/*
#include "JRequest.h"

using namespace std;

#define     MAX_THREAD                      500;                        // 最大线程数设置

class JSchedule {
public:
    JSchedule();
    ~JSchedule();
    void run();                                                         // 程序入口

protected:
    virtual void request_init();                                        // request参数初始化
    virtual void schedule_init();                                       // schedule参数初始化

private:
    JRequest*                               request;
    void getUrlPair();                                                    // 获取已经抓取到的链接

    //void putUrlFilter(string& url);                                     // url放入过滤器中
    //void putUrlQue(string& url, bool isPri);                            // url放入待采集队列中
*/
    /*  控制函数  */
   // string& distribute_url();                                           // 分发任务

/*
private:

    bool                                        canExit;                // 是否准备退出
    string                                      startUrl;               // 开始采集url

    int                                         pairFIFO;               //
    string                                      reqSchFifo;             // req sch 管道

    mutex                                       filtMut;                // 过滤器锁

    mutex                                       pairMut;                // 锁
    unsigned int                                hadUrlNum;              // 已抓url数量
    map<string, string>*                        urlPair;                // 本地与网络链表对应






    ////////////

    unsigned int                                fdNum;                  // 一次性打开的fd数量最多不超过500
    unsigned int                                filterNum;              // 过滤器大小
    unsigned int                                retryNum;               // 重试次数
    unsigned int                                interval;               // 请求间隔时间
    unsigned int                                threadNum;              // 线程数




    string                                      baseUrl;                // 基础host, 不许更改
    unsigned long                               count;                  // 计数器, 线程安全
    queue<pair<string, int>>*                   priorUrl;               // 优先队列 url 和 文件描述符, 必须线程安全
    queue<string>*                              secUrl;                 // 低优先级 url, 高优先级没有且文件描述符有空闲才执行

    mutex                                       fdMut;                  // 文件描述符锁

    unique_lock<mutex>                          priUrlLock;             // 优先队列锁
    condition_variable                          priUrlCond;             // 优先队列条件变量



    // 下载器 -- 页面下载器
    // 下载器 -- 文件/图片下载器
    // 解析器
    // 文件输出
    // 持久化输出 -- 数据库 
};
*/
#endif
