//
// Created by admin on 2025/7/21.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>
#include <algorithm>

/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// muduo以两个指针巧妙地划分出头部区域,数据区与可写区

class Buffer {
public:
    static const size_t kCheapPrepend = 8;
    // muduo的buffer会在头部预留8字节空间,方便我们插入头部信息
    static const size_t kInitalSize = 1024;
    //初始化将空间设置为1024,muduo设置了自动扩充机制,稍后讲解

    //只有默认值时会使用1024
    explicit Buffer(size_t initialSize = kInitalSize) :
        buffer_(kCheapPrepend + initialSize),
        readerIndex_(kCheapPrepend),
        writerIndex_(kCheapPrepend)
        {}

    size_t readableBytes() const { return writeIndex_ - readerIndex_; }
    size_t writeableBytes() const { return buffer_.size() - writerIndex_; }
    size_t prependableBytes() const { return readerIndex_; }

    const char* peek() const { return begin() + readerIndex_; }
    void retrieveUntil(const char* end) { retrieve(end - peek()); }

    void retrieve(size_t len) {
        if(len < readableBytes()) {
            readerIndex_ += len;
        }else {
            retrieveAll();
        }
    }

    void retrieveAll() {
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    //得到当前buffer中的可读数据
    std::string GetBufferAllAsString() {
        size_t len = readableBytes();
        std::string result(peek(), len);
        return result;
    }

    std::string retrieveAllAsString() {
        return retrieveAsString(readableBytes());
    }

    std::string retrieveAsString(size_t len) {
        std::string result(peek(), len);
        retrieve(len);
        return result;
    }

    void ensureWritable(size_t len) {
        if(writeableBytes() < len) {
            makeSpace(len);
        }
    }

    //将数据写到缓冲区中
    void append(const char *data, size_t len) {
        ensureWriteableBytes(len);
        std::copy(data, data + len, beginWrite());
        writerIndex_ += len;
    }

    //检测\r\n换行,用于解析http等协议
    const char* findCRLF() const {
        const char* crlf = std::search(peek(), beginWrite(), kCRLF, KCRLF + 2);
        return crlf == beginWrite() ? nullptr : crlf;
    }

    char* beginWrite() {
        return begin() + writeIndex_;
    }

    //重载版本
    const char* beginWrite() const {
        return begin() + writeIndex_;
    }

    ssize_t readFd(int fd, int *saveErrno);
    ssize_t writeFd(int fd, int *saveErrno);
private:
    char* begin() {
        return buffer_.data();
    }

    const char* end() const {
        return buffer_.data();
    }

    void makeSpace(int len)
    {
        /**
         * kCheapPrepend | reader | writer |
         * kCheapPrepend |       len         |
         */
        // 整个buffer都不够用
        // 指数级扩容策略
        if (writableBytes() + prependableBytes() < len + kCheapPrepend) {
            size_t newSize = writerIndex_ + len;

            // 计算下一个合适的容量(至少是当前大小的1.5倍)
            size_t newCapacity = buffer_.size();
            while (newCapacity < newSize)
            newCapacity = newCapacity * 3 / 2;  // 扩大到1.5倍
            buffer_.resize(newCapacity);
            } else // 整个buffer够用，将后面移动到前面继续分配
            {
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_,
                    begin() + writerIndex_,
                    begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    /**
     * 采取vector形式,自动扩充内存
     * 当然,也可以提前预留空间大小
     */
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
    static const char kCRLF[];
};



#endif //BUFFER_H
