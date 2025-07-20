//
// Created by 24172 on 2025/7/19.
//

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>
#include <string>
#include <sys/time.h>
#include <cstdint>

class Timestamp {
public:
    Timestamp() : microSecondsSinceEpoch(0) {}
    explicit Timestamp(int64_t microSecondsSinceEpoch)
        : microSecondsSinceEpoch(microSecondsSinceEpoch) {}

    //获取当前时间戳
    static Timestamp now();

    std::string toString() const;
    std::string toFormattedString(bool showMicroseconds = false) const;

    //返回微秒
    int64_t microSecondsSinceEpoch() const {return microSecondsSinceEpoch_;}
    //返回秒数
    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
        //这里的取余操作是必做的,我们要准确获取秒数一定要这样操作
    }

    //返回一个值为0的Timestamp,用于失效处理
    static Timestamp invalid() {
        return Timestamp();
    }

    static const int KMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch_;
};

//我们重载运算符,定时器需要比较时间戳
inline bool operator<(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

//重复定时任务时,比如runevery和runafter,我们就增加时间戳
inline Timestamp addTime(Timestamp timestamp, double seconds) {
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

#endif //TIMESTAMP_H
