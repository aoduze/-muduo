//
// Created by admin on 2025/7/22.
//

#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include "FixedBuffer.h"
#include "noncopyable.h"

#include <string>

static const int kMaxNumbericSize = 48;

class GeneralTemplate : noncopyable {
public:
    GeneralTemplate()
      : data_(nullptr),
        len_(len)
        { }

    explicit GeneralTemplate(const char* data,int len)
      : data_(data),
        len_(len)
        { }

    const char* data_;
    int len_;
};

class LogStream : noncopyable {
public:
    //此处的Buffer使用了FixedBuffer类的封装,要注意这里的buffer大小是固定的
	using Buffer = FixedBuffer<kSmallBuffer>;

	void append(const char* data, int len) { buffer_.append(data, len); }
	const Buffer& buffer() const { return buffer_};
	void resetBuffer() { buffer_.reset(); }

	//重载运算符
	LogStream& operator<<(short);
	LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);

    LogStream& operator<<(float v);
    LogStream& operator<<(double v);

    LogStream& operator<<(char c);
    LogStream& operator<<(const void* data);
    LogStream& operator<<(const char* str);
    LogStream& operator<<(const unsigned char* str);
    LogStream& operator<<(const std::string& str);
    LogStream& operator<<(const Buffer& buf);

    // (const char*, int)的重载
    LogStream& operator<<(const GeneralTemplate& g);
private:
	//切记,我们对于整型要特殊处理
	template <typename T>
	void formatInteger(T);

	Buffer buffer_;
};



#endif //LOGSTREAM_H
