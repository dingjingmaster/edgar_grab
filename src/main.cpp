/*************************************************************************
> FileName: main.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月07日 星期三 10时26分30秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "JRequest.h"

int main(int argc, char* argv[]) {

    JRequest        jreq;
    jreq.addUrl("http://blog.csdn.net/s1234567_89/article/details/50723353", true);
    jreq.run();


}



