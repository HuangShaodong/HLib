#ifndef HLIB_EXCEPTION_H
#define HLIB_EXCEPTION_H

#include "Object.h"

namespace HLib
{

#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(excep, msg) (throw excep(msg, __FILE__, __LINE__))
#endif

// 异常类的实现决不能抛异常
class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, const int line) NO_EXCEPT;

public:
    Exception() NO_EXCEPT;
    Exception(const char* message) NO_EXCEPT;
    Exception(const char* file, const int line) NO_EXCEPT;
    Exception(const char* message, const char* file, const int line) NO_EXCEPT;
    Exception(const Exception& except) NO_EXCEPT;
    Exception& operator = (const Exception& except) NO_EXCEPT;

    virtual const char* message() const NO_EXCEPT { return m_message; }
    virtual const char* location() const NO_EXCEPT { return m_location; }

    virtual ~Exception() NO_EXCEPT = 0;
};


// 计算异常子类
class ArithmeticException : public Exception
{
public:
    ArithmeticException() NO_EXCEPT;
    ArithmeticException(const char* message) NO_EXCEPT;
    ArithmeticException(const char* file, const int line) NO_EXCEPT;
    ArithmeticException(const char* message, const char* file, const int line) NO_EXCEPT;
    ArithmeticException(const ArithmeticException& except) NO_EXCEPT;
    ArithmeticException& operator = (const ArithmeticException& except) NO_EXCEPT;
};


// 空指针异常子类
class NullPointerException : public Exception
{
public:
    NullPointerException() NO_EXCEPT;
    NullPointerException(const char* message) NO_EXCEPT;
    NullPointerException(const char* file, const int line) NO_EXCEPT;
    NullPointerException(const char* message, const char* file, const int line) NO_EXCEPT;
    NullPointerException(const NullPointerException& except) NO_EXCEPT;
    NullPointerException& operator = (const NullPointerException& except) NO_EXCEPT;
};


// 越界异常子类
class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() NO_EXCEPT;
    IndexOutOfBoundsException(const char* message) NO_EXCEPT;
    IndexOutOfBoundsException(const char* file, const int line) NO_EXCEPT;
    IndexOutOfBoundsException(const char* message, const char* file, const int line) NO_EXCEPT;
    IndexOutOfBoundsException(const IndexOutOfBoundsException& except) NO_EXCEPT;
    IndexOutOfBoundsException& operator = (const IndexOutOfBoundsException& except) NO_EXCEPT;
};


// 内存不足异常子类
class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() NO_EXCEPT;
    NoEnoughMemoryException(const char* message) NO_EXCEPT;
    NoEnoughMemoryException(const char* file, const int line) NO_EXCEPT;
    NoEnoughMemoryException(const char* message, const char* file, const int line) NO_EXCEPT;
    NoEnoughMemoryException(const NoEnoughMemoryException& except) NO_EXCEPT;
    NoEnoughMemoryException& operator = (const NoEnoughMemoryException& except) NO_EXCEPT;
};


// 参数错误异常子类
class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() NO_EXCEPT;
    InvalidParameterException(const char* message) NO_EXCEPT;
    InvalidParameterException(const char* file, const int line) NO_EXCEPT;
    InvalidParameterException(const char* message, const char* file, const int line) NO_EXCEPT;
    InvalidParameterException(const InvalidParameterException& except) NO_EXCEPT;
    InvalidParameterException& operator = (const InvalidParameterException& except) NO_EXCEPT;
};


// 非法操作异常子类
class InvalidOperationException : public Exception
{
public:
    InvalidOperationException() NO_EXCEPT;
    InvalidOperationException(const char* message) NO_EXCEPT;
    InvalidOperationException(const char* file, const int line) NO_EXCEPT;
    InvalidOperationException(const char* message, const char* file, const int line) NO_EXCEPT;
    InvalidOperationException(const InvalidOperationException& except) NO_EXCEPT;
    InvalidOperationException& operator = (const InvalidOperationException& except) NO_EXCEPT;
};


} // namespace HLib

#endif // HLIB_EXCEPTION_H
