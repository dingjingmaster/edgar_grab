/*************************************************************************
> FileName: strings_test.cpp
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2018年01月30日 星期二 17时51分57秒
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include "JString.h"
int main() {
    char* a = "0123456789";
    EdgarString tes1;
    EdgarString tes4(a);

    puts(tes4.copyString());
    printf("%c\n", tes4[8]);
    printf("%d\n", tes4.len());
    tes4[2] = 'd';
    tes4.setChar(1, 'a');
    tes4.addChar('x');
    tes4.addString("yyyy");
    printf("%c\n", tes4[8]);
    puts(tes4.copyString());
}
