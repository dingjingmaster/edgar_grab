/*************************************************************************
> FileName: JRequest.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 18时15分24秒
 ************************************************************************/

#ifndef _JREQUEST_H
#define _JREQUEST_H
class JRequest {
public:
    JRequest(string url);
    ~JRequest();

    JRequest& run();

protected:
    virtual void parseUrl();
private:

private:
    string                              resHead;                        // 返回的头信息
    string                              resHtml;                        // 返回的html
    list<string>                        urlList;                        // 解析获取的url列表
    map<string, string>                 reqHead;                        // 请求头
};
#endif
