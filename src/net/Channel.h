//
// Created by admin on 2025/7/21.
//

#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <memory>
#include <sys/epoll.h>

#include "noncopyable.h"
#include "Timestamp.h"
#include "Logging.h"

// 前置声明，不引用头文件防止暴露太多信息
class EventLoop;
class Timestamp;

class Channel : noncopyable {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    //fd得到poller通知后就会处理
    void handleEvent(Timestamp receiveTime);

    //设置回调函数
    //使用右值引用,延长生命周期
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    void tie(const std::shared_ptr<void>&);

    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt) {revents_ = revt; }  //设置Poller返回的发生事件

    //返回当前事件状态
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    bool isReadEvent() const { return events_ == kReadEvent; }
    bool isWriteEvent() const { return events_ == kWriteEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    // one lool per thread
    EventLoop* ownerLoop() { return loop_; }
    void remove();

private:
    void update();
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;    //EventLoop
    const int fd_;       //监听fd
    int events_;         //注册事件
    int revents_;        //返回的具体发生的事件
    int index_;          //在Poller上注册的情况

    std::weak_ptr<EventLoop> tie_;
    bool tied_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};



#endif //CHANNEL_H
