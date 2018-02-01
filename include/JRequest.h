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
#include <list>
#include <map>
using std::string;
using std::list;
using std::map;
class JRequest {
public:
    JRequest(string url);
    ~JRequest();
    void setHead(string key, string value);
    string& getHtml();
    void run();

protected:
    virtual void parseUrl();

private:
    string                              url;                            // 要请求的url
    string                              uniqCode;                       // 唯一识别码
    string                              resHtml;                        // 返回的html
    list<string>                        urlList;                        // 解析获取的url列表
    map<string, string>                 reqHead;                        // 设置请求头
};
#endif
