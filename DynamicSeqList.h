#ifndef HLIB_DYNAMICSEQLIST_H
#define HLIB_DYNAMICSEQLIST_H

#include "SeqList.h"

namespace HLib
{

template <typename T>
class DynamicSeqList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicSeqList(const int capacity);
    void resize(const int newCapacity);
    int capacity() const NO_EXCEPT;

    ~DynamicSeqList();
};


template<typename T>
DynamicSeqList<T>::DynamicSeqList(const int capacity)
{
    this->m_array = new T[capacity];

    if( this->m_array )
    {
        this->m_length = 0;
        m_capacity = capacity;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicSeqList object...");
    }
}


// 重置空间大小
template<typename T>
void DynamicSeqList<T>::resize(const int newCapacity)
{
    if( newCapacity != m_capacity )
    {
        T* array = new T[newCapacity];

        if( array )
        {
            const int length = (this->m_length < newCapacity ? this->m_length : newCapacity);
            for( int i=0; i<length; i++ )
            {
                array[i] = this->m_array[i];
            }

            T* tmp = this->m_array;
            this->m_array = array;
            this->m_length = length;
            m_capacity = newCapacity;

            delete[] tmp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicSeqList object...");
        }
    }
}


template<typename T>
int DynamicSeqList<T>::capacity() const NO_EXCEPT
{
    return m_capacity;
}


template<typename T>
DynamicSeqList<T>::~DynamicSeqList()
{
    delete[] this->m_array;
}


} // namespace HLib

#endif // HLIB_DYNAMICSEQLIST_H
