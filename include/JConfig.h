/*************************************************************************
> FileName: JConfig.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月07日 星期三 16时37分05秒
 ************************************************************************/

#ifndef _JCONFIG_H
#define _JCONFIG_H

class JConfig {
public:
    JConfig(string confPath); 
    ~JConfig(); 

private:
    string                      confPath;                               // 配置文件路径

private:
}

#endif
