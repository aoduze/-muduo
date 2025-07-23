//
// Created by admin on 2025/7/21.
//

#ifndef TIMER_H
#define TIMER_H

#include "noncopyable.h"
#include "Re_muduo/base/Timestamp.h"
#include <functional>

//Timer用于描述一个定时器
class Timer : noncopyable {
public:
    using TimerCallback = std::function<void()>;

    Timer(TimerCallback cb, Timestamp when, double interval) :
        callback_(std::move(cb)),
        expiration_(when),
        interval_(interval),
        repeat_(interval > 0.0 )
        { }

    void run() const {
        callback_();
    }

    Timestamp expiration() const { return expiration_; }
    bool repeat() const { return repeat_; }

    //重启定时器
    void restart(Timestamp now);
private:
    const TimerCallback callback_;    //回调函数
    Timestamp expiration_;            //下一次超时时刻
    const double interval_;           //超时的时间间隔
    const bool repeat_;               //是否一次性
};



#endif //TIMER_H
