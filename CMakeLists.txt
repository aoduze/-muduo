cmake_minimum_required(VERSION 3.31)
project(Re_muduo)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/base)
include_directories(src/logger)
include_directories(src/net)
include_directories(src/timer)

add_executable(Re_muduo
        .idea/.gitignore
        .idea/deployment.xml
        .idea/editor.xml
        .idea/material_theme_project_new.xml
        .idea/misc.xml
        .idea/modules.xml
        .idea/Re_muduo.iml
        .idea/vcs.xml
        .idea/workspace.xml
        src/base/CurrentThread.cpp
        src/base/CurrentThread.h
        src/base/noncopyable.h
        src/base/Thread.cpp
        src/base/Thread.h
        src/base/ThreadPool.cpp
        src/base/ThreadPool.h
        src/base/Timestamp.cpp
        src/base/Timestamp.h
        src/logger/FixedBuffer.h
        src/logger/Logging.cpp
        src/logger/Logging.h
        src/logger/LogStream.cpp
        src/logger/LogStream.h
        src/net/Buffer.cpp
        src/net/Buffer.h
        src/net/Channel.cpp
        src/net/Channel.h
        src/net/EventLoop.cpp
        src/net/EventLoop.h
        src/timer/Timer.cpp
        src/timer/Timer.h
        src/timer/TimerQueue.cpp
        src/timer/TimerQueue.h)
