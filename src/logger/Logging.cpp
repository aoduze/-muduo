//
// Created by admin on 2025/7/23.
//

#include "Logging.h"
#include "CurrentThread.h"

namespace ThreadInfo {
    //thread_local保证线程之间不互相干扰数据
    thread_local char t_errnobuf[512];
    thread_local char t_time[64];
    thread_local time_t t_lastSecond;
};

const char* getErrnoMsg(int savedErrno) {
    return strerror_r(savedErrno, ThreadInfo::t_errnobuf, sizeof(ThreadInfo::t_errnobuf));
}

const char* getLevelName[Logger::LogLevel::LEVEL_COUNT] {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
};

