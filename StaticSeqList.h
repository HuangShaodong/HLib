#ifndef HLIB_STATICSEQLIST_H
#define HLIB_STATICSEQLIST_H

#include "SeqList.h"

namespace HLib
{

template <typename T, int N>
class StaticSeqList : public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticSeqList() NO_EXCEPT;
    int capacity() const NO_EXCEPT;
};


template<typename T, int N>
StaticSeqList<T, N>::StaticSeqList() NO_EXCEPT
{
    this->m_array = m_space;
    this->m_length = 0;
}


template<typename T, int N>
inline int StaticSeqList<T, N>::capacity() const NO_EXCEPT
{
    return N;
}


} // namespace HLib

#endif // HLIB_STATICSEQLIST_H
