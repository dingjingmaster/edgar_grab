/*************************************************************************
> FileName: JRequest.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 09时47分11秒
 ************************************************************************/
#include <stdio.h>
#include <cstring>
#include "JRequest.h"
#include "htmlcxx/html/ParserDom.h"
#include "curl/curl.h"

using namespace std;
using namespace htmlcxx;

static int write_req_cb(char* data, size_t size, size_t nmemb, string* writerData) {
    if(writerData == NULL) {
        return 0;
    }
    writerData ->append(data, size * nmemb);

    return size * nmemb;
}

JRequest::JRequest(string url) {
    this ->url = url;
}

void JRequest::setHead(string key, string value) {
}

string& JRequest::getHtml() {
    return resHtml;
}

void JRequest::run() {

    CURL*                       handle;
    CURLcode                    code;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    handle = curl_easy_init();
    if(NULL == handle) {
        //error
        //return NULL;
    }
    
    // 设置url
    code = curl_easy_setopt(handle, CURLOPT_URL, this ->url.c_str());
    if(CURLE_OK != code) {
    cout << "url失败" << endl;
        //
        //return NULL;
    }

    // 设置头
    /*
    code = curl_easy_setopt(handle, CURLOPT_URL, this ->url.c_str());
    if(CURLE_OK) {
        //
        //return NULL;
    }
    */

    // 设置读取html
    code = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_req_cb);
    if(CURLE_OK != code) {
        //
    cout << "cb失败" << endl;
        //return NULL;
    }

    code = curl_easy_setopt(handle, CURLOPT_WRITEDATA, this ->resHtml);
    if(CURLE_OK != code) {
    cout << "resHtml失败" << endl;
        //
        //return NULL;
    }

    code = curl_easy_perform(handle);
    curl_easy_cleanup(handle);

    // 获取链接
    parseUrl();
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
    tree<HTML::Node> dom = parser.parseTree(this ->resHtml);
    for(tree<HTML::Node>::iterator it = dom.begin(); it != dom.end(); ++ it) {
        if(!it ->isTag()) {
            continue;
        }
        if(it ->tagName().compare("a") == 0) {
            it ->parseAttributes();
            if(it ->attribute("href").first) {
                string url = it -> attribute("href").second;
                urlNorm(url);
                urlList.push_back(url);
            }
        }
    }
}

JRequest::~JRequest() {
}

