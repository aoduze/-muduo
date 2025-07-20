//
// Created by admin on 2025/7/20.
//

#ifndef CURRENTTHREAD_H
#define CURRENTTHREAD_H

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread {
    extern __thread int t_cachedTid;
    //保存tid缓冲

    inline int tid() {
        if(__builtin_expect(t_cachedTid == 0, 0)) {
            cacheTid();
        }
        return t_cachedTid;
    }
}

#endif //CURRENTTHREAD_H
