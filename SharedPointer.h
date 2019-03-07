#ifndef HLIB_SHAREDPOINTER_H
#define HLIB_SHAREDPOINTER_H

#include <malloc.h>

#include "Pointer.h"
#include "Exception.h"

namespace HLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

    void clear();

public:
    SharedPointer() NO_EXCEPT;
    SharedPointer(T* ptr);
    SharedPointer(const SharedPointer<T>& obj) NO_EXCEPT;
    SharedPointer<T>& operator = (const SharedPointer<T>& obj);

    ~SharedPointer();
};


template<typename T>
SharedPointer<T>::SharedPointer() NO_EXCEPT
    : Pointer<T>(), m_ref(NULL)
{}


template<typename T>
SharedPointer<T>::SharedPointer(T* ptr)
    : Pointer<T>(ptr)
{
    if( ptr )
    {
        m_ref = static_cast<int*>(malloc(sizeof(int)));

        if( m_ref )
        {
            *m_ref = 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create HLib::SharedPointer object...");
        }
    }
    else
    {
        m_ref = NULL;
    }
}


template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& obj) NO_EXCEPT
    : Pointer<T>(obj.m_ptr), m_ref(obj.m_ref)
{
    if( m_ref )
    {
        (*m_ref)++;
    }
}


template<typename T>
SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>& obj)
{
    if( this != &obj )
    {
        clear();

        this->m_ptr = obj.m_ptr;
        m_ref = obj.m_ref;

        if( m_ref )
        {
            (*m_ref)++;
        }
    }

    return *this;
}


template<typename T>
SharedPointer<T>::~SharedPointer()
{
    clear();
}


// 当前SharedPointer<T>对象不再管理堆空间资源时，引用计数-1
// 当无SharedPointer<T>对象管理堆空间资源时，释放堆空间资源
template<typename T>
void SharedPointer<T>::clear()
{
    T* tmpPtr = this->m_ptr;
    int* tmpRef = m_ref;

    this->m_ptr = NULL;
    m_ref = NULL;

    if( tmpRef )
    {
        (*tmpRef)--;

        if( (*tmpRef) < 1 )
        {
            free(tmpRef);
            delete tmpPtr;
        }
    }
}


// 根据指向的堆空间地址判断SharedPointer<T>对象是否相等
template <typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.getPtr() == r.getPtr());
}

template <typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}


} // namespace HLib

#endif // HLIB_SHAREDPOINTER_H
