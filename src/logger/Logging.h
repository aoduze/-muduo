//
// Created by admin on 2025/7/23.
//

#ifndef LOGGING_H
#define LOGGING_H

#include "Timestamp.h"
#include "LogStream.h"

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string>
#include <functional>

//提取文件名
class SourceFile {
public:
    explicit SourceFile(const char* filename) : data_(filename) {
        const char* slash = strrchr(filename,'/');
        if(slash) { data_ = slash + 1;}
        size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
};

class Logger {
public:
    enum LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT,
    };

    //member function
    Logger(const char* file, int line);
    Logger(const char* file, int line, LogLevel level);
    Logger(const char* file, int line, LogLevel level,const char* func);
    ~Logger();

    //流的改变
    LogStream& stream() { return impl_.stream_; }

    static LogLevel LogLevel();
    static void setLogLevel(LogLevel level);

    using OutputFunc = std::function<void(const char*, int)>;
    using FlushFunc = std::function<void()>;
    static void setOutputFunc(OutputFunc);
    static void setFlush(FlushFunc);
private:
    class impl {
    public:
        using LogLevel = Logger::LogLevel;
        Impl(LogLevel level, int saveErrno, const char* file, int line);
        void formatTime();
        void finish();

        Timestamp time_;
        LogStream stream_;
        LogLevel level_;
        int line_;
        SourceFile basename_;
    }
    impl impl_;
};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel logLevel() {
    return g_logLevel;
}

const char* getErrnoMsg(int savedErrno);

// 当日志等级小于对应等级才会输出
// 比如设置等级为FATAL, 则LogLevel等级大于DEBUG和INFO, DEBUG和INFO等级的日志就不会输出

#define LOG_DEBUG if (logLevel() <= LOGER::DEBUG) \
    Logger(__FILE__, __LINE__, LOGGER::DEBUG, __func__).stream()
#define LOG_INFO if (logLevel() <= LOGGER::INFO) \
    Logger(__FILE__, __LINE__).stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).stream()
#endif //LOGGING_H
