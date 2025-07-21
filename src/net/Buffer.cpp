//
// Created by admin on 2025/7/21.
//
#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

#include "Buffer.h"
#include "Logging.h"

const char Buffer::kCRLF[] = "\r\n";

/**
 * 这里有一点需要注意，在fd环境下读取数据我们是有一层缓冲的
 * 我们知道缓冲区的大小,但fd内数据大小是不确定的的
 * 当我们向buffer中写数据时,muduo会启用一层类似栈的缓冲
 * 数据会先进入到栈中,随后才被压入buffer中,形成一层缓冲避免爆内存的情况产生
**/

ssize_t Buffer::readFd(int fd, int *saveErrno) {
    char extrabuf[65536] = {0}; //换算过来其实就是64KB

    /**
    struct iovec {
    ptr_t iov_base; // iov_base指向的缓冲区存放的是readv所接收的数据或是writev将要发送的数据
    size_t iov_len; // iov_len在各种情况下分别确定了接收的最大长度以及实际写入的长度
    };
    **/

    //使用结构体分配两个连续的缓冲区
    struct iovec vec[2];
    const size_t writable = writeableBytes();
    //但这里的buffer是底层缓冲区剩余的可写空间大小 不一定能完全存储下fd环境的数据

    //我们想将第一块缓冲区指向可写空间
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;
    //第二缓冲区,指向栈空间
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);

}
