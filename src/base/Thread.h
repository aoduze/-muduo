//
// Created by admin on 2025/7/20.
//

#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <atomic>
#include "noncopyable.h"

class Thread {
public:
    using ThreadFunc = std::function<void()>;
    explicit Thread(ThreadFunc,const std::string &name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_;}
private:
    void setDefaultName();

    boool started_;    //线程是否启动
    pid_t tid_;        //线程pid
    bool joined_;      //是否等待
    ThreadFunc func_;  //回调函数
    std::string name_; //线程名
    static std::atomic_int32_t numCreated_; //线程索引
};

#endif //THREAD_H
