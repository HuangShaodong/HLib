#ifndef HLIB_SEQLIST_H
#define HLIB_SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace HLib
{

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;

public:
    bool insert(const int pos, const T& elem);
    bool insert_front(const T& elem);
    bool insert_back(const T& elem);
    bool remove(const int pos);
    bool remove_front();
    bool remove_back();
    bool set(const int pos, const T& elem);
    bool get(const int pos, T& elem) const NO_EXCEPT;
    T get(const int pos) const;
    int find(const T& elem) const;
    int length() const NO_EXCEPT;
    void clear();
    T& operator [] (const int pos);
    T operator [] (const int pos) const;
    virtual int capacity() const NO_EXCEPT = 0;
};


template<typename T>
bool SeqList<T>::insert(const int pos, const T& elem)  // O(n)
{
    bool ret = ( (0 <= pos) && (pos <= m_length) );
    ret = ret && (m_length < capacity());

    if( ret )
    {
        for( int p=m_length-1; p>=pos; p-- )
        {
            m_array[p+1] = m_array[p];
        }

        m_array[pos] = elem;
        m_length++;
    }

    return ret;
}


template<typename T>
bool SeqList<T>::insert_front(const T& elem)
{
    return insert(0, elem);
}


template<typename T>
bool SeqList<T>::insert_back(const T& elem)
{
    return insert(m_length, elem);
}


template<typename T>
bool SeqList<T>::remove(const int pos)  // O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        for( int p=pos; p<m_length-1; p++ )
        {
            m_array[p] = m_array[p+1];
        }

        m_length--;
    }

    return ret;
}

template<typename T>
bool SeqList<T>::remove_front()
{
    return remove(0);
}


template<typename T>
bool SeqList<T>::remove_back()
{
    return remove(m_length-1);
}


template<typename T>
bool SeqList<T>::set(const int pos, const T& elem) // O(1)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        m_array[pos] = elem;
    }

    return ret;
}


template<typename T>
bool SeqList<T>::get(const int pos, T& elem) const NO_EXCEPT  // O(1)
{
    bool ret = true;

    if( (0 <= pos) && (pos < m_length) )
    {
        elem = m_array[pos];
    }

    return ret;
}


template<typename T>
T SeqList<T>::get(const int pos) const
{
    T ret;

    if( !get(pos, ret) )
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "parameter pos is OutOfBounds...");
    }

    return ret;
}


template<typename T>
int SeqList<T>::find(const T& elem) const  // O(n)
{
    int ret = -1;

    for( int p=0; p<m_length; p++ )
    {
        if( elem == m_array[p] )
        {
            ret = p;
            break;
        }
    }

    return ret;
}


template<typename T>
inline int SeqList<T>::length() const NO_EXCEPT
{
    return m_length;
}


template<typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}


template<typename T>
T& SeqList<T>::operator [] (const int pos)
{
    if( (0 <= pos) && (pos < m_length) )
    {
        return m_array[pos];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter pos is OutOfBounds...");
    }
}


template<typename T>
T SeqList<T>::operator [] (const int pos) const
{
    return (const_cast<SeqList<T>&>(*this))[pos];
}


} // namespace HLib

#endif // HLIB_SEQLIST_H
