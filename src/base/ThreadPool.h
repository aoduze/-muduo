//
// Created by admin on 2025/7/20.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "noncopyable.h"
#include "Thread.h"
#include "Logging.h"

#include <deque>
#include <vector>
#include <mutex>
#include <condition_variable>

class ThreadPool : noncopyable {
public:
    using ThreadFunction = std::function<void()>;

    explicit ThreadPool(const std::string& name = std::string("ThreadPool"));
    ~ThreadPool();

    void setThreadInitCallback(const ThreadFunction& cb) { threadInitCallback_ = cb; }
    void setThreadSize(const int& num) { threadSize_ = num; }
    void start();
    void stop();

    const std::string& name() cosnt { return name_; }
	void setMaxQueueSize(size_t maxSize) { maxQueueSize_ = maxSize; }
    size_t queueSize() const { return queue_.size(); }

    void add(ThreadFunction ThreadFunction);

private:
    bool isFull() const;
    void runInThread();

    bool    running_;                     //是否执行中
    std::string name_;                    //名字
	size_t maxQueueSize_;				  //最大队列长度
    size_t threadSize_;                   //大小
    mutable std::mutex mutex_;            //互斥量
    std::condition_variable condition_;   //信号量
    ThreadFunction threadInitCallback_;   //回调函数
    std::deque<ThreadFunction> queue_;    //回调函数队列
    std::vector<std::unique_ptr<Thread>> threads_;
};



#endif //THREADPOOL_H
