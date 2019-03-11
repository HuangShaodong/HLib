#ifndef HLIB_POINTER_H
#define HLIB_POINTER_H

#include "Object.h"

namespace HLib
{

template <typename T>
class Pointer : public Object
{
protected:
    T* m_ptr;

public:
    Pointer() NO_EXCEPT;
    Pointer(T* ptr) NO_EXCEPT;

    T* operator ->() NO_EXCEPT;
    const T* operator -> () const NO_EXCEPT;
    T& operator * () NO_EXCEPT;
    const T& operator * () const NO_EXCEPT;

    bool isNull() const NO_EXCEPT;
    T* getPtr() NO_EXCEPT;
    const T* getPtr() const NO_EXCEPT;
};


template<typename T>
Pointer<T>::Pointer() NO_EXCEPT
    : m_ptr(NULL)
{}


template<typename T>
Pointer<T>::Pointer(T* ptr) NO_EXCEPT
    : m_ptr(ptr)
{}


template<typename T>
inline T*
Pointer<T>::operator -> () NO_EXCEPT
{
    return m_ptr;
}


template<typename T>
inline const T*
Pointer<T>::operator -> () const NO_EXCEPT
{
    return m_ptr;
}


template<typename T>
T& Pointer<T>::operator * () NO_EXCEPT
{
    return *m_ptr;
}


template<typename T>
const T& Pointer<T>::operator * () const NO_EXCEPT
{
    return *m_ptr;
}


template<typename T>
bool Pointer<T>::isNull() const NO_EXCEPT
{
    return !m_ptr;
}


template<typename T>
T* Pointer<T>::getPtr() NO_EXCEPT
{
    return m_ptr;
}


template<typename T>
const T* Pointer<T>::getPtr() const NO_EXCEPT
{
    return m_ptr;
}


} // namespace HLib

#endif // HLIB_POINTER_H
