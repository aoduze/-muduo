//
// Created by admin on 2025/7/20.
//

#include <semaphore.h>
#include "Thread.h"
#include "CurrentThread.h"

std::atomic_int32_t THread::numCreated_(0);

Thread::Thread(ThreadFunc func,const std::string &name) :
    started_(false),
    joined_(false),
    tid_(0),
    func_(std::move(func)),
    name_(name)
{
    setDefaultName();
    //设置线程索引编号和姓名
}

Thread::~Thread() {
    if(started_ && joined_) {
        thread_ -> detach();
    }
}

void Thread::start() {
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();
        sem_post(&sem);
        func_();
    }));
    /**
    * 33行操作我们必须先拿到新线程的ID,信号量操作会帮我们处理并发情况
    */
    sem_wait(&sem);
}

void Thread::join() {
    joined_ = true;
    thread_ -> join();
    //这里唯一的要点是我们要等待线程执行完毕
}

vodi Thread::setDefaultName() {
    int num = ++numCreated_;
    if (name_.empty()) {
        char buf[32] = {0};
        snprintf(buf,sizeof(buf),"Thread%d",num);
        name_ = buf;
    }
}