//
// Created by admin on 2025/7/20.
//

#include "CurrentThread.h"

namespace CurrentThread {
    __thread int t_cachedTid = 0;

    void cacheTid()
    {
        if (t_cachedTid == 0)
        {
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
}