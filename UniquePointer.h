#ifndef HLIB_UNIQUEPOINTER_H
#define HLIB_UNIQUEPOINTER_H

#include "Pointer.h"

namespace HLib
{

// 仅能指向堆空间中单个对象或指针
// 一片堆空间仅能由一个UniquePointer<T>对象标识
// UniquePointer<T>对象具备空间所有权转让能力
template <typename T>
class UniquePointer : public Pointer<T>
{
public:
    UniquePointer() NO_EXCEPT;
    UniquePointer(T* ptr);
    UniquePointer(const UniquePointer<T>& obj);
    UniquePointer<T>& operator = (const UniquePointer<T>& obj);

    ~UniquePointer();
};


template<typename T>
UniquePointer<T>::UniquePointer() NO_EXCEPT
{}


template<typename T>
UniquePointer<T>::UniquePointer(T* ptr)
    : Pointer<T>(ptr)
{}


template<typename T>
UniquePointer<T>::UniquePointer(const UniquePointer<T>& obj)
    : Pointer<T>(obj)
{
    this->m_ptr = obj.m_ptr;

    const_cast<UniquePointer<T>&>(obj).m_ptr = NULL;
}


template<typename T>
UniquePointer<T>& UniquePointer<T>::operator = (const UniquePointer<T>& obj)
{
    if( this != &obj )
    {
        T* tmp = this->m_ptr;
        this->m_ptr = obj.m_ptr;

        const_cast<UniquePointer<T>&>(obj).m_ptr = NULL;
        delete tmp;
    }

    return *this;
}


template<typename T>
UniquePointer<T>::~UniquePointer()
{
    delete this->m_ptr;
}


} // namespace HLib

#endif // HLIB_UNIQUEPOINTER_H
