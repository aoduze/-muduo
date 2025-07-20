//
// Created by admin on 2025/7/20.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(const std::string& name) :
    name_(name),
    mutex_(),
    running_(false),
    cond_(),
    threadSize_(0) {}

void ThreadPool::~ThreadPool() {
    stop();
    for(const auto& thread : threads_) {
        thread.join();
        //轮询结束每一个线程
    }
}

void ThreadPool::start() {
    running_ = true;
    threads_.reserve(threadSize_);
    for(int i = 0; i < threadSize_; ++i) {
        char id[32];
        snprintf(id, sizeof(id), "%d", i+1);
        threads_.emplace_back(new Thread(
            std::bind(&ThreadPool::runInThread,this),name_ + id));
            threads_[i] -> start();
    }
    //不另起线程操作,如果当前线程是没有被创建出来的,那么这里的操作就理应是堵塞的
    if(threadSize_ == 0 && threadInitCallback_) {
        threadInitCallback_();
    }
}

void ThreadPool::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    running_ = false;
    cond_.notify_all();
}

void ThreadPool::queueSize() const {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.size();
}

void ThreadPool::add(ThreadFunction threadFunction) {
    std::unique_lock<std::mutex> lock(mutex_);
    queue_.emplace_back(threadFunction);
    cond_.notify_one();
}

void ThreadPool::runInThread() {
    try {
        if(threadInitCallback_) {}
    }
}

void ThreadPool::isFull() {

}


