//
// Created by 24172 on 2025/7/19.
//

#include "Timestamp.h"

Timestamp Timestamp::now() {
    struct timeval tv;
    //获取微秒和秒
    //此处不会有性能损失
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    //转换为微妙
    return Timestamp(seconds * KMicroSecondsPerSecond + tv.tv_usec);
}

std::string Timestamp::toString() const {
    char buf[32] = {0};
    int64_t seconds = ( microSecondsSinceEpoch_ / kMicroSecondsPerSecond );
    int64_t microseconds = ( microSecondsSinceEpoch_ % kMicroSecondsPerSecond );
    // 如果不方便包含，也可以用long long的格式化字符%lld
    snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    return buf;
}

std::string Timestamp::toFormattedString(bool showMicroseconds) const {
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / KMicroSecondsPerSecond);
    // 使用Localtime函数将秒数格式格式化成日历时间
    tm *tm_time = localtime(&seconds);
    if (showMicroseconds) {
        int microseconds = static_cast<int>(microSecondsSinceEpoch_ % KMicroSecondsPerSecond);
        snprintf(buf,sizeof(buf),"%4d/%02d/%02d %02d:%02d:%02d.%06d",
                 tm_time->tm_year + 1900,
                 tm_time->tm_mon + 1,
                 tm_time->tm_mday,
                 tm_time->tm_hour,
                 tm_time->tm_min,
                 tm_time->tm_sec,
                 microseconds);
    }
    else {
        snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
                tm_time->tm_year + 1900,
                tm_time->tm_mon + 1,
                tm_time->tm_mday,
                tm_time->tm_hour,
                tm_time->tm_min,
                tm_time->tm_sec);
    }
    return buf;
}