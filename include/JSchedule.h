/*************************************************************************
> FileName: JSchedule.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 16时54分19秒
 ************************************************************************/

#ifndef _JSCHEDULE_H
#define _JSCHEDULE_H
/**
 * 调度器 定爬
 */
// 以下全局变量需要改为配置文件
int         EDGAR_FDS                       200;
int         EDGAR_FILTER                    1024000;
int         EDGAR_RETRY                     5;
int         EDGAR_INTERVAL                  300;                        // ms
int         EDGAR_THREAD                    300;                        // 线程数
char[]      EDGAR_THREAD                    "";                         // 开始采集url

#define     MAX_THREAD                      500;                        // 最大线程数设置

class JSchedule {
public:
    JSchedule();
    ~JSchedule();
    void run();                                                         // 程序入口

protected:
    virtual void request();                                             // 请求
    virtual void download();                                            // 下载器
    virtual void parse();                                               // 解析
    virtual void outfile();                                             // 输出到文件
    virtual void routine();                                             // 每个线程都执行的

private:
    int getFd();                                                        // 重新打开文件
    void putUrlFilter(string& url);                                     // url放入过滤器中
    void putUrlQue(string& url, bool isPri);                            // url放入待采集队列中

private:
    int*                                        fds;                    // 一次性打开fd的数量, 线程安全

    string                                      baseUrl;                // 基础host, 不许更改
    unsigned long                               count;                  // 计数器, 线程安全
    set<string>*                                filter;                 // url过滤, 线程安全
    queue<pair<string, int>>*                   priorUrl;               // 优先队列 url 和 文件描述符, 必须线程安全
    queue<string>*                              secUrl;                 // 低优先级 url, 高优先级没有且文件描述符有空闲才执行

    mutex                                       fdMut;                  // 文件描述符锁
    mutex                                       filtMut;                // 过滤器锁

    unique_lock                                 priUrlLock;             // 优先队列锁
    condition_variable                          priUrlCond;             // 优先队列条件变量

    // 下载器 -- 页面下载器
    // 下载器 -- 文件/图片下载器
    // 解析器
    // 文件输出
    // 持久化输出 -- 数据库 
};
#endif
