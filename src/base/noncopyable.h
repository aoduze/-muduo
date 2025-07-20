//
// Created by admin on 2025/7/20.
//

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class noncopyable {
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
    //禁止拷贝构造操作

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif //NONCOPYABLE_H
