//
// Created by admin on 2025/7/22.
//
//FixedBuffer是一个固定的buffer模板
//只有最基本的功能

#ifndef FIXEDBUFFER_H
#define FIXEDBUFFER_H

#include "noncopyable.h"
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <string>

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000* 1000;

template <int SIZE>
class FixedBuffer : noncopyable {
public:
    FixedBuffer() : cur_(data_) {}

    void append(const char* buf, size_t len) {
        if(static_cast<size_t>(avail()) > len) {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    const char* data() const { return data_; }
    int length() const {return static_cast<int>(end() - data_); }

    char* current() { return cur_; }
    int avail() const { return static_cast<int>(end() - cur_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { ::bzero(cur_, len()); }

    std::string toString() const { return std::string(data_, length()); }
private:
    const char* end() const { return data_ + sizeof(data_); }
    char data_[SIZE];
    char* cur_;
}

#endif //FIXEDBUFFER_H
