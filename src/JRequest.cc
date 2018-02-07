/*************************************************************************
> FileName: JRequest.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 09时47分11秒
 ************************************************************************/
#include "JRequest.h"
#include "JIO.h"
#include "JFlag.h"

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData);
static void save_html(string& html);
static void routine();

using namespace std;
using namespace htmlcxx;

JRequest::JRequest() {
    seriesNum = 0;
    exited = false;
    canExit = false;
    filter = new set<string>;
    curl_global_init(CURL_GLOBAL_DEFAULT);                              // 初始化curl
    curlHandle = curl_easy_init();
    if(NULL == curlHandle) {
        cout << "curl 初始化失败" << endl;
    }
    if(tempDir.empty()) {
        tempDir = "./temp/";
    }
}

JRequest::~JRequest() {

    delete[] filter;
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
void JRequest::run() {


    requestLoop();
}



static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData) {
    if(writerData == NULL) {
        return 0;
    }
    writerData ->append(data, size * nmemb);                            // 读取html
    return size * nmemb;
}

static void save_html(string& html) {

    if(html ->length() > 0) {
        char                    buf[100] = {0};
        snprintf(buf, 100, "%08u", seriesNum);
        string path = tempDir + "/" + string(buf) + ".html";
        int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if(fd > 0) {
            int tim = 5;
            int ret = J_ERR;
            do {
                ret = write_all(fd, html ->c_str());
                -- tim;
            } while (ret != J_OK || tim < 0);
            seriesLock.lock();
            ++ seriesNum;
            seriesLock.unlock();
            close(fd);
            html ->clear();
        } else {
            cout << "打开失败" << endl;
        }
    }
}

void routine() {
    CURL*                               curlHandle;                     // curl handle
    CURLcode                            code;
    string                              url;                            // 当前正在下载的url
    set<string>::iterator               it;

    code = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_req_cb);
    if(CURLE_OK != code) {
        cout << "cb失败" << endl;
    }


    while(true) {                                                       // 一直下载页面
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

            // 检测是否已爬取
            it = filter->find(url);
            if(it != filter->end()) {
        //        url.clear();
            }
        } while(url.empty());

        cout << "请求的url: " + url << endl;

        code = curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        if(CURLE_OK != code) {
            cout << "url失败" << endl;
        }
        filter->insert(url);

        code = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this ->resHtml);
        if(CURLE_OK != code) {
            cout << "resHtml失败" << endl;
        }

        code = curl_easy_perform(curlHandle);
        if(CURLE_OK != code) {
            cout << "下载html失败" << endl;
        }
        cout << *resHtml << endl;

        parseUrl();                                                     // 获取链接
        saveFile();                                                     // 放到本地
        url.clear();                                                    // 完成请求后清空url
    }

    exited = true;



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
void JRequest::requestLoop() {
    CURLcode                    code;

    set<string>::iterator       it;
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

            // 检测是否已爬取
            it = filter->find(url);
            if(it != filter->end()) {
        //        url.clear();
            }
        } while(url.empty());

        cout << "请求的url: " + url << endl;

        code = curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        if(CURLE_OK != code) {
            cout << "url失败" << endl;
        }
        filter->insert(url);

        code = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this ->resHtml);
        if(CURLE_OK != code) {
            cout << "resHtml失败" << endl;
        }

        code = curl_easy_perform(curlHandle);
        if(CURLE_OK != code) {
            cout << "下载html失败" << endl;
        }
        cout << *resHtml << endl;

        parseUrl();                                                     // 获取链接
        saveFile();                                                     // 放到本地
        url.clear();                                                    // 完成请求后清空url
    }

    exited = true;
}







