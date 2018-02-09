/*************************************************************************
> FileName: JRequest.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 09时47分11秒
 ************************************************************************/
#include "JIO.h"
#include "JLog.h"
#include "JFlag.h"
#include "JRequest.h"

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData);

using namespace std;
using namespace htmlcxx;

JRequest::JRequest() {
    seriesNum = 0;
    exited = false;
    canExit = false;
    filter = new set<string>;
    priUrl = new queue<string>;
    secUrl = new queue<string>;
    urlPair = new map<string, string>;
    if(tempDir.empty()) {
        tempDir = ".temp/";
        create_dir(tempDir.c_str());
    }

    DEBUG("JRequest 初始化成功...");
}

JRequest::~JRequest() {

    delete[] filter;
    delete[] priUrl;
    delete[] secUrl;
    delete[] urlPair;
    DEBUG("JRequest 析构成功...");
}

void JRequest::addUrl(string url, bool priority) {

    urlLock.lock();
    if(priority) {
        priUrl ->push(url);
    } else {
        secUrl ->push(url);
    }
    DEBUG("JRequest 添加一条url...");
    urlLock.unlock();
}
void JRequest::run() {

    //requestLoop();析构成功
    routine();
}
void JRequest::routine() {
    CURL*                               curlHandle;                     // curl handle
    CURLcode                            code;
    string                              url;                            // 当前正在下载的url
    string                              resHtml;
    set<string>::iterator               it;

    curl_global_init(CURL_GLOBAL_DEFAULT);                              // 初始化curl
    curlHandle = curl_easy_init();
    if(NULL == curlHandle) {
        ERROR("curl 初始化失败...");
    }
    code = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_req_cb);
    if(CURLE_OK != code) {
        ERROR("curl 设置接收回调函数失败...");
    }
    while(true) {                                                       // 一直下载页面
        if(canExit) {
            break;
        }
        do {                                                            // 检测是否已爬取
            url = getUrl();                                             // 设置url 优先爬取 最好做成条件变量
            it = filter->find(url);
            if(it != filter->end()) {
                url.clear();
            }
        } while(url.empty());

        code = curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        if(CURLE_OK != code) {
            ERROR("curl 设置url失败...");
        }
        filter->insert(url);

        code = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &resHtml);
        if(CURLE_OK != code) {
            ERROR("curl 接收html失败...");
        }

        code = curl_easy_perform(curlHandle);
        if(CURLE_OK != code) {
            ERROR("curl 下载html失败...");
        }

        parseUrl(resHtml);                                                     // 获取链接
        saveHtml(url, resHtml);                                                     // 放到本地
        resHtml.clear();
        url.clear();                                                    // 完成请求后清空url
    }
    curl_easy_cleanup(curlHandle);
    exited = true;
}

string JRequest::getUrl() {

    string url = "";
    
    urlLock.lock();
    if(!priUrl ->empty()){
        url = priUrl ->front();
        priUrl ->pop();
    } else if(!secUrl ->empty()) {
        url = secUrl ->front();
        secUrl ->pop();
    }
    urlLock.unlock();

    return url;
}

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData) {
    if(writerData == NULL) {
        return 0;
    }
    writerData ->append(data, size * nmemb);                            // 读取html
    return size * nmemb;
}


void JRequest::saveHtml(string& url, string& html) {

    if(html.length() > 0) {
        char                    buf[100] = {0};
        seriesLock.lock();
        snprintf(buf, 100, "%08u", seriesNum ++);
        seriesLock.unlock();
        string path = tempDir + "/" + string(buf) + ".html";
        int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if(fd > 0) {
            int tim = 5;
            int ret = J_ERR;
            do {
                ret = write_all(fd, html.c_str());
                -- tim;
            } while (ret != J_OK || tim < 0);
            close(fd);
        } else {
            ERROR("JRequest 打开文件失败...");
        }
        // 保存关系
        urlPairLock.lock();
        urlPair ->insert(make_pair(url, path));
        urlPairLock.unlock();
    }
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

void JRequest::parseUrl(string& html) {
    HTML::ParserDom         parser;
    tree<HTML::Node> dom = parser.parseTree(html);
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





