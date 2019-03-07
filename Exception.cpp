#include "Exception.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace HLib
{


//辅助初始化
void Exception::init(const char* message, const char* file, const int line) NO_EXCEPT
{
    m_message = ( message ? strdup(message) : NULL );

    if( file )
    {
        char lineBuf[16] = {0};
        snprintf(lineBuf, sizeof(lineBuf), "%d", line);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(lineBuf) + 2));

        if( m_location )
        {
            strcpy(m_location, file);
            strcat(m_location, ":");
            strcat(m_location, lineBuf);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception() NO_EXCEPT
    : m_message(NULL), m_location(NULL)
{}

Exception::Exception(const char* message) NO_EXCEPT
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, const int line) NO_EXCEPT
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, const int line) NO_EXCEPT
{
    init(message, file, line);
}

Exception::Exception(const Exception &except) NO_EXCEPT
    : m_message(strdup(except.m_message)),
      m_location(strdup(except.m_location))
{}

Exception& Exception::operator = (const Exception& except) NO_EXCEPT
{
    if( this != &except )
    {
        free(m_message);
        free(m_location);

        m_message = strdup(except.m_message);
        m_location = strdup(except.m_location);
    }

    return *this;
}

Exception::~Exception() NO_EXCEPT
{
    free(m_message);
    free(m_location);
}

// 计算异常
ArithmeticException::ArithmeticException() NO_EXCEPT
    : Exception() {}

ArithmeticException::ArithmeticException(const char* message) NO_EXCEPT
    : Exception(message) {}

ArithmeticException::ArithmeticException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line) {}

ArithmeticException::ArithmeticException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line) {}

ArithmeticException::ArithmeticException(const ArithmeticException& except) NO_EXCEPT
    : Exception(except) {}

ArithmeticException& ArithmeticException::operator =(const ArithmeticException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

// 空指针异常子类
NullPointerException::NullPointerException() NO_EXCEPT
    : Exception() {}

NullPointerException::NullPointerException(const char* message) NO_EXCEPT
    : Exception(message) {}

NullPointerException::NullPointerException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line) {}

NullPointerException::NullPointerException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line) {}

NullPointerException::NullPointerException(const NullPointerException& except) NO_EXCEPT
    : Exception(except) {}

NullPointerException& NullPointerException::operator =(const NullPointerException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

// 越界异常子类
IndexOutOfBoundsException::IndexOutOfBoundsException() NO_EXCEPT
    : Exception() {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char* message) NO_EXCEPT
    : Exception(message) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException& except) NO_EXCEPT
    : Exception(except) {}

IndexOutOfBoundsException& IndexOutOfBoundsException::operator =(const IndexOutOfBoundsException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

// 内存不足异常子类
NoEnoughMemoryException::NoEnoughMemoryException() NO_EXCEPT
    : Exception() {}

NoEnoughMemoryException::NoEnoughMemoryException(const char* message) NO_EXCEPT
    : Exception(message) {}

NoEnoughMemoryException::NoEnoughMemoryException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line) {}

NoEnoughMemoryException::NoEnoughMemoryException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line) {}

NoEnoughMemoryException::NoEnoughMemoryException(const NoEnoughMemoryException& except) NO_EXCEPT
    : Exception(except) {}

NoEnoughMemoryException& NoEnoughMemoryException::operator =(const NoEnoughMemoryException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

// 参数错误异常子类
InvalidParameterException::InvalidParameterException() NO_EXCEPT
    : Exception() {}

InvalidParameterException::InvalidParameterException(const char* message) NO_EXCEPT
    : Exception(message) {}

InvalidParameterException::InvalidParameterException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line) {}

InvalidParameterException::InvalidParameterException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line) {}

InvalidParameterException::InvalidParameterException(const InvalidParameterException& except) NO_EXCEPT
    : Exception(except) {}

InvalidParameterException& InvalidParameterException::operator =(const InvalidParameterException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

// 非法操作异常子类
InvalidOperationException::InvalidOperationException() NO_EXCEPT
    : Exception(){}

InvalidOperationException::InvalidOperationException(const char* message) NO_EXCEPT
    : Exception(message){}

InvalidOperationException::InvalidOperationException(const char* file, const int line) NO_EXCEPT
    : Exception(file, line){}

InvalidOperationException::InvalidOperationException(const char *message, const char *file, const int line) NO_EXCEPT
    : Exception(message, file, line){}

InvalidOperationException::InvalidOperationException(const InvalidOperationException& except) NO_EXCEPT
    : Exception(except){}

InvalidOperationException& InvalidOperationException::operator = (const InvalidOperationException& except) NO_EXCEPT
{
    Exception::operator = (except);

    return *this;
}

} // namespace HLib



