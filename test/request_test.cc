/*************************************************************************
> FileName: request_test.cc
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月01日 星期四 13时20分19秒
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include "JRequest.h"
int main() {
    JRequest req("http://www.cnys.com/");
    req.run();
}
