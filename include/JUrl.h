/*************************************************************************
> FileName: JUrl.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月31日 星期三 15时45分14秒
 ************************************************************************/

#ifndef _JURL_H
#define _JURL_H
class JUrl {
public:
    JUrl(char* line, int depth);
    JUrl(char* line);
    ~JUrl();
    bool isValid();
    void print();
    char* getHost();
    unsigned int port getPort();
    char* getFile();
    int getDepth();
    JUrl& giveBase();
    char* giveUrl();
    unsigned int hostHashCode();
    unsigned int urlHashCode();



private:
    char*                       host;
    char*                       file;
    int                         depth;
    unsigned int                port;

    void parseUrl(char* s);
    void parseWithBase(char* u, url* base);
    void normalizeFile(char* file);
    void isProtocol(char* s);
    JUrl(char* host, unsigned int port, char* file);

}
#endif
