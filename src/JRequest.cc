/*************************************************************************
> FileName: JRequest.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 09时47分11秒
 ************************************************************************/
#include <stdio.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "JRequest.h"
#include "curl/curl.h"
#include "htmlcxx/html/ParserDom.h"

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData);

using namespace std;
using namespace htmlcxx;

JRequest::JRequest() {
    seriesNum = 0;
    exited = false;
    canExit = false;
    resHtml = new string;
    priUrl = new queue<string>;
    secUrl = new queue<string>;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curlHandle = curl_easy_init();
    if(NULL == curlHandle) {
        cout << "curl 初始化失败" << endl;
    }
    if(tempDir.empty()) {
        tempDir = "./temp/";
    }
    toSchFIFO = tempDir + "/" + "req_sche";
    if(J_OK != create_dir(tempDir.c_str())) {
        // 创建失败
    }
    if(J_OK != create_fifo(toSchFIFO.c_str())) {
        // 创建失败
    }
    if(toSchedule = open(toSchFIFO.c_str(), O_WRONLY, 0) < 0) {
        // 打开失败
    }
}

JRequest::~JRequest() {
    delete[] resHtml;
    delete[] priUrl;
    delete[] secUrl;
    curl_easy_cleanup(curlHandle);
}

void JRequest::addUrl(string url, bool priority) {

    urlLock.lock();
    if(priority) {
        priUrl ->push(url);
    } else {
        secUrl ->push(url);
    }
    urlLock.unlock();
}

void JRequest::setHead(string key, string value) {

}

void JRequest::saveFile() {
    if(resHtml ->length() > 0) {
        char                    buf[100] = {0};
        snprintf(buf, 100, "%08u", seriesNum);
        string path = tempDir + "/" + string(buf) + ".html";
        string pathPair = url + "{]" + path + "\n";
        int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if(fd > 0) {
            int tim = 5;
            int ret = J_ERR;
            do {
                ret = write_all(fd, this ->resHtml ->c_str());
                -- tim;
            } while (ret != J_OK || tim < 0);
            ++ seriesNum;
            this ->resHtml ->clear();
            close(fd);
            write_all(toSchedule, pathPair.c_str());              // 写管道
        } else {
            cout << "打开失败" << endl;
        }
    }
}

void JRequest::run() {

    CURLcode                    code;

    // 设置读取html
    code = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_req_cb);
    if(CURLE_OK != code) {
        cout << "cb失败" << endl;
    }

    // 获取网页信息 并保存
    requestLoop();
    // 设置头
    /*
    code = curl_easy_setopt(handle, CURLOPT_URL, this ->url.c_str());
    if(CURLE_OK) {
        //
        //return NULL;
    }
    */

}

void urlNorm(string& str) {

    int             i = 0;
    int             strLen = str.length();
    const char*     pH = str.c_str();
    char            buf[1024] = {0};

    while(strLen - i > 7) {
        if(0 == strncmp(pH + i, "www", 3)) {
            strncpy(buf, pH + i, strlen(pH + i));
            break;
        } else if(0 == strncmp(pH + i, "http://", 7)) {
            strncpy(buf, pH + i + 7, strlen(pH));
            break;
        } 
        ++ i;
    }
    str.clear();
    str.append(buf);
}

void JRequest::parseUrl() {
    HTML::ParserDom         parser;
    tree<HTML::Node> dom = parser.parseTree(*(this ->resHtml));
    for(tree<HTML::Node>::iterator it = dom.begin(); it != dom.end(); ++ it) {
        if(!it ->isTag()) {
            continue;
        }
        if(it ->tagName().compare("a") == 0) {
            it ->parseAttributes();
            if(it ->attribute("href").first) {
                string murl = it -> attribute("href").second;
                urlNorm(murl);
                addUrl(murl, false);
            }
        }
    }
}

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData) {
    if(writerData == NULL) {
        return 0;
    }
    writerData ->append(data, size * nmemb);

    return size * nmemb;
}

void JRequest::requestLoop() {
    CURLcode                    code;
    while(true) {
        if(this ->canExit) {
            break;
        }
        // 设置url 优先爬取 最好做成条件变量
        do {
            if(!priUrl ->empty()){
                urlLock.lock();
                url = priUrl ->front();
                priUrl ->pop();
                urlLock.unlock();
            } else if(! secUrl ->empty()) {
                urlLock.lock();
                url = secUrl ->front();
                secUrl ->pop();
                urlLock.unlock();
            }
        } while(url.empty());

        code = curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        if(CURLE_OK != code) {
            cout << "url失败" << endl;
        }

        code = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this ->resHtml);
        if(CURLE_OK != code) {
            cout << "resHtml失败" << endl;
        }

        code = curl_easy_perform(curlHandle);
        if(CURLE_OK != code) {
            cout << "下载html失败" << endl;
        }
        parseUrl();                                                     // 获取链接
        saveFile();                                                     // 放到本地
        url.clear();                                                    // 完成请求后清空url
    }

    exited = true;
}










