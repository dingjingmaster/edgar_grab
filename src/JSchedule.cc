/*************************************************************************
> FileName: JSchedule.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 17时39分59秒
 ************************************************************************/
#include <JIO.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "JSchedule.h"
/*

void insert_urlpair(string& url);

JSchedule::JSchedule() {

    startUrl = "http://blog.sina.com.cn/";

    hadUrlNum = 0;
    canExit = false;
    urlPair = new map<string, string>;                                  // 网络 url 与本地路径

    //
    //reqSchFifo = string("./temp/") + "req_sche";
    if(J_OK != create_fifo("./fifo")) {
        // 创建失败
        cout << "fifo创建失败" << endl;
    }
}

JSchedule::~JSchedule() {
    delete[] urlPair;
    delete[] request;
}

void JSchedule::getUrlPair() {
    char        urlPairTmp[4096] = {0};
    while(true){
        if(canExit) {
            break;
        }
        // 读取已经抓取的url
        memset(urlPairTmp, 0, 4096);
        read_line(pairFIFO, urlPairTmp);
        // 加入到已经抓取列表
        //insert_urlpair(urlPairTmp);
        cout << "已抓取: " << urlPairTmp << endl;
    }
} 


void JSchedule::run() {

    // 创建进程
    pid_t       pid;

    pid = fork();
    if(0 == pid) {                                      // 主进程
        cout << "主进程" << endl;
        schedule_init();


    } else if (pid > 0) {                               // 请求
        cout << "请求进程" << endl;
        request_init();
        request ->run();

    } else {
        cout << "fork错误" <<endl;
    }


}

void JSchedule::request_init() {
    // 网页下载器初始化
    request = new JRequest();
    request ->addUrl(startUrl, false);
}

void JSchedule::schedule_init() {

    //if((pairFIFO = open(reqSchFifo.c_str(), O_RDONLY)) < 0) {
    if((pairFIFO = open("./fifo", O_RDONLY)) < 0) {
        // 打开失败
        cout << "fifo打开失败" << endl;
    }

    getUrlPair();
}
*/

