/*************************************************************************
> FileName: JLog.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Wed 22 Nov 2017 06:59:34 PM DST
 ************************************************************************/

#ifndef _JLOG_H
#define _JLOG_H
#include "zlog.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FATAL(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_FATAL, __VA_ARGS__)
#define ERROR(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_ERROR, __VA_ARGS__)
#define WARN(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_WARN, __VA_ARGS__)
#define NOTICE(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_NOTICE, __VA_ARGS__)
#define INFO(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_INFO, __VA_ARGS__)
#define DEBUG(...) \
	dzlog(__FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
	ZLOG_LEVEL_DEBUG, __VA_ARGS__)

void log_init(const char* confPath);

void log_destory(void);


#ifdef __cplusplus
}
#endif
#endif
