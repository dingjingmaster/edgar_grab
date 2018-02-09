/*************************************************************************
> FileName: main.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年02月07日 星期三 10时26分30秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "JLog.h"
#include "JSchedule.h"
#include "JIO.h"

int main(int argc, char* argv[]) {

    JSchedule           schedule;

    log_init("./conf/log.conf");
    //schedule.setStartUrl("http://blog.csdn.net/s1234567_89/article/details/50723353");
    //schedule.run();
    create_dirs("./temp/ssss/ok//sss.txt");


    log_destory();


}



