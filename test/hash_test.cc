/*************************************************************************
> FileName: strings_test.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月30日 星期二 17时51分57秒
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include "JHash.h"
int main() {
    JHash jh(1024, "./hash.txt", true);
    jh.addDoc("adsdasdasdsadasdasdawasadas");
    jh.save();
}
