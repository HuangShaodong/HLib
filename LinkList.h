#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace HLib
{

template <typename T>
class LinkList : public List<T>
{
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        char buf[sizeof(T)];
        Node* next;
    } m_head;

    int m_length;
    Node* m_curr;
    int m_step;

    Node* position(const int pos) const NO_EXCEPT;

public:
    LinkList();
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
    void clear();
    int length() const NO_EXCEPT;

    bool move(const int pos, const int step = 1) NO_EXCEPT;
    bool next() NO_EXCEPT;
    bool end() const NO_EXCEPT;
    T current();

    ~LinkList();
};


template<typename T>
typename LinkList<T>::Node* LinkList<T>::position(const int pos) const NO_EXCEPT  // O(n)
{
    Node* ret = reinterpret_cast<Node*>(&m_head);

    for( int p=0; p<pos; p++ )
    {
        ret = ret->next;
    }

    return ret;
}


template<typename T>
LinkList<T>::LinkList()
{
    m_head.next = NULL;
    m_length = 0;
    m_curr = NULL;
    m_step = 1;
}


template<typename T>
bool LinkList<T>::insert(const int pos, const T& elem) // O(n)
{
    bool ret = ( (0 <= pos) && (pos <= m_length) );

    if( ret )
    {
        Node* node = new Node();

        if( node )
        {
            Node* curr = position(pos);

            node->value = elem;
            node->next = curr->next;
            curr->next = node;

            m_length++;
        }
        else
        {
           THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
        }
    }

    return ret;
}


template<typename T>
bool LinkList<T>::insert_front(const T& elem) //  O(1)
{
    return insert(0, elem);
}


template<typename T>
bool LinkList<T>::insert_back(const T& elem)  // O(n)
{
    return insert(m_length, elem);
}


template<typename T>
bool LinkList<T>::remove(const int pos)  // O(n)
{
    bool ret = ( (0 <= pos) && (pos <m_length) );

    if( ret )
    {
        Node* curr = position(pos);
        Node* toDel = curr->next;

        if( m_curr == toDel )
        {
            m_curr = m_curr->next;
        }

        curr->next = toDel->next;
        m_length--;

        delete toDel;
    }

    return ret;
}

template<typename T>
bool LinkList<T>::remove_front()  // O(1)
{
    return remove(0);
}

template<typename T>
bool LinkList<T>::remove_back()  // O(n)
{
    return remove(m_length-1);
}


template<typename T>
bool LinkList<T>::set(const int pos, const T& elem)  // O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        position(pos)->next->value = elem;
    }

    return ret;
}


template<typename T>
bool LinkList<T>::get(const int pos, T& elem) const NO_EXCEPT // O(n)
{
    bool ret = ( (0 <= pos) && (pos < m_length) );

    if( ret )
    {
        elem = position(pos)->next->value;
    }

    return ret;
}


template<typename T>
T LinkList<T>::get(const int pos) const
{
    T ret;
    if( !get(pos, ret) )
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "parameter pos is OutofBound...");
    }

    return ret;
}


template<typename T>
int LinkList<T>::find(const T& elem) const  // O(n)
{
    int ret = -1;

    int curr = 0;
    Node* node = m_head.next;

    while( node )
    {
        if( elem == node->value )
        {
            ret = curr;
            break;
        }

        node = node->next;
        ret++;
    }

    return ret;
}


template<typename T>
void LinkList<T>::clear()
{
    Node* node = m_head.next;
    while( m_head.next )
    {
        Node* toDel = node;
        m_head.next = node->next;

        if( m_curr == toDel )
        {
            m_curr = m_curr->next;
        }

        m_length--;
        delete toDel;
    }
}


template<typename T>
inline int LinkList<T>::length() const NO_EXCEPT
{
    return m_length;
}


template<typename T>
bool LinkList<T>::move(const int pos, const int step) NO_EXCEPT
{
    bool ret = ( (0 <= pos) && (pos < m_length) && (step > 0));

    if( ret )
    {
        m_curr = position(pos)->next;
        m_step = step;
    }

    return ret;
}


template<typename T>
bool LinkList<T>::next() NO_EXCEPT
{
    int curr = 0;

    while( (curr < m_step) && (!end()))
    {
        m_curr = m_curr->next;
        curr++;
    }

    return curr == m_step;
}


template<typename T>
bool LinkList<T>::end() const NO_EXCEPT
{
    return (NULL == m_curr);
}

template<typename T>
T LinkList<T>::current()
{
    if( !end() )
    {
        return m_curr->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No value at current pos...");
    }
}


template<typename T>
LinkList<T>::~LinkList()
{
    clear();
}


} // namespace HLib

#endif // LINKLIST_H
